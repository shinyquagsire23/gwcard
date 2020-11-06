/*
 * Copyright (c) 2015-2020, SALT.
 * This file is licensed under GPLv2 or later
 * See LICENSE.md for terms of use.
 */

#ifndef _COMMAND_GW_H
#define _COMMAND_GW_H

#include "common.h"

#include "protocol.h"
#include "protocol_ctr.h"

void gwcard_cmd_led(u32 color);
void gwcard_cmd_read(u32 sector, u32 length, u32 blocks, void* buffer);
void gwcard_cmd_write(u32 sector, u32 blocks, void* buffer);
u32 gwcard_cmd_c7(u32 sector);
void gwcard_cmd_c3(u32 sector, void* buffer);
void gwcard_cmd_c4(u32 sector, void* buffer);
void gwcard_cmd_c5();

#endif
