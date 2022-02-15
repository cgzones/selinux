#ifndef _SEPOL_POLICYDB_INITIALSIDS_H_
#define _SEPOL_POLICYDB_INITIALSIDS_H_

#ifdef __cplusplus
extern "C" {
#endif

// initial sid names aren't actually stored in the pp files, need to a have
// a mapping, taken from the linux kernel
static const char * const selinux_sid_to_str[] = {
	"null",
	"kernel",
	"security",
	"unlabeled",
	"fs",
	"file",
	"file_labels",
	"init",
	"any_socket",
	"port",
	"netif",
	"netmsg",
	"node",
	"igmp_packet",
	"icmp_socket",
	"tcp_socket",
	"sysctl_modprobe",
	"sysctl",
	"sysctl_fs",
	"sysctl_kernel",
	"sysctl_net",
	"sysctl_net_unix",
	"sysctl_vm",
	"sysctl_dev",
	"kmod",
	"policy",
	"scmp_packet",
	"devnull",
};

#define SELINUX_SID_SZ (sizeof(selinux_sid_to_str)/sizeof(selinux_sid_to_str[0]))

static inline unsigned int selinux_str_to_sid(const char *name)
{
	unsigned i;

	for (i = 1; i < SELINUX_SID_SZ; i++) {
		if (strcmp(name, selinux_sid_to_str[i]) == 0)
			return i;
	}

	return 0;
}

static const char * const xen_sid_to_str[] = {
	"null",
	"xen",
	"dom0",
	"domio",
	"domxen",
	"unlabeled",
	"security",
	"ioport",
	"iomem",
	"irq",
	"device",
	"domU",
	"domDM",
};

#define XEN_SID_SZ (sizeof(xen_sid_to_str)/sizeof(xen_sid_to_str[0]))

static inline unsigned int xen_str_to_sid(const char *name)
{
	unsigned i;

	for (i = 1; i < XEN_SID_SZ; i++) {
		if (strcmp(name, xen_sid_to_str[i]) == 0)
			return i;
	}

	return 0;
}

#ifdef __cplusplus
}
#endif

#endif				/* _SEPOL_POLICYDB_INITIALSIDS_H_ */
