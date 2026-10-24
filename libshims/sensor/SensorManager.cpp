/*
 * Copyright (C) 2026 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

extern "C" {

void _ZN7android8String16C1EPKc(void *str16, const char *s);
void _ZN7android8String16D1Ev(void *str16);
void _ZN7android13SensorManager16createEventQueueENS_7String8EiNS_8String16E(
    void *sret, void *thisptr, void *pkgName, int mode, void *attrTag);

void _ZN7android13SensorManager16createEventQueueENS_7String8Ei(
    void *sret, void *thisptr, void *pkgName, int mode) {
    void *attrTag[2] = {nullptr, nullptr};
    _ZN7android8String16C1EPKc(attrTag, "");
    _ZN7android13SensorManager16createEventQueueENS_7String8EiNS_8String16E(
        sret, thisptr, pkgName, mode, attrTag);
    _ZN7android8String16D1Ev(attrTag);
}

}
