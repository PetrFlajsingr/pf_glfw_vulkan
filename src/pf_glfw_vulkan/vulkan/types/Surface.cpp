//
// Created by petr on 10/12/20.
//

#include "Surface.h"

namespace pf::vulkan {
Surface::Surface(std::shared_ptr<Instance> inst, std::shared_ptr<ui::Window> win)
    : instance(std::move(inst)), window(std::move(win)), vkSurface(window->createVulkanSurface(**instance)),
      windowSizeFnc([this] { return window->getResolution(); }) {}

const vk::SurfaceKHR &Surface::getSurface() { return vkSurface.get(); }

std::string Surface::info() const { return "Vulkan unique surface"; }

const vk::SurfaceKHR &Surface::operator*() const { return *vkSurface; }

vk::SurfaceKHR const *Surface::operator->() const { return &*vkSurface; }
Instance &Surface::getInstance() { return *instance; }
ui::Resolution Surface::getWindowSize() const { return windowSizeFnc(); }
ui::Window &Surface::getWindow() { return *window; }

}// namespace pf::vulkan