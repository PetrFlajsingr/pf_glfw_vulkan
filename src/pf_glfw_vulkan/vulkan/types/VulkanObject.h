//
// Created by petr on 10/12/20.
//

#ifndef VOXEL_RENDER_VULKANOBJECT_H
#define VOXEL_RENDER_VULKANOBJECT_H

#include <memory>
#include <string>
#include <pf_glfw_vulkan/_export.h>

namespace pf::vulkan {
class PF_GLFW_VULKAN_EXPORT VulkanObject {
 public:
  [[nodiscard]] virtual std::string info() const = 0;
  virtual ~VulkanObject() = default;

  inline friend std::ostream &operator<<(std::ostream &ostream, const VulkanObject &obj) {
    return ostream << obj.info();
  }
};
}// namespace pf::vulkan

#endif//VOXEL_RENDER_VULKANOBJECT_H
