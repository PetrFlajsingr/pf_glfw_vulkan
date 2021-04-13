//
// Created by petr on 10/19/20.
//

#ifndef PF_GLFW_VULKAN_VULKAN_TYPES_BUFFER_H
#define PF_GLFW_VULKAN_VULKAN_TYPES_BUFFER_H

#include "VulkanObject.h"
#include "configs/BufferConfig.h"
#include "configs/BufferViewConfig.h"
#include "fwd.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <pf_common/concepts/PtrConstructible.h>
#include <pf_glfw_vulkan/_export.h>
#include <span>
#include <vulkan/vulkan.hpp>

namespace pf::vulkan {

class PF_GLFW_VULKAN_EXPORT BufferMapping : public VulkanObject, public PtrConstructible<BufferMapping> {
 public:
  BufferMapping(std::shared_ptr<Buffer> buff, vk::DeviceSize start, vk::DeviceSize count);
  ~BufferMapping() override;

  [[nodiscard]] void *rawData();

  template<typename T>
  std::span<T> data(vk::DeviceSize start = 0) {
    const auto count = getTypedSize<T>() - start;
    return data<T>(start, count);
  }
  template<typename T>
  std::span<T> data(vk::DeviceSize start, vk::DeviceSize count) {
    const auto typedSize = getTypedSize<T>();
    assert(start < typedSize);
    assert(start + count <= typedSize);
    return std::span<T>(reinterpret_cast<T *>(dataPtr) + start, count);
  }

  template<typename T>
  std::span<T> dataRawOffset(vk::DeviceSize start) {
    const auto count = getTypedSize<T>() - start;
    return data<T>(start, count);
  }
  template<typename T>
  std::span<T> dataRawOffset(vk::DeviceSize start, vk::DeviceSize count) {
    const auto size = getSize();
    assert(start < size);
    assert(start + count <= size);
    return std::span<T>(reinterpret_cast<T *>(reinterpret_cast<std::byte *>(dataPtr) + start), count / sizeof(T));
  }

  template<typename T>
  void set(T &&value, vk::DeviceSize start = 0) {
    if constexpr (std::ranges::contiguous_range<T>) {
      using ValueType = std::ranges::range_value_t<T>;
      const auto typedSize = getTypedSize<ValueType>();
      assert(start < typedSize);
      assert(start + value.size() <= typedSize);
      std::ranges::copy(value, reinterpret_cast<ValueType *>(dataPtr) + start);
    } else {
      const auto typedSize = getTypedSize<std::remove_reference_t<T>>();
      assert(start < typedSize);
      assert(start + 1 <= typedSize);
      data<std::decay_t<T>>(start)[0] = value;
    }
  }

  template<typename T>
  void setRawOffset(T &&value, vk::DeviceSize start) {
    if constexpr (std::ranges::contiguous_range<T>) {
      using ValueType = typename std::ranges::range_value_t<T>;
      const auto size = getSize();
      assert(start < size);
      assert(start + value.size() * sizeof(ValueType) <= size);
      std::ranges::copy(value, reinterpret_cast<ValueType *>(reinterpret_cast<std::byte *>(dataPtr) + start));
    } else {
      const auto size = getSize();
      constexpr auto valueSize = sizeof(std::remove_reference_t<T>);
      assert(start < size);
      assert(start + valueSize <= size);
      *reinterpret_cast<std::decay_t<T> *>(reinterpret_cast<std::byte *>(dataPtr) + start) = value;
    }
  }

  [[nodiscard]] vk::DeviceSize getSize() const;

  template<typename T>
  [[nodiscard]] vk::DeviceSize getTypedSize() const {
    return getSize() / sizeof(T);
  }

  [[nodiscard]] std::string info() const override;

 private:
  std::shared_ptr<Buffer> buffer;
  vk::DeviceSize offset;
  vk::DeviceSize range;

  void *dataPtr = nullptr;
};

class PF_GLFW_VULKAN_EXPORT Buffer : public VulkanObject,
                                     public PtrConstructible<Buffer>,
                                     public std::enable_shared_from_this<Buffer> {
 public:
  Buffer(std::shared_ptr<LogicalDevice> device, BufferConfig &&config, bool allocateImmediately = false);

  void allocate();

  [[nodiscard]] const LogicalDevice &getLogicalDevice() const;
  [[nodiscard]] vk::DeviceSize getSize() const;
  [[nodiscard]] const vk::BufferUsageFlags &getUsageFlags() const;
  [[nodiscard]] vk::SharingMode getSharingMode() const;
  [[nodiscard]] const vk::Buffer &getVkBuffer() const;
  [[nodiscard]] const vk::DeviceMemory &getMemory() const;

  const vk::Buffer &operator*() const;
  vk::Buffer const *operator->() const;

  [[nodiscard]] bool isAllocated() const;

  [[nodiscard]] std::shared_ptr<BufferView> createView(BufferViewConfig &&config);
  [[nodiscard]] BufferMapping mapping(vk::DeviceSize offset = 0);
  [[nodiscard]] BufferMapping mapping(vk::DeviceSize offset, vk::DeviceSize range);
  [[nodiscard]] std::shared_ptr<BufferMapping> mappingShared(vk::DeviceSize offset = 0);
  [[nodiscard]] std::shared_ptr<BufferMapping> mappingShared(vk::DeviceSize offset, vk::DeviceSize range);

  [[nodiscard]] std::string info() const override;

 private:
  uint32_t findMemoryType(uint32_t memoryTypeBits);

  std::shared_ptr<LogicalDevice> logicalDevice;
  vk::DeviceSize size;
  vk::BufferUsageFlags usageFlags;
  vk::SharingMode sharingMode;

  bool isAllocated_ = false;

  vk::UniqueDeviceMemory vkMemory;
  vk::UniqueBuffer vkBuffer;
};

}// namespace pf::vulkan

#endif//PF_GLFW_VULKAN_VULKAN_TYPES_BUFFER_H
