//
// Created by petr on 9/24/20.
//

#ifndef PF_GLFW_VULKAN_UI_EVENTS_EVENTDISPATCHIMPL_H
#define PF_GLFW_VULKAN_UI_EVENTS_EVENTDISPATCHIMPL_H

#include "common.h"
#include <array>
#include <chrono>
#include <concepts>
#include <pf_common/Subscription.h>
#include <pf_common/coroutines/Sequence.h>
#include <pf_glfw_vulkan/_export.h>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <utility>

namespace pf::events {
class PF_GLFW_VULKAN_EXPORT EventDispatchImpl {
 public:
  Subscription addMouseListener(MouseEventType type, MouseEventListener auto listener) {
    const auto id = generateListenerId();
    mouseListeners[magic_enum::enum_integer(type)][id] = listener;
    return Subscription(
        [id, type, this] { mouseListeners[magic_enum::enum_integer(type)].erase(id); });
  }

  Subscription addKeyListener(KeyEventType type, KeyEventListener auto listener) {
    const auto id = generateListenerId();
    keyListeners[magic_enum::enum_integer(type)][id] = listener;
    return Subscription(
        [id, type, this] { keyListeners[magic_enum::enum_integer(type)].erase(id); });
  }

  Subscription addTextListener(TextEventListener auto listener) {
    const auto id = generateListenerId();
    textListeners[id] = listener;
    return Subscription([id, this] { textListeners.erase(id); });
  }

  [[nodiscard]] const std::unordered_set<MouseButton> &getMouseButtonsDown() const;

  void enqueue(std::invocable auto &&fnc,
               std::chrono::milliseconds delay = std::chrono::milliseconds(0)) {
    const auto execTime = std::chrono::steady_clock::now() + delay;
    eventQueue.emplace(fnc, execTime);
  }

  void setInputIgnorePredicate(InputIgnorePredicate auto pred) { inputIgnorePredicate = pred; }

 protected:
  using ListenerId = uint32_t;

  void notifyMouse(MouseEventType type, MouseButton button, std::pair<double, double> location,
                   std::pair<double, double> delta);

  void notifyKey(KeyEventType type, char key);

  void notifyText(std::string text);

  void onFrame();

 private:
  ListenerId generateListenerId();

  bool isDblClick();

  cppcoro::generator<ListenerId> idGenerator = iota<ListenerId>();

  std::function<bool()> inputIgnorePredicate = [] { return false; };

  std::array<std::unordered_map<ListenerId, details::MouseEventFnc>, MouseEventTypeCount>
      mouseListeners;
  std::array<std::unordered_map<ListenerId, details::KeyEventFnc>, KeyboardEventTypeCount>
      keyListeners;
  std::unordered_map<ListenerId, details::TextEventFnc> textListeners;

  std::unordered_set<MouseButton> buttonsDown;
  std::chrono::steady_clock::time_point lastClickTime{};
  const std::chrono::milliseconds DBL_CLICK_LIMIT{1500};

  struct DelayEvent {
    std::function<void()> fnc;
    std::chrono::steady_clock::time_point execTime;
    bool operator<(const DelayEvent &rhs) const;

    void operator()() const;
  };
  std::priority_queue<DelayEvent, std::vector<DelayEvent>, std::less<>> eventQueue;
};
}// namespace pf::events

#endif//PF_GLFW_VULKAN_UI_EVENTS_EVENTDISPATCHIMPL_H
