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

#ifndef _SERVICE_H__
#define _SERVICE_H__

extern void service_init(int announce);
extern void service_cleanup(void);
extern void service_announce(struct interface *iface, int ttl);
extern void service_announce_services(struct interface *iface, const char *service, int ttl);
extern void service_reply(struct interface *iface, const char *match, int ttl);
extern void service_reply_a(struct interface *iface, int ttl);

#endif
