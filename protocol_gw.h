/*
 * Copyright (c) 2015-2020, SALT.
 * This file is licensed under GPLv2 or later
 * See LICENSE.md for terms of use.
 */

#ifndef _PROTOCOL_GW_H
#define _PROTOCOL_GW_H

#include "common.h"

#include "protocol_ntr.h"
#include "command_ntr.h"

bool gwcard_init();
void gwcard_deinit();
bool gwcard_init_status();

//Gateway SPI magic data
const long int gw_magic_size;
const unsigned char gw_magic[0x1001];

//Supercard DSTWO+ variant
const long int gw_magic_sc_size;
const unsigned char gw_magic_sc[0x1001];

#endif
