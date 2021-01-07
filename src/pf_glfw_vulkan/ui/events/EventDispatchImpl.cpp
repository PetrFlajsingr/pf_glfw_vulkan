//
// Created by petr on 10/12/20.
//
#include "EventDispatchImpl.h"

namespace pf::events {

void EventDispatchImpl::notifyMouse(MouseEventType type, MouseButton button, std::pair<double, double> location,
                                    std::pair<double, double> delta) {
  if (inputIgnorePredicate()) { return; }
  auto mouseClicked = false;
  if (type == MouseEventType::Down) {
    buttonsDown.emplace(button);
  } else if (type == MouseEventType::Up) {
    mouseClicked = buttonsDown.contains(button);
    buttonsDown.erase(button);
  }
  const auto &listeners = mouseListeners[magic_enum::enum_integer(type)];
  const auto event = MouseEvent{.type = type, .button = button, .location = location, .delta = delta};
  for (auto &[id, listener] : listeners) {
    if (listener(event)) { break; }
  }
  if (mouseClicked) {
    using namespace std::chrono_literals;
    if (isDblClick()) {
      lastClickTime = std::chrono::steady_clock::now();
      notifyMouse(MouseEventType::DblClick, event.button, event.location, event.delta);
    } else {
      lastClickTime = std::chrono::steady_clock::now();
      enqueue(
          [this, event] {
            if (std::chrono::steady_clock::now() - lastClickTime < DBL_CLICK_LIMIT) { return; }
            notifyMouse(MouseEventType::Click, event.button, event.location, event.delta);
          },
          DBL_CLICK_LIMIT);
    }
  }
}
void EventDispatchImpl::notifyKey(KeyEventType type, char key) {
  if (inputIgnorePredicate()) { return; }
  const auto &listeners = keyListeners[magic_enum::enum_integer(type)];
  const auto event = KeyEvent{.type = type, .key = key};
  for (auto &[id, listener] : listeners) {
    if (listener(event)) { break; }
  }
}
void EventDispatchImpl::notifyText(std::string text) {
  if (inputIgnorePredicate()) { return; }
  const auto event = TextEvent{.text = std::move(text)};
  for (auto &[id, listener] : textListeners) {
    if (listener(event)) { break; }
  }
}
void EventDispatchImpl::onFrame() {
  const auto currTime = std::chrono::steady_clock::now();
  while (!eventQueue.empty() && eventQueue.top().execTime <= currTime) {
    eventQueue.top()();
    eventQueue.pop();
  }
}
EventDispatchImpl::ListenerId EventDispatchImpl::generateListenerId() { return getNext(idGenerator); }
bool EventDispatchImpl::isDblClick() {
  const auto currTime = std::chrono::steady_clock::now();
  const auto difference = currTime - lastClickTime;
  return difference < DBL_CLICK_LIMIT;
}
const std::unordered_set<MouseButton> &EventDispatchImpl::getMouseButtonsDown() const { return buttonsDown; }
bool EventDispatchImpl::DelayEvent::operator<(const EventDispatchImpl::DelayEvent &rhs) const {
  return execTime < rhs.execTime;
}
void EventDispatchImpl::DelayEvent::operator()() const { fnc(); }

}// namespace pf::events