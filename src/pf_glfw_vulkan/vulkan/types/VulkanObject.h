//
// Created by petr on 10/12/20.
//

#ifndef PF_GLFW_VULKAN_VULKAN_TYPES_VULKANOBJECT_H
#define PF_GLFW_VULKAN_VULKAN_TYPES_VULKANOBJECT_H

#include <memory>
#include <pf_glfw_vulkan/_export.h>
#include <string>

namespace pf::vulkan {
// TODO: docs
// TODO: change set usage to Flags<Enum>
class PF_GLFW_VULKAN_EXPORT VulkanObject {
 public:
  [[nodiscard]] virtual std::string info() const = 0;
  virtual ~VulkanObject() = default;

  inline friend std::ostream &operator<<(std::ostream &ostream, const VulkanObject &obj) {
    return ostream << obj.info();
  }
};
}// namespace pf::vulkan

#endif//PF_GLFW_VULKAN_VULKAN_TYPES_VULKANOBJECT_H
