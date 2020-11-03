cmake_minimum_required(VERSION 3.17)

include("cmake/HunterGate.cmake")

HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.269.tar.gz"
        SHA1 "64024b7b95b4c86d50ae05b926814448c93a70a0"
)


set(CPM_DOWNLOAD_LOCATION "${CMAKE_SOURCE_DIR}/cmake/CPM.cmake")
set(CPM_DOWNLOAD_VERSION 0.27.4)

if (NOT (EXISTS ${CPM_DOWNLOAD_LOCATION} AND CPM_VERSION STREQUAL CPM_DOWNLOAD_VERSION))
    message(STATUS "Downloading CPM.cmake")
    file(DOWNLOAD https://github.com/TheLartians/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake ${CPM_DOWNLOAD_LOCATION})
endif ()

include(${CPM_DOWNLOAD_LOCATION})

project(pf_glfw_vulkan
        VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
list(APPEND flags "-fconcepts" "-fconcepts-diagnostics-depth=10" "-Werror=return-type" "-fcoroutines"
        "-Wall" "-Wextra" "-Werror" "-Wpedantic" "-Wno-unknown-pragmas" "-Wno-unused-function"
        "-Wpointer-arith" "-Wcast-qual" "-Wno-type-limits")
if (CMAKE_BUILD_TYPE MATCHES Release)
    list(APPEND flags "-o3")
endif()

add_compile_definitions(GLFW_INCLUDE_VULKAN
        VULKAN_HPP_DEFAULT_DISPATCH_LOADER_DYNAMIC_STORAGE
        VULKAN_HPP_NO_NODISCARD_WARNINGS
        STB_IMAGE_IMPLEMENTATION)

find_package(Vulkan REQUIRED)
include_directories(${Vulkan_INCLUDE_DIRS})
set(VK_LAYER_PATH "/etc/vulkan/explicit_layer.d")
set(LD_LIBRARY_PATH "/usr/lib")
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

set(RANGE_V3_TESTS OFF)
set(SHADERC_SKIP_TESTS ON)
set(SPIRV_CROSS_ENABLE_TESTS OFF)

CPMAddPackage(
        NAME backward_cpp
        GITHUB_REPOSITORY bombela/backward-cpp
        GIT_TAG v1.5
)
CPMAddPackage(
        NAME pf_common
        GITHUB_REPOSITORY PetrFlajsingr/pf_common
        GIT_TAG master
)
CPMAddPackage(
        NAME cppcoro
        GITHUB_REPOSITORY dutow/cppcoro
        GIT_TAG 4b1951ff3c25fea78198a5c0aabb50589946b694
)
CPMAddPackage(
        NAME magic_enum
        GITHUB_REPOSITORY Neargye/magic_enum
        GIT_TAG v0.6.6
)
set(RANGE_V3_TESTS OFF)
CPMAddPackage(
        NAME range-v3
        GITHUB_REPOSITORY ericniebler/range-v3
        GIT_TAG 0.11.0
)
include_directories(${cppcoro_SOURCE_DIR}/include)


CPMAddPackage(
        NAME glslang
        GITHUB_REPOSITORY KhronosGroup/glslang
        GIT_TAG master-tot
)
CPMAddPackage(
        NAME spirvheaders
        GITHUB_REPOSITORY KhronosGroup/SPIRV-Headers
        GIT_TAG 1.5.3.reservations1
)
CPMAddPackage(
        NAME spirvtools
        GITHUB_REPOSITORY KhronosGroup/SPIRV-Tools
        GIT_TAG v2020.4
)
CPMAddPackage(
        NAME spirvcross
        GITHUB_REPOSITORY KhronosGroup/SPIRV-Cross
        GIT_TAG 2020-09-17
)
CPMAddPackage(
        NAME shaderc
        GITHUB_REPOSITORY google/shaderc
        GIT_TAG v2020.3
        OPTIONS
        "SHADERC_SKIP_INSTALL ON"
)


hunter_add_package(fmt)
find_package(fmt CONFIG REQUIRED)
hunter_add_package(stb)
find_package(stb CONFIG REQUIRED)

set(SOURCES
        src/pf_glfw_vulkan/concepts/Window.cpp
        src/pf_glfw_vulkan/ui/GlfwWindow.cpp
        src/pf_glfw_vulkan/ui/events/EventDispatchImpl.cpp
        src/pf_glfw_vulkan/vulkan/DefaultDeviceSuitabilityScorer.cpp
        src/pf_glfw_vulkan/vulkan/VulkanException.cpp
        src/pf_glfw_vulkan/vulkan/glsl/Compiler.cpp
        src/pf_glfw_vulkan/vulkan/types/Buffer.cpp
        src/pf_glfw_vulkan/vulkan/types/BufferView.cpp
        src/pf_glfw_vulkan/vulkan/types/CommandBuffer.cpp
        src/pf_glfw_vulkan/vulkan/types/CommandPool.cpp
        src/pf_glfw_vulkan/vulkan/types/DescriptorPool.cpp
        src/pf_glfw_vulkan/vulkan/types/DescriptorSetLayout.cpp
        src/pf_glfw_vulkan/vulkan/types/Fence.cpp
        src/pf_glfw_vulkan/vulkan/types/FrameBuffer.cpp
        src/pf_glfw_vulkan/vulkan/types/GraphicsPipeline.cpp
        src/pf_glfw_vulkan/vulkan/types/Image.cpp
        src/pf_glfw_vulkan/vulkan/types/ImageView.cpp
        src/pf_glfw_vulkan/vulkan/types/Instance.cpp
        src/pf_glfw_vulkan/vulkan/types/LogicalDevice.cpp
        src/pf_glfw_vulkan/vulkan/types/PhysicalDevice.cpp
        src/pf_glfw_vulkan/vulkan/types/RenderPass.cpp
        src/pf_glfw_vulkan/vulkan/types/Semaphore.cpp
        src/pf_glfw_vulkan/vulkan/types/Shader.cpp
        src/pf_glfw_vulkan/vulkan/types/Surface.cpp
        src/pf_glfw_vulkan/vulkan/types/SwapChain.cpp
        src/pf_glfw_vulkan/vulkan/types/Texture.cpp
        src/pf_glfw_vulkan/vulkan/types/TextureSampler.cpp
        src/pf_glfw_vulkan/vulkan/types/VulkanCommon.cpp
        src/pf_glfw_vulkan/vulkan/types/builders/GraphicsPipelineBuilder.cpp
        src/pf_glfw_vulkan/vulkan/types/builders/RenderPassBuilder.cpp
        )

set(INCLUDES
        src/pf_glfw_vulkan/concepts/Window.h
        src/pf_glfw_vulkan/ui/GlfwWindow.h
        src/pf_glfw_vulkan/ui/events/common.h
        src/pf_glfw_vulkan/ui/events/EventDispatchImpl.h
        src/pf_glfw_vulkan/vulkan/DefaultDeviceSuitabilityScorer.h
        src/pf_glfw_vulkan/vulkan/VulkanException.h
        src/pf_glfw_vulkan/vulkan/glsl/Compiler.h
        src/pf_glfw_vulkan/vulkan/types/Buffer.h
        src/pf_glfw_vulkan/vulkan/types/BufferView.h
        src/pf_glfw_vulkan/vulkan/types/CommandBuffer.h
        src/pf_glfw_vulkan/vulkan/types/CommandPool.h
        src/pf_glfw_vulkan/vulkan/types/DescriptorPool.h
        src/pf_glfw_vulkan/vulkan/types/DescriptorSetLayout.h
        src/pf_glfw_vulkan/vulkan/types/Fence.h
        src/pf_glfw_vulkan/vulkan/types/FrameBuffer.h
        src/pf_glfw_vulkan/vulkan/types/fwd.h
        src/pf_glfw_vulkan/vulkan/types/GraphicsPipeline.h
        src/pf_glfw_vulkan/vulkan/types/Image.h
        src/pf_glfw_vulkan/vulkan/types/ImageView.h
        src/pf_glfw_vulkan/vulkan/types/Instance.h
        src/pf_glfw_vulkan/vulkan/types/LogicalDevice.h
        src/pf_glfw_vulkan/vulkan/types/PhysicalDevice.h
        src/pf_glfw_vulkan/vulkan/types/RenderPass.h
        src/pf_glfw_vulkan/vulkan/types/Semaphore.h
        src/pf_glfw_vulkan/vulkan/types/Shader.h
        src/pf_glfw_vulkan/vulkan/types/Surface.h
        src/pf_glfw_vulkan/vulkan/types/SwapChain.h
        src/pf_glfw_vulkan/vulkan/types/Texture.h
        src/pf_glfw_vulkan/vulkan/types/TextureSampler.h
        src/pf_glfw_vulkan/vulkan/types.h
        src/pf_glfw_vulkan/vulkan/types/VulkanCommon.h
        src/pf_glfw_vulkan/vulkan/types/VulkanObject.h
        src/pf_glfw_vulkan/vulkan/types/builders/GraphicsPipelineBuilder.h
        src/pf_glfw_vulkan/vulkan/types/builders/RenderPassBuilder.h
        src/pf_glfw_vulkan/lib_config.h src/pf_glfw_vulkan/logging.h src/pf_glfw_vulkan/lib_config.cpp src/pf_glfw_vulkan/enums.h)


option(BUILD_SHARED_LIBS "build this library as shared")


SET(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "add a postfix, usually d on windows")
SET(CMAKE_RELEASE_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")
SET(CMAKE_RELWITHDEBINFO_POSTFIX "rd" CACHE STRING "add a postfix, usually empty on windows")
SET(CMAKE_MINSIZEREL_POSTFIX "s" CACHE STRING "add a postfix, usually empty on windows")

add_library(${PROJECT_NAME} ${SOURCES} ${INCLUDES} ${BACKWARD_ENABLE})
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
add_backward(${PROJECT_NAME})
target_compile_options(${PROJECT_NAME} PRIVATE ${flags})

include(GNUInstallDirs)

target_include_directories(${PROJECT_NAME} PUBLIC $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)

target_link_libraries(${PROJECT_NAME} PRIVATE pf_common::pf_common fmt::fmt magic_enum range-v3 ${GLFW_STATIC_LIBRARIES} ${Vulkan_LIBRARIES})
add_dependencies(${PROJECT_NAME} pf_common::pf_common fmt::fmt magic_enum range-v3 shaderc glslang)


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME ${PROJECT_NAME}/${PROJECT_NAME_LOWER}_export.h)

set_property(TARGET ${PROJECT_NAME} PROPERTY VERSION ${PROJECT_VERSION})
set_property(TARGET ${PROJECT_NAME} PROPERTY SOVERSION ${PROJECT_VERSION_MAJOR})
set_property(TARGET ${PROJECT_NAME} PROPERTY INTERFACE_${PROJECT_NAME}_MAJOR_VERSION ${PROJECT_VERSION_MAJOR})
set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY COMPATIBLE_INTERFACE_STRING ${PROJECT_NAME}_MAJOR_VERSION)


install(TARGETS ${PROJECT_NAME} pf_common magic_enum
        EXPORT ${PROJECT_NAME}Targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        )

install(
        FILES
        ${INCLUDES}
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME_LOWER}_export.h
        DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
        COMPONENT
        Devel
)

install(
        FILES
        ${GENERATED_INCLUDES}
        DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/Generated
        COMPONENT
        Devel
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}ConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
)

export(EXPORT ${PROJECT_NAME}Targets
        FILE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}Targets.cmake
        NAMESPACE ${PROJECT_NAME}::
        )

set(ConfigPackageLocation lib/cmake/${PROJECT_NAME})
install(EXPORT ${PROJECT_NAME}Targets
        FILE
        ${PROJECT_NAME}Targets.cmake
        NAMESPACE
        ${PROJECT_NAME}::
        DESTINATION
        ${ConfigPackageLocation}
        )

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}Config.cmake
        "include($" "{CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}Targets.cmake)"
        )

install(
        FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}Config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}ConfigVersion.cmake
        DESTINATION
        ${ConfigPackageLocation}
        COMPONENT
        Devel
)

