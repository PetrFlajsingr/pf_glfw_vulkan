//
// Created by petr on 11/3/20.
//

#ifndef PF_GLFW_VULKAN_LIB_CONFIG_H
#define PF_GLFW_VULKAN_LIB_CONFIG_H

#include <memory>
#include <pf_common/ILogger.h>
#include <pf_glfw_vulkan/_export.h>

namespace pf::vulkan {
PF_GLFW_VULKAN_EXPORT void setGlobalLoggerInstance(std::shared_ptr<ILogger> logger);
}

#endif//PF_GLFW_VULKAN_LIB_CONFIG_H
