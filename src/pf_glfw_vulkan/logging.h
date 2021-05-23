//
// Created by petr on 11/3/20.
//

#ifndef PF_GLFW_VULKAN_LOGGING_H
#define PF_GLFW_VULKAN_LOGGING_H

#include "lib_config.h"

namespace pf::vulkan::logging {
namespace details {
inline std::shared_ptr<ILogger> globalLogger = std::make_shared<EmptyLogger>();
}

constexpr auto VK_TAG = "vulkan";

inline void log(LogLevel level, std::string_view tag, std::string_view msg, const auto &...args) {
  details::globalLogger->log(level, tag, fmt::format(msg, args...));
}
inline void logt(std::string_view tag, std::string_view msg, const auto &...args) {
  log(LogLevel::Trace, tag, msg, args...);
}
inline void logi(std::string_view tag, std::string_view msg, const auto &...args) {
  log(LogLevel::Info, tag, msg, args...);
}
inline void logd(std::string_view tag, std::string_view msg, const auto &...args) {
  log(LogLevel::Debug, tag, msg, args...);
}
inline void logw(std::string_view tag, std::string_view msg, const auto &...args) {
  log(LogLevel::Warn, tag, msg, args...);
}
inline void logc(std::string_view tag, std::string_view msg, const auto &...args) {
  log(LogLevel::Critical, tag, msg, args...);
}
inline void loge(std::string_view tag, std::string_view msg, const auto &...args) {
  log(LogLevel::Err, tag, msg, args...);
}

}// namespace pf::vulkan::logging

#endif//PF_GLFW_VULKAN_LOGGING_H
