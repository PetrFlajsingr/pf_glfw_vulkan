//
// Created by petr on 5/30/21.
//

#ifndef PF_GLFW_VULKAN_SRC_PF_GLFW_VULKAN_UI_WINDOWEVENTSDEFAULTIMPL_H
#define PF_GLFW_VULKAN_SRC_PF_GLFW_VULKAN_UI_WINDOWEVENTSDEFAULTIMPL_H

#include <pf_common/coroutines/Sequence.h>
#include <pf_glfw_vulkan/ui/Window.h>

namespace pf::ui {

class PF_GLFW_VULKAN_EXPORT WindowEventsDefaultImpl : public Window {
 public:
  WindowEventsDefaultImpl(const Resolution &resolution, Mode mode, const std::string &title);
  Flags<events::MouseButton> getMouseButtonsDown() override;

 protected:
  Subscription addMouseListenerImpl(events::MouseEventType event, events::details::MouseEventFnc listener) override;
  Subscription addKeyboardListenerImpl(events::KeyEventType event, events::details::KeyEventFnc listener) override;
  Subscription addTextListenerImpl(events::details::TextEventFnc listener) override;
  void setInputIgnorePredicateImpl(std::function<bool()> predicate) override;
  std::future<void> enqueueImpl(std::function<void()> callable, std::chrono::microseconds delay) override;

  void notifyMouse(events::MouseEventType type, events::MouseButton button, std::pair<double, double> location,
                   std::pair<double, double> delta);

  void notifyKey(events::KeyEventType type, const Flags<events::ModifierKey> &modifierKeys, char key);

  void notifyText(const std::string &text);

  void onFrame();

 private:
  using ListenerId = uint32_t;
  ListenerId generateListenerId();

  bool isDblClick();

  cppcoro::generator<ListenerId> idGenerator = iota<ListenerId>();

  std::function<bool()> inputIgnorePredicate = [] { return false; };

  std::array<std::unordered_map<ListenerId, events::details::MouseEventFnc>, events::MouseEventTypeCount>
      mouseListeners;
  std::array<std::unordered_map<ListenerId, events::details::KeyEventFnc>, events::KeyboardEventTypeCount> keyListeners;
  std::unordered_map<ListenerId, events::details::TextEventFnc> textListeners;

  Flags<events::MouseButton> buttonsDown;
  std::chrono::steady_clock::time_point lastClickTime{};
  const std::chrono::milliseconds DBL_CLICK_LIMIT{500};

  struct DelayEvent {
    static inline auto IdGenerator = iota<std::size_t>();
    DelayEvent(std::function<void()> fnc, const std::chrono::steady_clock::time_point &execTime);
    std::function<void()> fnc;
    std::chrono::steady_clock::time_point execTime;
    std::size_t id = getNext(IdGenerator);
    bool operator<(const DelayEvent &rhs) const;

    void operator()() const;
  };
  std::priority_queue<DelayEvent, std::vector<DelayEvent>, std::less<>> eventQueue;
};

}// namespace pf::ui
#endif//PF_GLFW_VULKAN_SRC_PF_GLFW_VULKAN_UI_WINDOWEVENTSDEFAULTIMPL_H
