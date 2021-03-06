//
// Created by petr on 9/26/20.
//

#ifndef PF_GLFW_VULKAN_VULKAN_TYPES_PHYSICALDEVICE_H
#define PF_GLFW_VULKAN_VULKAN_TYPES_PHYSICALDEVICE_H

#include "../DefaultDeviceSuitabilityScorer.h"
#include "../VulkanException.h"
#include "VulkanObject.h"
#include "configs/LogicalDeviceConfig.h"
#include "fwd.h"
#include <pf_common/concepts/PtrConstructible.h>
#include <pf_glfw_vulkan/_export.h>
#include <pf_glfw_vulkan/logging.h>
#include <range/v3/action/sort.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/transform.hpp>
#include <unordered_set>
#include <vulkan/vulkan.hpp>

namespace pf::vulkan {

namespace details {
std::unordered_map<vk::QueueFlagBits, uint32_t> getQueueFamilyIndices(vk::PhysicalDevice &physicalDevice,
                                                                      std::unordered_set<vk::QueueFlagBits> queueTypes);

uint32_t getPresentQueueFamilyIndex(vk::PhysicalDevice &physicalDevice, const vk::SurfaceKHR &surface);
// TODO: counts
std::vector<vk::DeviceQueueCreateInfo> buildQueueCreateInfo(const std::unordered_set<uint32_t> &queueIndices,
                                                            std::vector<float> &queuePriorities);
}// namespace details

class PF_GLFW_VULKAN_EXPORT PhysicalDevice : public VulkanObject,
                                             public PtrConstructible<PhysicalDevice>,
                                             public std::enable_shared_from_this<PhysicalDevice> {
 public:
  template<DeviceSuitabilityScorer DeviceScorer>
  explicit PhysicalDevice(std::shared_ptr<Instance> instance, DeviceScorer &&scorer)
      : instance(std::move(instance)), vkDevice(selectPhysicalDevice(getPhysicalDevices(), scorer)) {}

  PhysicalDevice(const PhysicalDevice &) = delete;
  PhysicalDevice &operator=(const PhysicalDevice &) = delete;

  [[nodiscard]] const vk::PhysicalDevice &getPhysicalDevice();

  const vk::PhysicalDevice &operator*() const;
  vk::PhysicalDevice const *operator->() const;

  [[nodiscard]] LogicalDevice &getLogicalDevice(const std::string &id);

  std::string info() const override;

  [[nodiscard]] std::shared_ptr<LogicalDevice> &createLogicalDevice(LogicalDeviceConfig config);

  [[nodiscard]] Instance &getInstance() const;

 private:
  std::vector<vk::PhysicalDevice> getPhysicalDevices();

  template<DeviceSuitabilityScorer DeviceScorer>
  static vk::PhysicalDevice selectPhysicalDevice(const std::vector<vk::PhysicalDevice> &physicalDevices,
                                                 DeviceScorer &&device_scorer);

  std::shared_ptr<Instance> instance;
  vk::PhysicalDevice vkDevice;
  std::unordered_map<std::string, std::shared_ptr<LogicalDevice>> logicalDevices;
};

template<DeviceSuitabilityScorer DeviceScorer>
vk::PhysicalDevice PhysicalDevice::selectPhysicalDevice(const std::vector<vk::PhysicalDevice> &physicalDevices,
                                                        DeviceScorer &&device_scorer) {
  using namespace ranges;
  using namespace logging;
  logi(VK_TAG, "Selecting physical device.");
  const auto suitableDevices =
      physicalDevices | views::transform([&](const auto &device) {
        const auto deviceName = device.getProperties().deviceName;
        const auto score = device_scorer(device);
        logi(VK_TAG, "Device name: {}, score: {}", deviceName, score.has_value() ? *score : -1);
        return std::make_pair(score, device);
      })
      | views::filter([](const auto &scored_device) { return scored_device.first.has_value(); }) | to_vector
      | actions::sort([](const auto &dev_a, const auto &dev_b) { return dev_a.first.value() > dev_b.first.value(); });
  if (suitableDevices.empty()) { throw VulkanException("No suitable physical device was found."); }
  const auto selectedDevice = suitableDevices.front().second;
  const auto deviceName = selectedDevice.getProperties().deviceName;
  const auto score = suitableDevices.front().first.value();
  logi(VK_TAG, "Selected device: Device name: {}, score: {}", deviceName, score);
  return selectedDevice;
}

}// namespace pf::vulkan

#endif//PF_GLFW_VULKAN_VULKAN_TYPES_PHYSICALDEVICE_H
