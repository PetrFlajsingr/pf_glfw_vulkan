//
// Created by petr on 11/7/20.
//

#include "TextureConfigs.h"
#include <magic_enum.hpp>
#include <pf_common/exceptions/StackTraceException.h>

vk::Format pf::vulkan::TextureChannelsToVkFormat(pf::vulkan::TextureChannels channels) {
  {
    switch (channels) {
      case TextureChannels::grey: return vk::Format::eR8Srgb;
      case TextureChannels::grey_alpha: return vk::Format::eR8G8Srgb;
      case TextureChannels::rgb: return vk::Format::eR8G8B8Srgb;
      case TextureChannels::rgb_alpha: return vk::Format::eR8G8B8A8Srgb;
      default: throw StackTraceException::fmt("Value not handled in switch: {}", magic_enum::enum_name(channels));
    }
  }
}
