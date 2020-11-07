//
// Created by petr on 10/19/20.
//

#ifndef PF_GLFW_VULKAN_VULKAN_TYPES_BUFFERVIEW_H
#define PF_GLFW_VULKAN_VULKAN_TYPES_BUFFERVIEW_H

#include "VulkanObject.h"
#include "fwd.h"
#include <pf_common/concepts/PtrConstructible.h>
#include <pf_glfw_vulkan/_export.h>
#include <vulkan/vulkan.hpp>
#include "configs/BufferViewConfig.h"

namespace pf::vulkan {

class PF_GLFW_VULKAN_EXPORT BufferView : public VulkanObject, public PtrConstructible<BufferView> {
 public:
  BufferView(std::shared_ptr<Buffer> buff, BufferViewConfig &&config);

  [[nodiscard]] const Buffer &getBuffer() const;
  [[nodiscard]] vk::Format getFormat() const;
  [[nodiscard]] vk::DeviceSize getOffset() const;
  [[nodiscard]] vk::DeviceSize getRange() const;
  [[nodiscard]] const vk::BufferView &getVkBufferView() const;

  [[nodiscard]] std::string info() const override;

 private:
  std::shared_ptr<Buffer> buffer;
  vk::Format format;
  vk::DeviceSize offset;
  vk::DeviceSize range;

  vk::UniqueBufferView vkBufferView;
};
}// namespace pf::vulkan
#endif//PF_GLFW_VULKAN_VULKAN_TYPES_BUFFERVIEW_H
