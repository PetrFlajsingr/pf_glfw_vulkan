//
// Created by petr on 11/7/20.
//

#ifndef PF_GLFW_VULKAN_VULKAN_TYPES_CONFIGS_SHADERCONFIGS_H
#define PF_GLFW_VULKAN_VULKAN_TYPES_CONFIGS_SHADERCONFIGS_H

#include "../../glsl/Compiler.h"
#include <pf_glfw_vulkan/_export.h>
#include <string>
#include <vulkan/vulkan.hpp>

namespace pf::vulkan {

enum class ShaderType {
  Vertex,
  Fragment,
  Compute,
  Geometry,
  TessControl,
  TessEval,
  RayGen,
  AnyHit,
  ClosestHit,
  Miss,
  Intersection,
  Callable,
  Task,
  Mesg
};

struct PF_GLFW_VULKAN_EXPORT ShaderConfigFile {
  std::string name;
  ShaderType type;
  std::string path;
};

struct PF_GLFW_VULKAN_EXPORT ShaderConfigSrc {
  std::string name;
  ShaderType type;
  std::vector<uint8_t> data;
};

struct PF_GLFW_VULKAN_EXPORT ShaderConfigGlslFile {
  std::string name;
  ShaderType type;
  std::string path;
  glsl::MacroDefs macros;
  glsl::ReplaceMacroDefs replaceMacros = {};
  glsl::Optimization optimization = {};
};

struct PF_GLFW_VULKAN_EXPORT ShaderConfigGlslSrc {
  std::string name;
  ShaderType type;
  std::string src;
  glsl::MacroDefs macros;
  glsl::ReplaceMacroDefs replaceMacros = {};
  glsl::Optimization optimization = {};
};

}// namespace pf::vulkan

#endif//PF_GLFW_VULKAN_VULKAN_TYPES_CONFIGS_SHADERCONFIGS_H
