/*
 * Copyright (c) 2015-2020, SALT.
 * This file is licensed under GPLv2 or later
 * See LICENSE.md for terms of use.
 */

#include "command_gw.h"

#include "draw.h"
#include "utils.h"

u32 read_count = 0;

void gwcard_cmd_c5()
{
    static const u32 c5_cmd[4] = {0xC5000000, 0x00000000, 0x00000000, 0x00000000};
    ctrcard_send_command(c5_cmd, 0, 1, 0x100002C, NULL);
}

void gwcard_cmd_led(u32 color)
{
    const u32 led_cmd[4] = {0x72000000 | (color & 0xFFFFFF), 0x00000000, 0x00000000, 0x00000000};
    ctrcard_send_command(led_cmd, 0x200, 1, 0x100822C, NULL);
}

void gwcard_cmd_read(u32 sector, u32 length, u32 blocks, void* buffer)
{
    if(read_count++ > 10000)
    {
        gwcard_cmd_c5();
        read_count = 0;
    }

    gwcard_cmd_led(BLACK);
    const u32 read_cmd[4] = {
        (0xBF000000 | (u32)(sector >> 23)),
        (u32)((sector << 9) & 0xFFFFFFFF),
        0x00000000, 0x00000000
    };

    ctrcard_send_command(read_cmd, length, blocks, 0x100822C, buffer);
    gwcard_cmd_led(PURPLE);
}

void gwcard_cmd_write(u32 sector, u32 blocks, void* buffer)
{
    void *cur_buff = buffer;
    u32 cur_sector = sector;
    u32 cur_blocks = blocks;

    gwcard_cmd_led(RED);
    gwcard_cmd_c3(cur_sector, cur_buff);
    gwcard_cmd_led(PURPLE);
    gwcard_cmd_c7(cur_sector);


    while(1)
    {
        cur_sector++;
        cur_buff += 0x200;
        cur_blocks--;

        if(cur_blocks == 0)
            break;

        gwcard_cmd_led(RED);
        gwcard_cmd_c4(cur_sector, cur_buff);
        gwcard_cmd_led(PURPLE);
        gwcard_cmd_c7(cur_sector);
    }
}

u32 gwcard_cmd_c7(u32 sector)
{
    u32 out = 0;
    const u32 c7_cmd[4] = {
        (0xC7000000 | (u32)(sector >> 23)),
        (u32)((sector << 9) & 0xFFFFFFFF),
        0x00000000, 0x00000000
    };
    ctrcard_send_command(c7_cmd, 4, 1, 0x100002C, &out);
    return out;
}

void gwcard_cmd_c3(u32 sector, void* buffer)
{
    const u32 c3_cmd[4] = {
        (0xC3000000 | (u32)(sector >> 23)),
        (u32)((sector << 9) & 0xFFFFFFFF),
        0x00000000, 0x00000000
    };
    ctrcard_send_command(c3_cmd, 0x200, 0xC80001, 0x2100800C, buffer);
}

void gwcard_cmd_c4(u32 sector, void* buffer)
{
    const u32 c4_cmd[4] = {
        (0xC4000000 | (u32)(sector >> 23)),
        (u32)((sector << 9) & 0xFFFFFFFF),
        0x00000000, 0x00000000
    };
    ctrcard_send_command(c4_cmd, 0x200, 0x140001, 0x2100800C, buffer);
}
