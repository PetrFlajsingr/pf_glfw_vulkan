//
// Created by petr on 5/29/21.
//

#include "Window.h"
#include <fmt/format.h>
#include <pf_common/exceptions/StackTraceException.h>

namespace pf::ui {

std::ostream &operator<<(std::ostream &os, const Resolution &res) {
  os << fmt::format("{}x{}", res.width, res.height);
  return os;
}

Window::Window(const Resolution &resolution, Mode mode, const std::string &title)
    : resolution(resolution), mode(mode), title(title) {}

void Window::setResolution(Resolution newResolution) { resolution = newResolution; }

Resolution Window::getResolution() const { return resolution; }

void Window::setMode(Mode newMode) { mode = newMode; }

Mode Window::getMode() const { return mode; }

void Window::setTitle(std::string newTitle) { title = std::move(newTitle); }

std::string_view Window::getTitle() const { return title; }

}// namespace pf::ui