//
// Created by petr on 9/25/20.
//

#ifndef PF_GLFW_VULKAN_VULKANEXCEPTION_H
#define PF_GLFW_VULKAN_VULKANEXCEPTION_H

#include <pf_common/exceptions/StackTraceException.h>
#include <pf_glfw_vulkan/_export.h>

namespace pf::vulkan {
class PF_GLFW_VULKAN_EXPORT VulkanException : public StackTraceException {
 public:
  explicit VulkanException(const std::string_view &message);
  static VulkanException fmt(std::string_view fmt, auto &&...args) {
    return VulkanException(fmt::format(fmt, args...));
  }
};
}// namespace pf::vulkan
#endif//PF_GLFW_VULKAN_VULKANEXCEPTION_H
