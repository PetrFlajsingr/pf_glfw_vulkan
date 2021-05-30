//
// Created by petr on 5/29/21.
//

#include "Window.h"
#include <fmt/format.h>
#include <pf_common/exceptions/StackTraceException.h>

namespace pf::ui {
using namespace enum_operators;

std::ostream &operator<<(std::ostream &os, const Resolution &res) {
  os << fmt::format("{}x{}", res.width, res.height);
  return os;
}

Window::Window(const Resolution &resolution, Mode mode, const std::string &title)
    : resolution(resolution), mode(mode), title(title) {}

void Window::setResolution(Resolution newResolution) { resolution = newResolution; }

Resolution Window::getResolution() const { return resolution; }

void Window::setMode(Mode newMode) { mode = newMode; }

Mode Window::getMode() const { return mode; }

void Window::setTitle(std::string newTitle) { title = std::move(newTitle); }

std::string_view Window::getTitle() const { return title; }

WindowEventsDefaultImpl::WindowEventsDefaultImpl(const Resolution &resolution, Mode mode, const std::string &title)
    : Window(resolution, mode, title) {}

Subscription WindowEventsDefaultImpl::addMouseListenerImpl(events::MouseEventType event,
                                                           events::details::MouseEventFnc listener) {
  const auto id = generateListenerId();
  mouseListeners[*magic_enum::enum_index(event)][id] = listener;
  return Subscription([id, event, this] { mouseListeners[*magic_enum::enum_index(event)].erase(id); });
}

Subscription WindowEventsDefaultImpl::addKeyboardListenerImpl(events::KeyEventType event,
                                                              events::details::KeyEventFnc listener) {
  const auto id = generateListenerId();
  keyListeners[*magic_enum::enum_index(event)][id] = listener;
  return Subscription([id, event, this] { keyListeners[*magic_enum::enum_index(event)].erase(id); });
}

Subscription WindowEventsDefaultImpl::addTextListenerImpl(events::details::TextEventFnc listener) {
  const auto id = generateListenerId();
  textListeners[id] = listener;
  return Subscription([id, this] { textListeners.erase(id); });
}

void WindowEventsDefaultImpl::setInputIgnorePredicateImpl(std::function<bool()> predicate) {
  inputIgnorePredicate = predicate;
}

void WindowEventsDefaultImpl::enqueueImpl(std::function<void()> callable, std::chrono::microseconds delay) {
  const auto execTime = std::chrono::steady_clock::now() + delay;
  eventQueue.emplace(callable, execTime);
}

Flags<events::MouseButton> WindowEventsDefaultImpl::getMouseButtonsDown() { return buttonsDown; }

WindowEventsDefaultImpl::ListenerId WindowEventsDefaultImpl::generateListenerId() { return getNext(idGenerator); }

bool WindowEventsDefaultImpl::isDblClick() {
  const auto currTime = std::chrono::steady_clock::now();
  const auto difference = currTime - lastClickTime;
  return difference < DBL_CLICK_LIMIT;
}
void WindowEventsDefaultImpl::notifyMouse(events::MouseEventType type, events::MouseButton button,
                                          std::pair<double, double> location, std::pair<double, double> delta) {
  if (inputIgnorePredicate()) { return; }
  auto mouseClicked = false;
  if (type == events::MouseEventType::Down) {
    buttonsDown |= button;
  } else if (type == events::MouseEventType::Up) {
    mouseClicked = buttonsDown.is(button);
    buttonsDown &= ~button;
  }
  const auto &listeners = mouseListeners[*magic_enum::enum_index(type)];
  const auto event = events::MouseEvent{.type = type, .button = button, .location = location, .delta = delta};
  for (auto &[id, listener] : listeners) {
    if (listener(event)) { break; }
  }
  if (mouseClicked) {
    using namespace std::chrono_literals;
    if (isDblClick()) {
      lastClickTime = std::chrono::steady_clock::now();
      notifyMouse(events::MouseEventType::DblClick, event.button, event.location, event.delta);
    } else {
      lastClickTime = std::chrono::steady_clock::now();
      enqueue(
          [this, event] {
            if (std::chrono::steady_clock::now() - lastClickTime < DBL_CLICK_LIMIT) { return; }
            notifyMouse(events::MouseEventType::Click, event.button, event.location, event.delta);
          },
          DBL_CLICK_LIMIT);
    }
  }
}
void WindowEventsDefaultImpl::notifyKey(events::KeyEventType type, const Flags<events::ModifierKey> &modifierKeys,
                                        char key) {
  if (inputIgnorePredicate()) { return; }
  const auto &listeners = keyListeners[*magic_enum::enum_index(type)];
  for (auto &[id, listener] : listeners) {
    if (listener(events::KeyEvent{.type = type, .modifiersKeys = modifierKeys, .key = key})) { break; }
  }
}
void WindowEventsDefaultImpl::notifyText(const std::string &text) {
  if (inputIgnorePredicate()) { return; }
  for ([[maybe_unused]] auto &[id, listener] : textListeners) {
    if (listener(events::TextEvent{.text = text})) { break; }
  }
}
void WindowEventsDefaultImpl::onFrame() {
  const auto currTime = std::chrono::steady_clock::now();
  while (!eventQueue.empty() && eventQueue.top().execTime <= currTime) {
    eventQueue.top()();
    eventQueue.pop();
  }
}

bool WindowEventsDefaultImpl::DelayEvent::operator<(const WindowEventsDefaultImpl::DelayEvent &rhs) const {
  return execTime < rhs.execTime;
}

void WindowEventsDefaultImpl::DelayEvent::operator()() const { fnc(); }
}// namespace pf::ui