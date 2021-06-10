//
// Created by petr on 6/10/21.
//

#ifndef PF_GLFW_VULKAN_SRC_PF_GLFW_VULKAN_VULKAN_TYPES_BUFFERMAPPING_H
#define PF_GLFW_VULKAN_SRC_PF_GLFW_VULKAN_VULKAN_TYPES_BUFFERMAPPING_H

#include "VulkanObject.h"
#include "fwd.h"
#include <algorithm>
#include <cassert>
#include <pf_common/concepts/PtrConstructible.h>
#include <span>
#include <type_traits>
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
    [[maybe_unused]] const auto typedSize = getTypedSize<T>();
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
    [[maybe_unused]] const auto size = getSize();
    assert(start < size);
    assert(start + count <= size);
    return std::span<T>(reinterpret_cast<T *>(reinterpret_cast<std::byte *>(dataPtr) + start), count / sizeof(T));
  }

  template<typename T>
  void set(T &&value, vk::DeviceSize start = 0) {
    if constexpr (std::ranges::contiguous_range<T>) {
      using ValueType = std::ranges::range_value_t<T>;
      [[maybe_unused]] const auto typedSize = getTypedSize<ValueType>();
      assert(start < typedSize);
      assert(start + value.size() <= typedSize);
      std::ranges::copy(value, reinterpret_cast<ValueType *>(dataPtr) + start);
    } else {
      [[maybe_unused]] const auto typedSize = getTypedSize<std::remove_reference_t<T>>();
      assert(start < typedSize);
      assert(start + 1 <= typedSize);
      data<std::decay_t<T>>(start)[0] = value;
    }
  }

  template<typename T>
  void setRawOffset(T &&value, vk::DeviceSize start) {
    if constexpr (std::ranges::contiguous_range<T>) {
      using ValueType = typename std::ranges::range_value_t<T>;
      [[maybe_unused]] const auto size = getSize();
      assert(start < size);
      assert(start + value.size() * sizeof(ValueType) <= size);
      std::ranges::copy(value, reinterpret_cast<ValueType *>(reinterpret_cast<std::byte *>(dataPtr) + start));
    } else {
      [[maybe_unused]] const auto size = getSize();
      [[maybe_unused]] constexpr auto valueSize = sizeof(std::remove_reference_t<T>);
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
}// namespace pf::vulkan
#endif//PF_GLFW_VULKAN_SRC_PF_GLFW_VULKAN_VULKAN_TYPES_BUFFERMAPPING_H
