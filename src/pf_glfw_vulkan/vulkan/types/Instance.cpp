//
// Created by petr on 9/26/20.
//

#include "Instance.h"
#include <pf_glfw_vulkan/logging.h>
#include <range/v3/view.hpp>
#include <utility>

namespace pf::vulkan {

Instance::Instance(InstanceConfig config) {
  using namespace logging;
  log(LogLevel::Info, VK_TAG, "Creating vulkan instance.");
  const auto appInfo = vk::ApplicationInfo{.pApplicationName = config.appName.c_str(),
                                           .applicationVersion = versionToUint32(config.appVersion),
                                           .pEngineName = config.engineInfo.name.c_str(),
                                           .engineVersion = versionToUint32(config.engineInfo.engineVersion),
                                           .apiVersion = versionToUint32(config.vkVersion)};
  logFmt(LogLevel::Info, VK_TAG, "App name: {}\nversion: {}\nengine name: {}\nengine version: {}\nvulkan version: {}.",
         config.appName, config.appVersion, config.engineInfo.name, config.engineInfo.engineVersion, config.vkVersion);

  const auto messageSeverityFlags = vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose
      | vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning
      | vk::DebugUtilsMessageSeverityFlagBitsEXT::eError;
  const auto messageTypeFlags = vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral
      | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation;
  const auto debugCreateInfo = vk::DebugUtilsMessengerCreateInfoEXT{.flags = {},
                                                                    .messageSeverity = messageSeverityFlags,
                                                                    .messageType = messageTypeFlags,
                                                                    .pfnUserCallback = cVulkanDebugCallback,
                                                                    .pUserData = this};
  using namespace ranges;

  const auto validationLayersEnabled = !config.validationLayers.empty() && config.callback.has_value();
  if (validationLayersEnabled) {
    log(LogLevel::Info, VK_TAG, "Validation layers are enabled.");
    config.requiredWindowExtensions.emplace(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    config.requiredWindowExtensions.emplace("VK_EXT_debug_report");
    debugCallback = config.callback.value();
  }

  const auto extCStr =
      config.requiredWindowExtensions | views::transform([](auto &str) { return str.c_str(); }) | to_vector;
  const auto layerCStr =
      config.validationLayers | ranges::views::transform([](auto &str) { return str.c_str(); }) | to_vector;

  auto createInfo = vk::InstanceCreateInfo();
  createInfo.setPApplicationInfo(&appInfo).setPEnabledExtensionNames(extCStr).setPEnabledLayerNames(layerCStr).setPNext(
      validationLayersEnabled ? &debugCreateInfo : nullptr);

  vkInstance = vk::createInstanceUnique(createInfo);

  if (validationLayersEnabled) {
    debugMessenger = vkInstance->createDebugUtilsMessengerEXTUnique(
        debugCreateInfo, nullptr, vk::DispatchLoaderDynamic{*vkInstance, vkGetInstanceProcAddr});
  }
  log(LogLevel::Info, VK_TAG, "Vulkan instance created.");
}

const vk::Instance &Instance::getInstance() { return vkInstance.get(); }

std::optional<std::reference_wrapper<const vk::DebugUtilsMessengerEXT>> Instance::getDebugMessenger() {
  if (debugMessenger.has_value()) { return debugMessenger->get(); }
  return std::nullopt;
}

Instance::~Instance() {
  if (debugMessenger.has_value()) { debugMessenger->release(); }
  vkInstance.release();
}

void Instance::setDebugCallback(const VulkanDebugCallback &callback) { debugCallback = callback; }

void Instance::setVkInstance(vk::UniqueInstance &&instance) { vkInstance = std::move(instance); }

void Instance::setDebugMessenger(DynamicUniqueDebugUtilsMessengerEXT &&messenger) {
  debugMessenger = std::move(messenger);
}

VkBool32 Instance::cVulkanDebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT severity,
                                        VkDebugUtilsMessageTypeFlagsEXT msgTypeFlags,
                                        const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData, void *user_data) {
  auto self = reinterpret_cast<Instance *>(user_data);
  return self->debugCallback(DebugCallbackData::fromVk(*pCallbackData),
                             static_cast<vk::DebugUtilsMessageSeverityFlagBitsEXT>(severity),
                             static_cast<vk::DebugUtilsMessageTypeFlagsEXT>(msgTypeFlags))
      ? VK_TRUE
      : VK_FALSE;
}
std::string Instance::info() const { return "Vulkan instance unique"; }

const vk::Instance &Instance::operator*() const { return *vkInstance; }

vk::Instance const *Instance::operator->() const { return &*vkInstance; }

}// namespace pf::vulkan