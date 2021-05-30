//
// Created by petr on 9/24/20.
//

#ifndef PF_GLFW_VULKAN_UI_GLFWWINDOW_H
#define PF_GLFW_VULKAN_UI_GLFWWINDOW_H

#include "events/common.h"
#include <GLFW/glfw3.h>
#include <array>
#include <concepts>
#include <pf_common/Subscription.h>
#include <pf_common/coroutines/Sequence.h>
#include <pf_glfw_vulkan/_export.h>
#include <pf_glfw_vulkan/ui/WindowEventsDefaultImpl.h>
#include <unordered_map>

namespace pf::ui {
class PF_GLFW_VULKAN_EXPORT GlfwWindow final : public WindowEventsDefaultImpl {
 public:
  explicit GlfwWindow(const WindowSettings &settings);
  virtual ~GlfwWindow();
  [[nodiscard]] std::optional<std::string> init() override;

  void run() override;

  void close() override;

  void setCursorPosition(double x, double y) override;
  void setCursorHiddenAndCaptured(bool disabled) override;

  [[nodiscard]] vk::UniqueSurfaceKHR createVulkanSurface(const vk::Instance &instance) override;
  std::unordered_set<std::string> requiredVulkanExtensions() override;

  GLFWwindow *getHandle() const;

 private:
  static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
  static void mousePositionCallback(GLFWwindow *window, double xpos, double ypos);
  static void mouseWheelCallback(GLFWwindow *window, double xpos, double ypos);
  static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
  static void resizeCallback(GLFWwindow *window, int width, int height);
  static Flags<events::ModifierKey> ModToFlags(int mod);
  GLFWwindow *handle{};
  std::function<void()> mainLoopFnc = [] {};
  std::function<void(Resolution)> resizeFnc = [](Resolution) {};
  std::pair<double, double> cursorPosition{0, 0};
};

std::optional<events::MouseButton> glfwButtonToEvents(int button);
std::optional<events::KeyEventType> glfwKeyEventToEvents(int key_event);

std::ostream &operator<<(std::ostream &os, const GlfwWindow &window);
}// namespace pf::ui
#endif//PF_GLFW_VULKAN_UI_GLFWWINDOW_H
