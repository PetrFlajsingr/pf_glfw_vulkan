//
// Created by petr on 9/24/20.
//

#ifndef PF_GLFW_VULKAN_UI_EVENTS_COMMON_H
#define PF_GLFW_VULKAN_UI_EVENTS_COMMON_H

#include <functional>
#include <magic_enum.hpp>
#include <pf_glfw_vulkan/_export.h>
#include <string>
#include <utility>

namespace pf::events {

enum class MouseButton { Left, Right, Middle, None };
constexpr unsigned int mouseButtonCount = 3;
enum class MouseButtonState { Pressed, Released };

enum class MouseEventType { Down, Up, Click, DblClick, Move, Wheel };
constexpr std::size_t MouseEventTypeCount = magic_enum::enum_count<MouseEventType>();

enum class KeyEventType { Up, Pressed, Repeat };
constexpr std::size_t KeyboardEventTypeCount = magic_enum::enum_count<KeyEventType>();

struct PF_GLFW_VULKAN_EXPORT KeyEvent {
  KeyEventType type;
  char key;
};

struct PF_GLFW_VULKAN_EXPORT TextEvent {
  std::string text;
};

struct PF_GLFW_VULKAN_EXPORT MouseEvent {
  MouseEventType type;
  MouseButton button;
  std::pair<double, double> location;
  std::pair<double, double> delta;
};

namespace details {
using MouseEventFnc = std::function<bool(MouseEvent)>;
using KeyEventFnc = std::function<bool(KeyEvent)>;
using TextEventFnc = std::function<bool(TextEvent)>;
}// namespace details

template<typename F>
concept MouseEventListener = std::invocable<F, MouseEvent> && std::same_as < std::invoke_result_t<F, MouseEvent>,
bool > ;
template<typename F>
concept KeyEventListener = std::invocable<F, KeyEvent> && std::same_as < std::invoke_result_t<F, KeyEvent>,
bool > ;
template<typename F>
concept TextEventListener = std::invocable<F, TextEvent> && std::same_as < std::invoke_result_t<F, TextEvent>,
bool > ;
template<typename F>
concept InputIgnorePredicate = std::invocable<F> && std::same_as < std::invoke_result_t<F>,
bool > ;

}// namespace pf::events

#endif//PF_GLFW_VULKAN_UI_EVENTS_COMMON_H
