/*
 * Copyright (C) 2026 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <fcntl.h>
#include <linux/random.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main(void) {
    int fd = open("/dev/urandom", O_RDWR);
    if (fd >= 0) {
        char buf[512];
        int tfd = open("/proc/timer_list", O_RDONLY);
        if (tfd >= 0) {
            ssize_t n = read(tfd, buf, sizeof(buf));
            if (n > 0) {
                write(fd, buf, (size_t)n);
            }
            close(tfd);
        }
        int ent = 4096;
        ioctl(fd, RNDADDTOENTCNT, &ent);
        read(fd, buf, 64);
        close(fd);
    }
    return 0;
}
