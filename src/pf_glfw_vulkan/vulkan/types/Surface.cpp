//
// Created by petr on 10/12/20.
//

#include "Surface.h"

namespace pf::vulkan {
Surface::Surface(std::shared_ptr<Instance> inst, ui::Window &window)
    : instance(std::move(inst)), vkSurface(window.createVulkanSurface(**instance)),
      windowSizeFnc([&window] { return window.getResolution(); }) {}

const vk::SurfaceKHR &Surface::getSurface() { return vkSurface.get(); }

std::string Surface::info() const { return "Vulkan unique surface"; }

const vk::SurfaceKHR &Surface::operator*() const { return *vkSurface; }

vk::SurfaceKHR const *Surface::operator->() const { return &*vkSurface; }
Instance &Surface::getInstance() { return *instance; }
ui::Resolution Surface::getWindowSize() const { return windowSizeFnc(); }

}// namespace pf::vulkan