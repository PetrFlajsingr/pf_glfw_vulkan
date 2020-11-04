//
// Created by petr on 10/28/20.
//

#ifndef PF_GLFW_VULKAN_VULKAN_TYPES_SEMAPHORE_H
#define PF_GLFW_VULKAN_VULKAN_TYPES_SEMAPHORE_H

#include "VulkanObject.h"
#include "fwd.h"
#include <pf_common/concepts/PtrConstructible.h>
#include <pf_glfw_vulkan/_export.h>
#include <vulkan/vulkan.hpp>

namespace pf::vulkan {

class PF_GLFW_VULKAN_EXPORT Semaphore : public VulkanObject, public PtrConstructible<Semaphore> {
 public:
  explicit Semaphore(std::shared_ptr<LogicalDevice> device);

  const vk::Semaphore &operator*() const;
  vk::Semaphore const *operator->() const;

  [[nodiscard]] const vk::Semaphore &getVkSemaphore() const;

  [[nodiscard]] LogicalDevice &getLogicalDevice() const;

  [[nodiscard]] std::string info() const override;

 private:
  std::shared_ptr<LogicalDevice> logicalDevice;
  vk::UniqueSemaphore vkSemaphore;
};

}// namespace pf::vulkan

#endif//PF_GLFW_VULKAN_VULKAN_TYPES_SEMAPHORE_H
