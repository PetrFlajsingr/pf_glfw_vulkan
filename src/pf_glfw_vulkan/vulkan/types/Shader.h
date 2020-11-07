//
// Created by petr on 9/28/20.
//

#ifndef PF_GLFW_VULKAN_VULKAN_TYPES_SHADER_H
#define PF_GLFW_VULKAN_VULKAN_TYPES_SHADER_H

#include "VulkanObject.h"
#include "fwd.h"
#include <istream>
#include <pf_common/concepts/PtrConstructible.h>
#include <pf_glfw_vulkan/_export.h>
#include <pf_glfw_vulkan/vulkan/glsl/Compiler.h>
#include <vulkan/vulkan.hpp>
#include "configs/ShaderConfigs.h"

namespace pf::vulkan {

shaderc_shader_kind toShaderc(ShaderType type);

vk::ShaderStageFlagBits ShaderTypeToVk(ShaderType type);

class PF_GLFW_VULKAN_EXPORT Shader : public VulkanObject, public PtrConstructible<Shader> {
 public:
  explicit Shader(std::shared_ptr<LogicalDevice> device, const ShaderConfigFile &config);
  explicit Shader(std::shared_ptr<LogicalDevice> device, const ShaderConfigSrc &config);
  explicit Shader(std::shared_ptr<LogicalDevice> device, const ShaderConfigGlslSrc &config);
  explicit Shader(std::shared_ptr<LogicalDevice> device, const ShaderConfigGlslFile &config);

  Shader(const Shader &other) = delete;
  Shader &operator=(const Shader &other) = delete;

  [[nodiscard]] const vk::ShaderModule &getShaderModule();
  [[nodiscard]] ShaderType getType() const;
  [[nodiscard]] vk::ShaderStageFlagBits getVkType() const;
  [[nodiscard]] const std::string &getName() const;
  const vk::ShaderModule &operator*() const;

  vk::ShaderModule const *operator->() const;

  [[nodiscard]] std::string info() const override;

 private:
  std::shared_ptr<LogicalDevice> logicalDevice;
  vk::UniqueShaderModule vkShader;
  ShaderType type;
  std::string name;
};

std::vector<uint8_t> readSpvFile(std::ifstream &istream);
std::vector<uint8_t> readSpvFile(std::ifstream &&istream);

}// namespace pf::vulkan

#endif//PF_GLFW_VULKAN_VULKAN_TYPES_SHADER_H
