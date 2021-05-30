//
// Created by petr on 5/29/21.
//

#ifndef PF_GLFW_VULKAN_SRC_PF_GLFW_VULKAN_UI_WINDOW_H
#define PF_GLFW_VULKAN_SRC_PF_GLFW_VULKAN_UI_WINDOW_H

#include "Resolution.h"
#include <chrono>
#include <cppcoro/generator.hpp>
#include <functional>
#include <optional>
#include <pf_common/Subscription.h>
#include <pf_common/coroutines/Sequence.h>
#include <pf_glfw_vulkan/_export.h>
#include <pf_glfw_vulkan/ui/events/common.h>
#include <queue>
#include <string>
#include <unordered_set>
#include <vulkan/vulkan.hpp>

namespace pf::ui {

std::ostream &operator<<(std::ostream &os, const Resolution &res);

enum class Mode { Windowed, Borderless, Fullscreen, FullscreenBorderless };

struct PF_GLFW_VULKAN_EXPORT WindowSettings {
  Resolution resolution;
  std::string title;
  Mode mode;
};
class PF_GLFW_VULKAN_EXPORT Window {
 public:
  Window(const Resolution &resolution, Mode mode, const std::string &title);
  virtual std::optional<std::string> init() = 0;

  void setMainLoopCallback(std::invocable auto &&callback) { mainLoopCallback = callback; }
  void setResizeCallback(std::invocable<Resolution> auto &&callback) { resizeCallback = callback; }

  virtual void run() = 0;// start mainloop

  virtual void setResolution(Resolution newResolution);
  [[nodiscard]] Resolution getResolution() const;

  virtual void setMode(Mode newMode);
  [[nodiscard]] Mode getMode() const;

  virtual void setTitle(std::string newTitle);
  [[nodiscard]] std::string_view getTitle() const;

  // TODO: minimize, maximize...
  virtual void close() = 0;
  virtual void setCursorPosition(double x, double y) = 0;
  virtual void setCursorHiddenAndCaptured(bool hiddenAndCaptured) = 0;

  Subscription addMouseListener(events::MouseEventType event, events::MouseEventListener auto &&listener) {
    return addMouseListenerImpl(event, std::forward<decltype(listener)>(listener));
  }
  Subscription addKeyboardListener(events::KeyEventType event, events::KeyEventListener auto &&listener) {
    return addKeyboardListenerImpl(event, std::forward<decltype(listener)>(listener));
  }
  Subscription addTextListener(events::TextEventListener auto &&listener) {
    return addTextListenerImpl(std::forward<decltype(listener)>(listener));
  }

  [[nodiscard]] virtual vk::UniqueSurfaceKHR createVulkanSurface(const vk::Instance &instance) = 0;
  [[nodiscard]] virtual std::unordered_set<std::string> requiredVulkanExtensions() = 0;

  void setInputIgnorePredicate(std::predicate auto &&predicate) {
    setInputIgnorePredicateImpl(std::forward<decltype(predicate)>(predicate));
  }

  void enqueue(std::invocable auto &&callable, std::chrono::microseconds delay = std::chrono::microseconds{0}) {
    enqueueImpl(std::forward<decltype(callable)>(callable), delay);
  }

  [[nodiscard]] virtual Flags<events::MouseButton> getMouseButtonsDown() = 0;

 protected:
  virtual Subscription addMouseListenerImpl(events::MouseEventType event, events::details::MouseEventFnc listener) = 0;
  virtual Subscription addKeyboardListenerImpl(events::KeyEventType event, events::details::KeyEventFnc listener) = 0;
  virtual Subscription addTextListenerImpl(events::details::TextEventFnc listener) = 0;
  virtual void setInputIgnorePredicateImpl(std::function<bool()> predicate) = 0;
  virtual void enqueueImpl(std::function<void()> callable, std::chrono::microseconds delay) = 0;

  Resolution resolution;
  Mode mode;
  std::string title;
  std::function<void()> mainLoopCallback = [] {};
  std::function<void(Resolution)> resizeCallback = [](Resolution) {};
};

}// namespace pf::ui

#endif//PF_GLFW_VULKAN_SRC_PF_GLFW_VULKAN_UI_WINDOW_H
