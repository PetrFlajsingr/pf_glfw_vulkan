//
// Created by petr on 10/19/20.
//

#ifndef VOXEL_RENDER_BUFFERVIEW_H
#define VOXEL_RENDER_BUFFERVIEW_H

#include <pf_common/concepts/PtrConstructible.h>
#include "VulkanObject.h"
#include "fwd.h"
#include <vulkan/vulkan.hpp>
#include <pf_glfw_vulkan/_export.h>

namespace pf::vulkan {

struct PF_GLFW_VULKAN_EXPORT BufferViewConfig {
  vk::BufferViewCreateFlags createFlags;
  vk::Format format;
  vk::DeviceSize offset;
  vk::DeviceSize range;
};

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
#endif//VOXEL_RENDER_BUFFERVIEW_H
