//
// Created by petr on 6/10/21.
//

#include "BufferMemoryPool.h"
#include "Buffer.h"
#include <fmt/format.h>

namespace pf::vulkan {

std::string BufferMemoryPool::info() const { return fmt::format("Memory on buffer: {}", buffer->info()); }

BufferMemoryPool::BufferMemoryPool(std::shared_ptr<Buffer> b, vk::DeviceSize align, vk::DeviceSize bufferOffset,
                                   std::optional<vk::DeviceSize> memSize)
    : alignment(align), buffer(std::move(b)), offsetInBuffer(bufferOffset),
      allocatedMemorySize(memSize.value_or(buffer->getSize() - bufferOffset)) {
  availableMemory.emplace(0, allocatedMemorySize);
}

tl::expected<BufferMemoryPool::Block, std::string> BufferMemoryPool::leaseMemory(vk::DeviceSize size) {
  assert(size != 0);
  size += size % alignment;
  const Chunk *chunkToUse = nullptr;
  for (auto &chunk : availableMemory) {
    if (size <= chunk.size) {
      chunkToUse = &chunk;
      break;
    }
  }
  if (chunkToUse == nullptr) { return tl::make_unexpected("No chunk with enough memory available."); }
  auto block = Block{Id++, chunkToUse->offset, size, shared_from_this()};
  auto newChunk = Chunk{chunkToUse->offset + size, chunkToUse->size - size};
  availableMemory.erase(*chunkToUse);
  if (newChunk.size > 0) { availableMemory.emplace(newChunk); }
  return block;
}

void BufferMemoryPool::returnMemory(const BufferMemoryPool::Block &block) {
  if (!block.valid) { return; }
  //logd(MAIN_TAG, "Returning block: {}", block.info());
  block.valid = false;
  Chunk chunkToAdd{block.getOffset(), block.getSize()};
  const auto followingChunkOffset = block.getOffset() + block.getSize();
  std::vector<Chunk> chunksToRemove{};
  for (auto &chunk : availableMemory) {
    if (chunk.offset > followingChunkOffset) { break; }
    if (chunk.offset + chunk.size == block.getOffset()) {
      chunksToRemove.emplace_back(chunk);
      chunkToAdd.offset -= chunk.size;
      chunkToAdd.size += chunk.size;
    } else if (chunk.offset == followingChunkOffset) {
      chunksToRemove.emplace_back(chunk);
      chunkToAdd.size += chunk.size;
    }
  }
  std::ranges::for_each(chunksToRemove, [this](auto &chunkToRemove) { availableMemory.erase(chunkToRemove); });
  availableMemory.emplace(chunkToAdd);
}

const std::shared_ptr<Buffer> &BufferMemoryPool::getBuffer() const { return buffer; }
vk::DeviceSize BufferMemoryPool::getOffsetInBuffer() const { return offsetInBuffer; }

BufferMemoryPool::Block::Block(BufferMemoryPool::BlockId id, vk::DeviceSize offset, vk::DeviceSize size,
                               std::shared_ptr<BufferMemoryPool> parent)
    : alignment(parent->alignment), id(id), offset_(offset), size(size), owner(std::move(parent)) {}

BufferMemoryPool::Block::Block(BufferMemoryPool::Block &&other) noexcept
    : alignment(other.alignment), id(other.id), offset_(other.offset_), size(other.size), owner(other.owner) {
  other.valid = false;
}

BufferMemoryPool::Block &BufferMemoryPool::Block::operator=(BufferMemoryPool::Block &&other) noexcept {
  other.valid = false;
  id = other.id;
  offset_ = other.offset_;
  size = other.size;
  owner = other.owner;
  return *this;
}

BufferMemoryPool::Block::~Block() {
  if (valid) { owner->returnMemory(*this); }
}

BufferMapping BufferMemoryPool::Block::mapping(vk::DeviceSize offset) {
  assert(valid);
  return BufferMapping(owner->getBuffer(), offset_ + offset + owner->getOffsetInBuffer(), getSize() - offset);
}

BufferMapping BufferMemoryPool::Block::mapping(vk::DeviceSize offset, vk::DeviceSize range) {
  assert(valid);
  return BufferMapping(owner->getBuffer(), offset_ + offset + owner->getOffsetInBuffer(), range);
}

vk::DeviceSize BufferMemoryPool::Block::getSize() const { return size; }
BufferMemoryPool::BlockId BufferMemoryPool::Block::getId() const { return id; }
vk::DeviceSize BufferMemoryPool::Block::getOffset() const { return offset_; }
std::string BufferMemoryPool::Block::info() const {
  if (!valid) { return "Invalid memory block."; }
  return fmt::format("Memory block from pool {}. Offset: {}, size: {}.", owner->info(), offset_, size);
}

bool BufferMemoryPool::Chunk::operator<(const BufferMemoryPool::Chunk &rhs) const { return offset < rhs.offset; }

bool BufferMemoryPool::Chunk::operator>(const BufferMemoryPool::Chunk &rhs) const { return rhs < *this; }

bool BufferMemoryPool::Chunk::operator<=(const BufferMemoryPool::Chunk &rhs) const { return !(rhs < *this); }

bool BufferMemoryPool::Chunk::operator>=(const BufferMemoryPool::Chunk &rhs) const { return !(*this < rhs); }

bool BufferMemoryPool::Chunk::operator==(const BufferMemoryPool::Chunk &rhs) const { return offset == rhs.offset; }

bool BufferMemoryPool::Chunk::operator!=(const BufferMemoryPool::Chunk &rhs) const { return !(rhs == *this); }
}// namespace pf::vulkan