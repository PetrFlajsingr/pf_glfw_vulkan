//
// Created by petr on 6/10/21.
//

#include "BufferMapping.h"
#include "Buffer.h"
#include "LogicalDevice.h"
#include <fmt/format.h>

namespace pf::vulkan {

BufferMapping::BufferMapping(std::shared_ptr<Buffer> buff, vk::DeviceSize start, vk::DeviceSize count)
    : buffer(std::move(buff)), offset(start), range(count) {
  dataPtr = buffer->getLogicalDevice()->mapMemory(buffer->getMemory(), offset, range, {});
}

BufferMapping::~BufferMapping() { buffer->getLogicalDevice()->unmapMemory(buffer->getMemory()); }
std::string BufferMapping::info() const {
  return fmt::format("Buffer mapping to '{}' with offset: {}, range: {}", buffer->info(), offset, range);
}
vk::DeviceSize BufferMapping::getSize() const { return range; }

void *BufferMapping::rawData() { return dataPtr; }
}// namespace pf::vulkan