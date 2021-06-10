//
// Created by petr on 10/16/20.
//

#ifndef PF_GLFW_VULKAN_VULKAN_TYPES_FWD_H
#define PF_GLFW_VULKAN_VULKAN_TYPES_FWD_H

namespace pf::vulkan {
class CommandPool;
class CommandBuffer;
class DescriptorSetLayout;
class PhysicalDevice;
class LogicalDevice;
class FrameBuffer;
class GraphicsPipeline;
class Image;
class ImageRef;
class ImageUnique;
class ImageView;
class Instance;
class RenderPass;
class Shader;
class Surface;
class SwapChain;
class Buffer;
class BufferView;
class BufferMemoryPool;
class DescriptorPool;
class Semaphore;
class Fence;
class Texture;
class TextureSampler;

class RenderPassBuilder;
class GraphicsPipelineBuilder;
}// namespace pf::vulkan

#endif//PF_GLFW_VULKAN_VULKAN_TYPES_FWD_H
