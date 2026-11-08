/*
 * Copyright (C) 2026 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <sys/types.h>

extern "C" {

static char gDummySensorManager[256];

void* _ZN7android13SensorManager21getInstanceForPackageERKNS_8String16E(void* /*opPackageName*/) {
    return &gDummySensorManager[0];
}

void* _ZN7android13SensorManager16getDefaultSensorEi(void* /*thisptr*/, int /*type*/) {
    return nullptr;
}

ssize_t _ZN7android13SensorManager13getSensorListEPPKPKNS_6SensorE(void* /*thisptr*/, void const* const** list) {
    if (list) *list = nullptr;
    return 0;
}

void _ZN7android13SensorManager16createEventQueueENS_7String8Ei(
    void *sret, void * /*thisptr*/, void * /*pkgName*/, int /*mode*/) {
    void** sp = reinterpret_cast<void**>(sret);
    if (sp) *sp = nullptr;
}

void _ZN7android13SensorManager16createEventQueueENS_7String8EiNS_8String16E(
    void *sret, void * /*thisptr*/, void * /*pkgName*/, int /*mode*/, void * /*attrTag*/) {
    void** sp = reinterpret_cast<void**>(sret);
    if (sp) *sp = nullptr;
}

int32_t _ZNK7android16SensorEventQueue13disableSensorEPKNS_6SensorE(void* /*thisptr*/, void* /*sensor*/) {
    return 0;
}

int32_t _ZNK7android16SensorEventQueue12enableSensorEPKNS_6SensorE(void* /*thisptr*/, void* /*sensor*/) {
    return 0;
}

int32_t _ZNK7android16SensorEventQueue12setEventRateEPKNS_6SensorEx(void* /*thisptr*/, void* /*sensor*/, int64_t /*ns*/) {
    return 0;
}

int _ZNK7android16SensorEventQueue5getFdEv(void* /*thisptr*/) {
    return -1;
}

ssize_t _ZN7android16SensorEventQueue4readEP12ASensorEventj(void* /*thisptr*/, void* /*events*/, size_t /*numEvents*/) {
    return 0;
}

}
