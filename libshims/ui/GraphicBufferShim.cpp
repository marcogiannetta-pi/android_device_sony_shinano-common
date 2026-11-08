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
#include <ui/GraphicBufferMapper.h>
#include <ui/Rect.h>
#include <utils/RefBase.h>
#include <new>

namespace android {

// ShimRef fits into the legacy 136-byte buffer allocated by libsomc_chokoballpal.
// Modern GraphicBuffer is 1784 bytes and overflows the 136-byte allocation.
class ShimRef : public RefBase {
public:
    sp<GraphicBuffer> mRealBuffer;
    virtual ~ShimRef() {
        mRealBuffer.clear();
    }
};

// Deprecated 7-argument GraphicBuffer constructor (32-bit inUsage)
extern "C" void _ZN7android13GraphicBufferC1EjjijjP13native_handleb(
        void* thisptr, uint32_t inWidth, uint32_t inHeight,
        PixelFormat inFormat, uint32_t inUsage, uint32_t inStride,
        native_handle_t* inHandle, bool keepOwnership) {
    ALOGI("GraphicBufferShim: C1 this=%p w=%u h=%u fmt=%d usage=0x%x stride=%u handle=%p keep=%d",
          thisptr, inWidth, inHeight, inFormat, inUsage, inStride, inHandle, keepOwnership);
    auto real = sp<GraphicBuffer>::make(
            inHandle, keepOwnership ? GraphicBuffer::TAKE_HANDLE : GraphicBuffer::WRAP_HANDLE,
            inWidth, inHeight, inFormat, 1, static_cast<uint64_t>(inUsage), inStride);
    ShimRef* shim = new (thisptr) ShimRef();
    shim->mRealBuffer = real;
}

// Inlined getNativeBuffer() out-of-line ABI export
extern "C" ANativeWindowBuffer* _ZNK7android13GraphicBuffer15getNativeBufferEv(const GraphicBuffer* buffer) {
    const ShimRef* shim = reinterpret_cast<const ShimRef*>(buffer);
    if (shim && shim->mRealBuffer != nullptr) {
        return static_cast<ANativeWindowBuffer*>(shim->mRealBuffer.get());
    }
    return nullptr;
}

// Inlined initCheck() out-of-line ABI export
extern "C" status_t _ZNK7android13GraphicBuffer9initCheckEv(const GraphicBuffer* buffer) {
    const ShimRef* shim = reinterpret_cast<const ShimRef*>(buffer);
    if (shim && shim->mRealBuffer != nullptr) {
        return shim->mRealBuffer->initCheck();
    }
    return android::OK;
}

// GraphicBufferMapper::unlock(buffer_handle_t) ABI shim for Android 14+
extern "C" status_t _ZN7android19GraphicBufferMapper6unlockEPK13native_handlePNS_4base14unique_fd_implINS4_13DefaultCloserEEE(
        void* thisptr, buffer_handle_t handle, void* outFence);

extern "C" status_t _ZN7android19GraphicBufferMapper6unlockEPK13native_handle(
        void* thisptr, buffer_handle_t handle) {
    return _ZN7android19GraphicBufferMapper6unlockEPK13native_handlePNS_4base14unique_fd_implINS4_13DefaultCloserEEE(
            thisptr, handle, nullptr);
}

// Permission shims for vendor camera HAL
extern "C" bool _ZN7android22checkCallingPermissionERKNS_8String16EPiS3_(
        const void* /*permission*/, int* outPid, int* outUid) {
    if (outPid) *outPid = 0;
    if (outUid) *outUid = 0;
    return true;
}

extern "C" bool _ZN7android15checkPermissionERKNS_8String16Eijb(
        const void* /*permission*/, pid_t /*pid*/, uid_t /*uid*/, bool /*doCheckPermission*/) {
    return true;
}

extern "C" bool _ZN7android15checkPermissionERKNS_8String16Eij(
        const void* /*permission*/, pid_t /*pid*/, uid_t /*uid*/) {
    return true;
}

} // namespace android
