//
// PS4 Jailbreak / Sandbox Escape wrapper for pplay
//

#ifndef PPLAY_PS4_JAILBREAK_H
#define PPLAY_PS4_JAILBREAK_H

#ifdef __PS4__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize PS4 jailbreak and escape sandbox
 * This must be called early in the application startup
 * @return 0 on success, -1 on failure
 */
int ps4_jailbreak_init(void);

/**
 * Mount a system path inside the sandbox
 * @param system_path The real filesystem path (e.g., "/mnt/disc")
 * @param mount_name The name to mount it as in the sandbox
 * @return 0 on success, error code on failure
 */
int ps4_mount_in_sandbox(const char* system_path, const char* mount_name);

/**
 * Unmount a previously mounted path from the sandbox
 * @param mount_name The mount name to unmount
 * @return 0 on success, error code on failure
 */
int ps4_unmount_from_sandbox(const char* mount_name);

#ifdef __cplusplus
}
#endif

#endif // __PS4__

#endif // PPLAY_PS4_JAILBREAK_H
