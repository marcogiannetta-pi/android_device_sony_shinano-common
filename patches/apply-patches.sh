#!/bin/bash
# Script to automatically apply LineageOS 21.0 (Android 14) patches for Sony Shinano / MSM8974
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ANDROID_ROOT="$(cd "${SCRIPT_DIR}/../../../.." && pwd)"

echo "=== LineageOS 21.0 Patch Applier for Sony Shinano ==="
echo "Android Root: ${ANDROID_ROOT}"
echo "Patches Dir:  ${SCRIPT_DIR}"
echo ""

declare -A PATCH_MAP=(
    ["frameworks_av"]="frameworks/av"
    ["frameworks_native"]="frameworks/native"
    ["hardware_broadcom_fm"]="hardware/broadcom/fm"
    ["hardware_interfaces"]="hardware/interfaces"
    ["hardware_qcom-caf_msm8974_audio"]="hardware/qcom-caf/msm8974/audio"
    ["hardware_sony_thermanager"]="hardware/sony/thermanager"
    ["lineage-sdk"]="lineage-sdk"
    ["packages_apps_Settings"]="packages/apps/Settings"
    ["packages_apps_Trebuchet"]="packages/apps/Trebuchet"
    ["packages_modules_IntentResolver"]="packages/modules/IntentResolver"
    ["packages_providers_ContactsProvider"]="packages/providers/ContactsProvider"
    ["packages_services_Mms"]="packages/services/Mms"
    ["system_core"]="system/core"
    ["system_media"]="system/media"
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
echo "=== All LineageOS 21.0 patches checked / applied successfully! ==="
