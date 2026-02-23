/*
 * Copyright © Microsoft Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef DZN_NULL_DESC_H
#define DZN_NULL_DESC_H

#define D3D12_IGNORE_SDK_LAYERS
#include <unknwn.h>
#include <directx/d3d12.h>

#include <vulkan/vulkan_core.h>
#include <stdbool.h>

enum dzn_null_desc_kind {
   DZN_NULL_DESC_CBV,
   DZN_NULL_DESC_SRV,
   DZN_NULL_DESC_UAV,
};

struct dzn_null_desc {
   enum dzn_null_desc_kind kind;
   union {
      D3D12_CONSTANT_BUFFER_VIEW_DESC cbv;
      D3D12_SHADER_RESOURCE_VIEW_DESC srv;
      D3D12_UNORDERED_ACCESS_VIEW_DESC uav;
   };
};

void
dzn_null_desc_init(struct dzn_null_desc *desc,
                   bool writeable,
                   VkDescriptorType type);

#endif /* DZN_NULL_DESC_H */
