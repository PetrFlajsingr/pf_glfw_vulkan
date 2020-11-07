//
// Created by petr on 9/27/20.
//

#ifndef PF_GLFW_VULKAN_VULKAN_TYPES_SURFACE_H
#define PF_GLFW_VULKAN_VULKAN_TYPES_SURFACE_H

#include "VulkanObject.h"
#include "Instance.h"
#include "fwd.h"
#include <pf_common/concepts/PtrConstructible.h>
#include <pf_glfw_vulkan/_export.h>
#include <pf_glfw_vulkan/concepts/Window.h>

namespace pf::vulkan {

class PF_GLFW_VULKAN_EXPORT Surface : public VulkanObject, public PtrConstructible<Surface> {
 public:
  template<ui::Window Window>
  explicit Surface(std::shared_ptr<Instance> inst, Window &window)
      : instance(std::move(inst)), vkSurface(window.createVulkanSurface(**instance)),
        windowSizeFnc([&window] { return window.getResolution(); }) {}

  Surface(const Surface &other) = delete;
  Surface &operator=(const Surface &other) = delete;

  [[nodiscard]] const vk::SurfaceKHR &getSurface();
  [[nodiscard]] Instance &getInstance();

  const vk::SurfaceKHR &operator*() const;
  vk::SurfaceKHR const *operator->() const;

  [[nodiscard]] std::string info() const override;

  [[nodiscard]] ui::Resolution getWindowSize() const;

 private:
  std::shared_ptr<Instance> instance;
  vk::UniqueSurfaceKHR vkSurface;

  std::function<ui::Resolution()> windowSizeFnc;
};

}// namespace pf::vulkan

#endif//PF_GLFW_VULKAN_VULKAN_TYPES_SURFACE_H
