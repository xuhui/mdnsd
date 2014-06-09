/*
 * Copyright (C) 2014 John Crispin <blogic@openwrt.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 2.1
 * as published by the Free Software Foundation
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <sys/stat.h>
#include <sys/types.h>

#include <time.h>
#include <stdio.h>
#include <fcntl.h>
#include <getopt.h>
#include <resolv.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/nameser.h>
#include <asm/byteorder.h>

#include <libubus.h>
#include <libubox/uloop.h>

#include "dns.h"
#include "ubus.h"
#include "util.h"
#include "cache.h"
#include "service.h"
#include "announce.h"
#include "interface.h"

static char *iface_name = "eth0";

int
main(int argc, char **argv)
{
	int ch, ttl;

	while ((ch = getopt(argc, argv, "t:i:d")) != -1) {
		switch (ch) {
		case 't':
			ttl = atoi(optarg);
			if (ttl > 0)
				announce_ttl = ttl;
			else
				fprintf(stderr, "invalid ttl\n");
			break;
		case 'd':
			debug++;
			break;
		case 'i':
			iface_name = optarg;
			break;
		}
	}

	if (!iface_name)
		return -1;

	uloop_init();

	if (interface_add(iface_name)) {
		fprintf(stderr, "Failed to add interface %s\n", iface_name);
		return -1;
	}

	signal_setup();

	if (cache_init())
		return -1;

	service_init();

	ubus_startup();
	uloop_run();
	uloop_done();

	cache_cleanup();
	service_cleanup();
	vlist_flush(&interfaces);

	return 0;
}
