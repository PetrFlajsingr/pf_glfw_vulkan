//
// Created by petr on 9/27/20.
//

#ifndef PF_GLFW_VULKAN_VULKAN_TYPES_COMMON_H
#define PF_GLFW_VULKAN_VULKAN_TYPES_COMMON_H

#include <fmt/format.h>
#include <fmt/ostream.h>
#include <functional>
#include <pf_glfw_vulkan/_export.h>
#include <string>
#include <vulkan/vulkan.hpp>

namespace pf::vulkan {

struct PF_GLFW_VULKAN_EXPORT DebugCallbackData {
  int32_t messageId;
  std::string message;
  inline static DebugCallbackData fromVk(const VkDebugUtilsMessengerCallbackDataEXT &src) {
    return {src.messageIdNumber, std::string(src.pMessage)};
  }
};

using VulkanDebugCallback =
    std::function<bool(DebugCallbackData, vk::DebugUtilsMessageSeverityFlagBitsEXT, vk::DebugUtilsMessageTypeFlagsEXT)>;

using DynamicUniqueDebugUtilsMessengerEXT = vk::UniqueHandle<vk::DebugUtilsMessengerEXT, vk::DispatchLoaderDynamic>;

struct PF_GLFW_VULKAN_EXPORT Version {
  uint32_t major;
  uint32_t minor;
  uint32_t patch;

  inline friend std::ostream &operator<<(std::ostream &os, const Version &self) {
    fmt::format_to(std::ostream_iterator<char>(os), "{}.{}.{}", self.major, self.minor, self.patch);
    return os;
  }
};

namespace literals {
PF_GLFW_VULKAN_EXPORT Version operator""_v(const char *verStr, std::size_t);
}

PF_GLFW_VULKAN_EXPORT inline uint32_t versionToUint32(const pf::vulkan::Version &version) {
  return VK_MAKE_VERSION(version.major, version.minor, version.patch);
}

PF_GLFW_VULKAN_EXPORT std::vector<uint32_t> splitVersionString(const char *verStr);

struct PF_GLFW_VULKAN_EXPORT EngineInfo {
  std::string name;
  Version engineVersion;
};

}// namespace pf::vulkan

#endif//PF_GLFW_VULKAN_VULKAN_TYPES_COMMON_H
