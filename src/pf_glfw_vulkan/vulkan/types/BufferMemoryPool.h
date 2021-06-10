//
// Created by petr on 5/30/21.
//

#ifndef REALISTIC_VOXEL_RENDERING_SRC_UTILS_BUFFERMEMORYPOOL_H
#define REALISTIC_VOXEL_RENDERING_SRC_UTILS_BUFFERMEMORYPOOL_H

#include "BufferMapping.h"
#include "VulkanObject.h"
#include "fwd.h"
#include <algorithm>
#include <cassert>
#include <optional>
#include <pf_common/concepts/PtrConstructible.h>
#include <pf_glfw_vulkan/_export.h>
#include <set>
#include <tl/expected.hpp>
#include <utility>
#include <vulkan/vulkan.hpp>

namespace pf::vulkan {

// TODO: defrag
class PF_GLFW_VULKAN_EXPORT BufferMemoryPool : public VulkanObject,
                                               public PtrConstructible<BufferMemoryPool>,
                                               public std::enable_shared_from_this<BufferMemoryPool> {
 public:
  using BlockId = std::size_t;
  [[nodiscard]] std::string info() const override;

  /**
   * Returns memory on destruction.
   */
  struct Block : public VulkanObject {
   public:
    friend class BufferMemoryPool;
    Block(BlockId id, vk::DeviceSize offset, vk::DeviceSize size, std::shared_ptr<BufferMemoryPool> parent);
    Block(const Block &) = delete;
    Block &operator=(const Block &) = delete;
    Block(Block &&other) noexcept;

    Block &operator=(Block &&other) noexcept;

    ~Block() override;

    [[nodiscard]] BufferMapping mapping(vk::DeviceSize offset = 0);
    [[nodiscard]] BufferMapping mapping(vk::DeviceSize offset, vk::DeviceSize range);

    [[nodiscard]] vk::DeviceSize getSize() const;
    [[nodiscard]] BlockId getId() const;
    [[nodiscard]] vk::DeviceSize getOffset() const;

    [[nodiscard]] std::string info() const override;

    const std::size_t alignment;

   private:
    BlockId id;
    vk::DeviceSize offset_;
    vk::DeviceSize size;
    std::shared_ptr<BufferMemoryPool> owner;
    mutable bool valid = true;
  };

  explicit BufferMemoryPool(std::shared_ptr<Buffer> b, vk::DeviceSize align, vk::DeviceSize bufferOffset = 0,
                            std::optional<vk::DeviceSize> memSize = std::nullopt);

  [[nodiscard]] tl::expected<Block, std::string> leaseMemory(vk::DeviceSize size);

  void returnMemory(const Block &block);

  [[nodiscard]] const std::shared_ptr<Buffer> &getBuffer() const;
  [[nodiscard]] vk::DeviceSize getOffsetInBuffer() const;
  const std::size_t alignment;

 private:
  struct Chunk {
    vk::DeviceSize offset;
    vk::DeviceSize size;
    inline bool operator<(const Chunk &rhs) const;
    inline bool operator>(const Chunk &rhs) const;
    inline bool operator<=(const Chunk &rhs) const;
    inline bool operator>=(const Chunk &rhs) const;
    inline bool operator==(const Chunk &rhs) const;
    inline bool operator!=(const Chunk &rhs) const;
  };

  std::shared_ptr<Buffer> buffer;
  vk::DeviceSize offsetInBuffer;
  std::set<Chunk> availableMemory;
  vk::DeviceSize allocatedMemorySize;
  static inline std::size_t Id = 0;
};

}// namespace pf::vulkan

#endif//REALISTIC_VOXEL_RENDERING_SRC_UTILS_BUFFERMEMORYPOOL_H
