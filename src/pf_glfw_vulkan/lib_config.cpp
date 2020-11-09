//
// Created by petr on 11/3/20.
//

#include "lib_config.h"
#include "logging.h"
#include <utility>

void pf::vulkan::setGlobalLoggerInstance(std::shared_ptr<ILogger> logger) {
  logging::details::globalLogger = std::move(logger);
}
