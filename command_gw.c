/*
 * Copyright (c) 2015-2016, SALT.
 * This file is licensed under GPLv2 or later
 * See LICENSE.md for terms of use.
 */
 
#include "command_gw.h"

u32 read_count = 0;

void gwcard_cmd_c5()
{
    static const u32 c5_cmd[4] = {0xC5000000, 0x00000000, 0x00000000, 0x00000000};
    CTR_SendCommand(c5_cmd, 0, 1, 0x100002C, NULL);
}
 
void gwcard_cmd_led(u32 color)
{
    const u32 led_cmd[4] = {0x72000000 | (color & 0xFFFFFF), 0x00000000, 0x00000000, 0x00000000};
    CTR_SendCommand(led_cmd, 0x200, 1, 0x100822C, NULL);
}

void gwcard_cmd_read(u32 sector, u32 length, u32 blocks, void* buffer)
{
    if(read_count++ > 10000)
    {
        gwcard_cmd_c5();
        read_count = 0;
    }

    const u32 read_cmd[4] = {
        (0xBF000000 | (u32)(sector >> 23)),
        (u32)((sector << 9) & 0xFFFFFFFF),
        0x00000000, 0x00000000
    };

    CTR_SendCommand(read_cmd, length, blocks, 0x100822C, buffer);
}
