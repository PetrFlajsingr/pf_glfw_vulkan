//
// Created by petr on 9/28/20.
//

#ifndef PF_GLFW_VULKAN_VULKAN_TYPES_DESCRIPTORSETLAYOUT_H
#define PF_GLFW_VULKAN_VULKAN_TYPES_DESCRIPTORSETLAYOUT_H

#include "VulkanObject.h"
#include "fwd.h"
#include <pf_common/concepts/PtrConstructible.h>
#include <pf_glfw_vulkan/_export.h>
#include <vulkan/vulkan.hpp>

namespace pf::vulkan {

struct PF_GLFW_VULKAN_EXPORT DescriptorSetLayoutBindingConfig {
  uint32_t binding;
  vk::DescriptorType type;
  uint32_t count;
  vk::ShaderStageFlags stageFlags;
};

struct PF_GLFW_VULKAN_EXPORT DescriptorSetLayoutConfig {
  std::vector<DescriptorSetLayoutBindingConfig> bindings;
};

class PF_GLFW_VULKAN_EXPORT DescriptorSetLayout : public VulkanObject, public PtrConstructible<DescriptorSetLayout> {
 public:
  explicit DescriptorSetLayout(std::shared_ptr<LogicalDevice> device, DescriptorSetLayoutConfig &&config);

  DescriptorSetLayout(const DescriptorSetLayout &other) = delete;
  DescriptorSetLayout &operator=(const DescriptorSetLayout &other) = delete;

  [[nodiscard]] const vk::DescriptorSetLayout &getLayout() const;
  [[nodiscard]] LogicalDevice &getDevice();
  [[nodiscard]] std::string info() const override;

  const vk::DescriptorSetLayout &operator*() const;
  vk::DescriptorSetLayout const *operator->() const;

 private:
  std::shared_ptr<LogicalDevice> logicalDevice;
  vk::UniqueDescriptorSetLayout vkSet;
};

}// namespace pf::vulkan
#endif//PF_GLFW_VULKAN_VULKAN_TYPES_DESCRIPTORSETLAYOUT_H
