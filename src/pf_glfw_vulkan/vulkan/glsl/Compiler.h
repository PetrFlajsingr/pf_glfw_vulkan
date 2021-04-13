//
// Created by petr on 10/18/20.
//

#ifndef PF_GLFW_VULKAN_VULKAN_GLSL_COMPILER_H
#define PF_GLFW_VULKAN_VULKAN_GLSL_COMPILER_H

#include <pf_common/exceptions/StackTraceException.h>
#include <pf_glfw_vulkan/_export.h>
#include <pf_glfw_vulkan/logging.h>
#include <shaderc/shaderc.hpp>
#include <string>
#include <utility>

namespace pf::glsl {

using MacroDefs = std::vector<std::string>;
using ReplaceMacroDefs = std::vector<std::pair<std::string, std::string>>;
using BinaryData = std::vector<uint32_t>;
enum class CompilationStep { None, Preprocessed, Assembly, Binary };

enum class Optimization { None, Size, Performance };

class CompilationException : public StackTraceException {
 public:
  explicit CompilationException(const std::string_view &message);

  static CompilationException fmt(std::string_view fmt, auto &&...args) {
    return CompilationException(fmt::format(fmt, args...));
  }
};

class PF_GLFW_VULKAN_EXPORT Compiler {
 public:
  Compiler(std::string srcName, std::string src, shaderc_shader_kind type, const MacroDefs &macros = {},
           const ReplaceMacroDefs &replaceMacros = {});

  std::string preprocess();
  [[nodiscard]] std::string toAssembly(Optimization optimization = Optimization::None);
  [[nodiscard]] BinaryData toBinary(Optimization optimization = Optimization::None);
  [[nodiscard]] BinaryData compile(Optimization optimization = Optimization::None);

 private:
  template<typename T>
  void checkCompilationResult(const shaderc::CompilationResult<T> &compilationResult) {
    constexpr auto LOG_TAG = "GLSL_COMPILE";
    if (compilationResult.GetNumErrors() > 0) {
      const auto message = fmt::format("Shader '{}' failed to compile due following errors:\n{}", name,
                                       compilationResult.GetErrorMessage());
      vulkan::logging::loge(LOG_TAG, message);
      throw CompilationException(message);
    } else if (compilationResult.GetNumWarnings() > 0) {
      const auto message =
          fmt::format("Shader '{}' compiled with following warnings:\n{}", name, compilationResult.GetErrorMessage());
      vulkan::logging::logw(LOG_TAG, message);
    }
  }

  shaderc::Compiler compiler;
  shaderc::CompileOptions options;
  std::string name;
  std::string source;
  shaderc_shader_kind kind;
  MacroDefs macros;
  CompilationStep currentStep = CompilationStep::None;
  BinaryData binaryData;
};

}// namespace pf::glsl
#endif//PF_GLFW_VULKAN_VULKAN_GLSL_COMPILER_H
