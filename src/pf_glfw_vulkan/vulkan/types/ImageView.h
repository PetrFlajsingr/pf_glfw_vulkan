//
// Created by petr on 9/27/20.
//

#ifndef PF_GLFW_VULKAN_VULKAN_TYPES_IMAGEVIEW_H
#define PF_GLFW_VULKAN_VULKAN_TYPES_IMAGEVIEW_H

#include "VulkanObject.h"
#include "configs/ImageViewConfig.h"
#include "fwd.h"
#include <pf_common/concepts/PtrConstructible.h>
#include <pf_glfw_vulkan/_export.h>
#include <vulkan/vulkan.hpp>

namespace pf::vulkan {

class PF_GLFW_VULKAN_EXPORT ImageView : public VulkanObject, public PtrConstructible<ImageView> {
 public:
  explicit ImageView(std::shared_ptr<Image> img, const ImageViewConfig &config);

  ImageView(const ImageView &other) = delete;
  ImageView &operator=(const ImageView &other) = delete;

  [[nodiscard]] const vk::ImageView &getImageView();

  const vk::ImageView &operator*() const;
  vk::ImageView const *operator->() const;

  [[nodiscard]] vk::Format getFormat() const;
  [[nodiscard]] vk::ColorSpaceKHR getColorSpace() const;
  [[nodiscard]] vk::ImageViewType getViewType() const;
  [[nodiscard]] const vk::ImageSubresourceRange &getSubresourceRange() const;

  [[nodiscard]] std::string info() const override;

 private:
  std::shared_ptr<Image> image;
  vk::UniqueImageView vkImageView;
  vk::Format format;
  vk::ColorSpaceKHR colorSpace;
  vk::ImageViewType viewType;
  vk::ImageSubresourceRange subresourceRange;
};

}// namespace pf::vulkan

#endif//PF_GLFW_VULKAN_VULKAN_TYPES_IMAGEVIEW_H
