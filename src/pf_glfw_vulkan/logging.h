//
// Created by petr on 11/3/20.
//

#ifndef PF_GLFW_VULKAN_SRC_PF_GLFW_VULKAN_LOGGING_H
#define PF_GLFW_VULKAN_SRC_PF_GLFW_VULKAN_LOGGING_H

#include "lib_config.h"

namespace pf::vulkan {
namespace details {
inline std::shared_ptr<ILogger> globalLogger = std::make_shared<EmptyLogger>();
}

constexpr auto VK_TAG = "vulkan";

inline void log(LogLevel level, std::string_view tag, std::string_view msg) {
  details::globalLogger->log(level, tag, msg);
}
inline void logt(std::string_view tag, std::string_view msg) {
  log(LogLevel::Trace, tag, msg);
}
inline void logi(std::string_view tag, std::string_view msg) {
  log(LogLevel::Info, tag, msg);
}
inline void logd(std::string_view tag, std::string_view msg) {
  log(LogLevel::Debug, tag, msg);
}
inline void logw(std::string_view tag, std::string_view msg) {
  log(LogLevel::Warn, tag, msg);
}
inline void logc(std::string_view tag, std::string_view msg) {
  log(LogLevel::Critical, tag, msg);
}
inline void loge(std::string_view tag, std::string_view msg) {
  log(LogLevel::Err, tag, msg);
}


void logFmt(LogLevel level, std::string_view tag, std::string_view msg,
            const auto &... args) {
  details::globalLogger->logFmt(level, tag, msg, args...);
}

void logtFmt(std::string_view tag, std::string_view msg, const auto &...args) {
  logFmt(LogLevel::Trace, tag, msg, args...);
}
void logiFmt(std::string_view tag, std::string_view msg, const auto &...args) {
  logFmt(LogLevel::Info, tag, msg, args...);
}
void logdFmt(std::string_view tag, std::string_view msg, const auto &...args) {
  logFmt(LogLevel::Debug, tag, msg, args...);
}
void logwFmt(std::string_view tag, std::string_view msg, const auto &...args) {
  logFmt(LogLevel::Warn, tag, msg, args...);
}
void logcFmt(std::string_view tag, std::string_view msg, const auto &...args) {
  logFmt(LogLevel::Critical, tag, msg, args...);
}
void logeFmt(std::string_view tag, std::string_view msg, const auto &...args) {
  logFmt(LogLevel::Err, tag, msg, args...);
}
}

#endif//PF_GLFW_VULKAN_SRC_PF_GLFW_VULKAN_LOGGING_H
