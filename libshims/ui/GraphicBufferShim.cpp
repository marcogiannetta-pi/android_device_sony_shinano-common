/*
 * Copyright (C) 2026 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <ui/GraphicBuffer.h>
#include <new>

namespace android {

// Deprecated 7-argument GraphicBuffer constructor (32-bit inUsage)
extern "C" void _ZN7android13GraphicBufferC1EjjijjP13native_handleb(
        void* thisptr, uint32_t inWidth, uint32_t inHeight,
        PixelFormat inFormat, uint32_t inUsage, uint32_t inStride,
        native_handle_t* inHandle, bool keepOwnership) {
    new (thisptr) GraphicBuffer(inHandle, keepOwnership ? GraphicBuffer::TAKE_HANDLE : GraphicBuffer::WRAP_HANDLE,
                                inWidth, inHeight, inFormat, 1, static_cast<uint64_t>(inUsage), inStride);
}

// Inlined getNativeBuffer() out-of-line ABI export
extern "C" ANativeWindowBuffer* _ZNK7android13GraphicBuffer15getNativeBufferEv(const GraphicBuffer* buffer) {
    return static_cast<ANativeWindowBuffer*>(const_cast<GraphicBuffer*>(buffer));
}

// Inlined initCheck() out-of-line ABI export
extern "C" status_t _ZNK7android13GraphicBuffer9initCheckEv(const GraphicBuffer* buffer) {
    return buffer->initCheck();
}

} // namespace android
