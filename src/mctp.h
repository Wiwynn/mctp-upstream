/* SPDX-License-Identifier: GPL-2.0 */
/*
 * mctp: userspace utility for managing the kernel MCTP stack.
 *
 * Interim definitions for the MCTP kernel interface. While the MCTP kernel
 * API is going through upstream, system toolchains may not yet have the
 * required definitions for mctp tools. This header provides fallback
 * implementations (protected by #ifdef guards) of those new interfaces.
 *
 * Copyright (c) 2021 Code Construct
 * Copyright (c) 2021 Google
 */

#ifndef _MCTP_H
#define _MCTP_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_LINUX_MCTP_H
#include <linux/mctp.h>
#endif

#ifndef AF_MCTP
#define AF_MCTP 45
#endif

/* MCTP serial line discipline */
#ifndef N_MCTP
#define N_MCTP	28
#endif

#include <stdint.h>

#ifndef MCTP_NET_ANY

#ifndef MAX_ADDR_LEN
#define MAX_ADDR_LEN 32
#endif

typedef uint8_t			mctp_eid_t;

struct mctp_addr {
	mctp_eid_t		s_addr;
};

struct sockaddr_mctp {
	unsigned short int	smctp_family;
	int			smctp_network;
	struct mctp_addr	smctp_addr;
	uint8_t			smctp_type;
	uint8_t			smctp_tag;
};

struct sockaddr_mctp_ext {
	struct sockaddr_mctp	smctp_base;
	int			smctp_ifindex;
	uint8_t			smctp_halen;
	unsigned char		smctp_haddr[MAX_ADDR_LEN];
};

#define MCTP_NET_ANY 0
#define MCTP_ADDR_ANY 0xff
#define MCTP_TAG_OWNER 0x08

#endif /* MCTP_NET_ANY */

#ifndef IFLA_MCTP_MAX

/* From if_link.h */
enum {
	IFLA_MCTP_UNSPEC,
	IFLA_MCTP_NET,
	IFLA_MCTP_MEDIA_TYPE,
	__IFLA_MCTP_MAX,
};

#define IFLA_MCTP_MAX (__IFLA_MCTP_MAX - 1)

#endif /* IFLA_MCTP_MAX */

/* setsockopt(2) options */
#ifndef SOL_MCTP
#define SOL_MCTP 0
#endif

#ifndef MCTP_OPT_ADDR_EXT
#define MCTP_OPT_ADDR_EXT	1
#endif

#endif /* _MCTP_H */