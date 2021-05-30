//
// Created by petr on 5/29/21.
//

#ifndef PF_GLFW_VULKAN_SRC_PF_GLFW_VULKAN_UI_RESOLUTION_H
#define PF_GLFW_VULKAN_SRC_PF_GLFW_VULKAN_UI_RESOLUTION_H

#include <cstddef>
#include <pf_glfw_vulkan/_export.h>

namespace pf::ui {
struct PF_GLFW_VULKAN_EXPORT Resolution {
  std::size_t width;
  std::size_t height;
  [[nodiscard]] inline double aspectRatio() const { return static_cast<double>(width) / height; }
};
}// namespace pf::ui

#endif//PF_GLFW_VULKAN_SRC_PF_GLFW_VULKAN_UI_RESOLUTION_H
