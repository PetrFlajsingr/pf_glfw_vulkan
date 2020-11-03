//
// Created by petr on 11/3/20.
//

#include "lib_config.h"

#include <utility>
#include "logging.h"

void pf::vulkan::setGlobalLoggerInstance(std::shared_ptr<ILogger> logger) {
  details::globalLogger = std::move(logger);
}
