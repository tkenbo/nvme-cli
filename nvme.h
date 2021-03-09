/*
 * Definitions for the NVM Express interface
 * Copyright (c) 2011-2014, Intel Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 */

#ifndef _NVME_H
#define _NVME_H

#include <dirent.h>
#include <stdbool.h>
#include <stdint.h>
#include <endian.h>
#include <sys/time.h>
#include <libnvme.h>

#include "plugin.h"
#include "util/json.h"
#include "util/argconfig.h"


enum nvme_print_flags {
	NORMAL	= 0,
	VERBOSE	= 1 << 0,	/* verbosely decode complex values for humans */
	JSON	= 1 << 1,	/* display in json format */
	VS	= 1 << 2,	/* hex dump vendor specific data areas */
	BINARY	= 1 << 3,	/* binary dump raw bytes */
};

#define SYS_NVME "/sys/class/nvme"

void register_extension(struct plugin *plugin);
int parse_and_open(int argc, char **argv, const char *desc,
	const struct argconfig_commandline_options *clo);

extern const char *devicename;
extern const char *output_format;

enum nvme_print_flags validate_output_format(char *format);
int __id_ctrl(int argc, char **argv, struct command *cmd,
	struct plugin *plugin, void (*vs)(__u8 *vs, struct json_object *root));
char *nvme_char_from_block(char *block);
void *mmap_registers(const char *dev);

extern int current_index;

void *nvme_alloc(size_t len, bool *huge);
void nvme_free(void *p, bool huge);

unsigned long long elapsed_utime(struct timeval start_time,
					struct timeval end_time);
#endif /* _NVME_H */
