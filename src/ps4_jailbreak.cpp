//
// PS4 Jailbreak / Sandbox Escape wrapper for pplay
//

#include "ps4_jailbreak.h"

#ifdef __PS4__

extern "C" {
#include "jailbreak.h"
#include "utils.h"
}

#include <stdio.h>

static bool jailbreak_initialized = false;

int ps4_jailbreak_init(void) {
    if (jailbreak_initialized) {
        printf("[PS4-JB] Jailbreak already initialized
");
        return 0;
    }

    printf("[PS4-JB] Initializing jailbreak and escaping sandbox...
");

    // Get current credentials
    struct jbc_cred cred;
    if (jbc_get_cred(&cred) != 0) {
        printf("[PS4-JB] ERROR: Failed to get credentials
");
        return -1;
    }

    printf("[PS4-JB] Current UID: %d, Prison: 0x%lx
", cred.uid, cred.prison);

    // Create root credentials (jailbreak)
    struct jbc_cred root_cred;
    if (jbc_jailbreak_cred(&root_cred) != 0) {
        printf("[PS4-JB] ERROR: Failed to create root credentials
");
        return -1;
    }

    printf("[PS4-JB] Root credentials created
");
    printf("[PS4-JB] - Prison0: 0x%lx
", root_cred.prison);
    printf("[PS4-JB] - Root vnode: 0x%lx
", root_cred.rdir);

    // Apply jailbreak credentials
    if (jbc_set_cred(&root_cred) != 0) {
        printf("[PS4-JB] ERROR: Failed to set root credentials
");
        return -1;
    }

    printf("[PS4-JB] ✓ Jailbreak successful! Sandbox escaped.
");
    printf("[PS4-JB] ✓ Process now has root privileges and full filesystem access
");

    jailbreak_initialized = true;
    return 0;
}

int ps4_mount_in_sandbox(const char* system_path, const char* mount_name) {
    if (!jailbreak_initialized) {
        printf("[PS4-JB] ERROR: Jailbreak not initialized. Call ps4_jailbreak_init() first.
");
        return -1;
    }

    printf("[PS4-JB] Mounting '%s' as '%s' in sandbox...
", system_path, mount_name);

    int result = jbc_mount_in_sandbox(system_path, mount_name);
    if (result != 0) {
        printf("[PS4-JB] ERROR: Failed to mount (error code: %d)
", result);
        return result;
    }

    printf("[PS4-JB] ✓ Successfully mounted '%s'
", mount_name);
    return 0;
}

int ps4_unmount_from_sandbox(const char* mount_name) {
    if (!jailbreak_initialized) {
        printf("[PS4-JB] ERROR: Jailbreak not initialized
");
        return -1;
    }

    printf("[PS4-JB] Unmounting '%s' from sandbox...
", mount_name);

    int result = jbc_unmount_in_sandbox(mount_name);
    if (result != 0) {
        printf("[PS4-JB] ERROR: Failed to unmount (error code: %d)
", result);
        return result;
    }

    printf("[PS4-JB] ✓ Successfully unmounted '%s'
", mount_name);
    return 0;
}

#endif // __PS4__
