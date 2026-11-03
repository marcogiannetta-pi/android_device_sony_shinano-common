#!/bin/bash
# Script to automatically apply LineageOS 22.2 (Android 15) patches for Sony Shinano / MSM8974
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ANDROID_ROOT="$(cd "${SCRIPT_DIR}/../../../.." && pwd)"

echo "=== LineageOS 22.2 Patch Applier for Sony Shinano ==="
echo "Android Root: ${ANDROID_ROOT}"
echo "Patches Dir:  ${SCRIPT_DIR}"
echo ""

declare -A PATCH_MAP=(
    ["art"]="art"
    ["bionic"]="bionic"
    ["build_soong"]="build/soong"
    ["device_lineage_sepolicy"]="device/lineage/sepolicy"
    ["device_sony_common"]="device/sony/common"
    ["external_skia"]="external/skia"
    ["frameworks_av"]="frameworks/av"
    ["frameworks_base"]="frameworks/base"
    ["frameworks_native"]="frameworks/native"
    ["frameworks_opt_telephony"]="frameworks/opt/telephony"
    ["hardware_broadcom_fm"]="hardware/broadcom/fm"
    ["hardware_interfaces"]="hardware/interfaces"
    ["hardware_lineage_compat"]="hardware/lineage/compat"
    ["hardware_qcom-caf_msm8974_audio"]="hardware/qcom-caf/msm8974/audio"
    ["hardware_ril"]="hardware/ril"
    ["hardware_sony_thermanager"]="hardware/sony/thermanager"
    ["libcore"]="libcore"
    ["packages_apps_Camera2"]="packages/apps/Camera2"
    ["packages_apps_Settings"]="packages/apps/Settings"
    ["packages_modules_adb"]="packages/modules/adb"
    ["packages_modules_Bluetooth"]="packages/modules/Bluetooth"
    ["packages_modules_Connectivity"]="packages/modules/Connectivity"
    ["system_core"]="system/core"
    ["system_libhidl"]="system/libhidl"
    ["system_libvintf"]="system/libvintf"
    ["system_media"]="system/media"
    ["system_netd"]="system/netd"
    ["system_vold"]="system/vold"
)

for patch_dir in "${!PATCH_MAP[@]}"; do
    target_repo="${PATCH_MAP[$patch_dir]}"
    full_target="${ANDROID_ROOT}/${target_repo}"
    full_patch_dir="${SCRIPT_DIR}/${patch_dir}"

    if [ ! -d "${full_target}" ]; then
        echo "[SKIP] Target directory ${target_repo} does not exist."
        continue
    fi

    if [ ! -d "${full_patch_dir}" ]; then
        continue
    fi

    echo "--> Checking patches for ${target_repo}..."
    cd "${full_target}"

    for patch_file in "${full_patch_dir}"/*.patch; do
        [ -e "${patch_file}" ] || continue
        patch_name="$(basename "${patch_file}")"

        # Check if already applied via git apply --reverse --check
        if git apply --reverse --check "${patch_file}" >/dev/null 2>&1; then
            echo "    [ALREADY APPLIED] ${patch_name}"
        else
            echo "    [APPLYING] ${patch_name}"
            if git apply -v "${patch_file}"; then
                echo "    [SUCCESS] ${patch_name} applied via git apply"
            else
                echo "    [ERROR] Failed to apply ${patch_name}"
                exit 1
            fi
        fi
    done
done

echo ""
echo "=== All LineageOS 22.2 patches checked / applied successfully! ==="
