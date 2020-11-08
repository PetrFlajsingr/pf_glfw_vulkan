//
// Created by petr on 10/27/20.
//

#ifndef PF_GLFW_VULKAN_VULKAN_TYPES_DESCRIPTORPOOL_H
#define PF_GLFW_VULKAN_VULKAN_TYPES_DESCRIPTORPOOL_H

#include "configs/DescriptorPoolConfig.h"
#include "fwd.h"
#include <pf_common/concepts/PtrConstructible.h>
#include <pf_glfw_vulkan/_export.h>
#include <vulkan/vulkan.hpp>

namespace pf::vulkan {

class PF_GLFW_VULKAN_EXPORT DescriptorPool : public PtrConstructible<DescriptorPool> {
 public:
  DescriptorPool(std::shared_ptr<LogicalDevice> device, DescriptorPoolConfig &&config);

  [[nodiscard]] vk::DescriptorPool &getDescriptorPool();
  vk::DescriptorPool &operator*();
  vk::DescriptorPool *operator->();

  [[nodiscard]] LogicalDevice &getDevice();

 private:
  vk::UniqueDescriptorPool vkDescriptorPool;
  std::shared_ptr<LogicalDevice> logicalDevice;
};
}// namespace pf::vulkan
#endif//PF_GLFW_VULKAN_VULKAN_TYPES_DESCRIPTORPOOL_H
