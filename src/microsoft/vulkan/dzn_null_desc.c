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

#include "dzn_null_desc.h"

#include <string.h>

void
dzn_null_desc_init(struct dzn_null_desc *desc,
                   bool writeable,
                   VkDescriptorType type)
{
   memset(desc, 0, sizeof(*desc));

   if (type == VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER ||
       type == VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC) {
      /* D3D12 CBVs don't support NULL resource; caller must patch in
       * a real BufferLocation pointing to a zero-filled buffer. */
      desc->kind = DZN_NULL_DESC_CBV;
      desc->cbv.SizeInBytes = D3D12_CONSTANT_BUFFER_DATA_PLACEMENT_ALIGNMENT;
   } else if (type == VK_DESCRIPTOR_TYPE_STORAGE_BUFFER ||
              type == VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC) {
      /* Storage buffers map to raw (byte address) buffers in D3D12 */
      if (writeable) {
         desc->kind = DZN_NULL_DESC_UAV;
         desc->uav.Format = DXGI_FORMAT_R32_TYPELESS;
         desc->uav.ViewDimension = D3D12_UAV_DIMENSION_BUFFER;
         desc->uav.Buffer.Flags = D3D12_BUFFER_UAV_FLAG_RAW;
      } else {
         desc->kind = DZN_NULL_DESC_SRV;
         desc->srv.Format = DXGI_FORMAT_R32_TYPELESS;
         desc->srv.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
         desc->srv.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
         desc->srv.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_RAW;
      }
   } else if (type == VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER ||
              type == VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER) {
      /* Texel buffers are typed buffers */
      if (writeable) {
         desc->kind = DZN_NULL_DESC_UAV;
         desc->uav.Format = DXGI_FORMAT_R32_UINT;
         desc->uav.ViewDimension = D3D12_UAV_DIMENSION_BUFFER;
      } else {
         desc->kind = DZN_NULL_DESC_SRV;
         desc->srv.Format = DXGI_FORMAT_R32_UINT;
         desc->srv.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
         desc->srv.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
      }
   } else {
      /* Image descriptors (SAMPLED_IMAGE, STORAGE_IMAGE, etc.) */
      if (writeable) {
         desc->kind = DZN_NULL_DESC_UAV;
         desc->uav.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
         desc->uav.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE2D;
      } else {
         desc->kind = DZN_NULL_DESC_SRV;
         desc->srv.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
         desc->srv.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
         desc->srv.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
      }
   }
}
