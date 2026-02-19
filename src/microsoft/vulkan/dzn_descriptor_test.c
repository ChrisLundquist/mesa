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

#undef NDEBUG
#include <assert.h>

static void
test_uniform_buffer(void)
{
   struct dzn_null_desc desc;

   dzn_null_desc_init(&desc, false, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER);
   assert(desc.kind == DZN_NULL_DESC_CBV);
   assert(desc.cbv.SizeInBytes == D3D12_CONSTANT_BUFFER_DATA_PLACEMENT_ALIGNMENT);
   assert(desc.cbv.BufferLocation == 0);

   dzn_null_desc_init(&desc, false, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC);
   assert(desc.kind == DZN_NULL_DESC_CBV);
   assert(desc.cbv.SizeInBytes == D3D12_CONSTANT_BUFFER_DATA_PLACEMENT_ALIGNMENT);

   /* writeable flag is ignored for uniform buffers */
   dzn_null_desc_init(&desc, true, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER);
   assert(desc.kind == DZN_NULL_DESC_CBV);
   assert(desc.cbv.SizeInBytes == D3D12_CONSTANT_BUFFER_DATA_PLACEMENT_ALIGNMENT);
}

static void
test_storage_buffer_writeable(void)
{
   struct dzn_null_desc desc;

   dzn_null_desc_init(&desc, true, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER);
   assert(desc.kind == DZN_NULL_DESC_UAV);
   assert(desc.uav.Format == DXGI_FORMAT_R32_TYPELESS);
   assert(desc.uav.ViewDimension == D3D12_UAV_DIMENSION_BUFFER);
   assert(desc.uav.Buffer.Flags == D3D12_BUFFER_UAV_FLAG_RAW);
   assert(desc.uav.Buffer.FirstElement == 0);
   assert(desc.uav.Buffer.NumElements == 0);

   dzn_null_desc_init(&desc, true, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC);
   assert(desc.kind == DZN_NULL_DESC_UAV);
   assert(desc.uav.Format == DXGI_FORMAT_R32_TYPELESS);
   assert(desc.uav.Buffer.Flags == D3D12_BUFFER_UAV_FLAG_RAW);
}

static void
test_storage_buffer_readonly(void)
{
   struct dzn_null_desc desc;

   dzn_null_desc_init(&desc, false, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER);
   assert(desc.kind == DZN_NULL_DESC_SRV);
   assert(desc.srv.Format == DXGI_FORMAT_R32_TYPELESS);
   assert(desc.srv.ViewDimension == D3D12_SRV_DIMENSION_BUFFER);
   assert(desc.srv.Shader4ComponentMapping == D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING);
   assert(desc.srv.Buffer.Flags == D3D12_BUFFER_SRV_FLAG_RAW);
   assert(desc.srv.Buffer.FirstElement == 0);
   assert(desc.srv.Buffer.NumElements == 0);

   dzn_null_desc_init(&desc, false, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC);
   assert(desc.kind == DZN_NULL_DESC_SRV);
   assert(desc.srv.Format == DXGI_FORMAT_R32_TYPELESS);
   assert(desc.srv.Buffer.Flags == D3D12_BUFFER_SRV_FLAG_RAW);
}

static void
test_texel_buffer_writeable(void)
{
   struct dzn_null_desc desc;

   dzn_null_desc_init(&desc, true, VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER);
   assert(desc.kind == DZN_NULL_DESC_UAV);
   assert(desc.uav.Format == DXGI_FORMAT_R32_UINT);
   assert(desc.uav.ViewDimension == D3D12_UAV_DIMENSION_BUFFER);
   assert(desc.uav.Buffer.Flags == 0);

   dzn_null_desc_init(&desc, true, VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER);
   assert(desc.kind == DZN_NULL_DESC_UAV);
   assert(desc.uav.Format == DXGI_FORMAT_R32_UINT);
   assert(desc.uav.ViewDimension == D3D12_UAV_DIMENSION_BUFFER);
}

static void
test_texel_buffer_readonly(void)
{
   struct dzn_null_desc desc;

   dzn_null_desc_init(&desc, false, VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER);
   assert(desc.kind == DZN_NULL_DESC_SRV);
   assert(desc.srv.Format == DXGI_FORMAT_R32_UINT);
   assert(desc.srv.ViewDimension == D3D12_SRV_DIMENSION_BUFFER);
   assert(desc.srv.Shader4ComponentMapping == D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING);
   assert(desc.srv.Buffer.Flags == 0);

   dzn_null_desc_init(&desc, false, VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER);
   assert(desc.kind == DZN_NULL_DESC_SRV);
   assert(desc.srv.Format == DXGI_FORMAT_R32_UINT);
   assert(desc.srv.ViewDimension == D3D12_SRV_DIMENSION_BUFFER);
}

static void
test_image_writeable(void)
{
   struct dzn_null_desc desc;

   dzn_null_desc_init(&desc, true, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE);
   assert(desc.kind == DZN_NULL_DESC_UAV);
   assert(desc.uav.Format == DXGI_FORMAT_R8G8B8A8_UNORM);
   assert(desc.uav.ViewDimension == D3D12_UAV_DIMENSION_TEXTURE2D);
}

static void
test_image_readonly(void)
{
   struct dzn_null_desc desc;

   dzn_null_desc_init(&desc, false, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE);
   assert(desc.kind == DZN_NULL_DESC_SRV);
   assert(desc.srv.Format == DXGI_FORMAT_R8G8B8A8_UNORM);
   assert(desc.srv.ViewDimension == D3D12_SRV_DIMENSION_TEXTURE2D);
   assert(desc.srv.Shader4ComponentMapping == D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING);

   dzn_null_desc_init(&desc, false, VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT);
   assert(desc.kind == DZN_NULL_DESC_SRV);
   assert(desc.srv.Format == DXGI_FORMAT_R8G8B8A8_UNORM);
   assert(desc.srv.ViewDimension == D3D12_SRV_DIMENSION_TEXTURE2D);

   dzn_null_desc_init(&desc, false, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER);
   assert(desc.kind == DZN_NULL_DESC_SRV);
   assert(desc.srv.Format == DXGI_FORMAT_R8G8B8A8_UNORM);
   assert(desc.srv.ViewDimension == D3D12_SRV_DIMENSION_TEXTURE2D);
}

int
main(void)
{
   test_uniform_buffer();
   test_storage_buffer_writeable();
   test_storage_buffer_readonly();
   test_texel_buffer_writeable();
   test_texel_buffer_readonly();
   test_image_writeable();
   test_image_readonly();
   return 0;
}
