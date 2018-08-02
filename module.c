#include <stdio.h>
#include <stdlib.h>
#include<sys/time.h>
#include <string.h>
#include "redismodule.h"

int HelloCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    char pandaSrt[] = "                              _,add8ba,\n"
                        "                            ,d888888888b,\n"
                        "                           d8888888888888b                        _,ad8ba,_\n"
                        "                          d888888888888888)                     ,d888888888b,\n"
                        "                          I8888888888888888 _________          ,8888888888888b\n"
                        "                __________`Y88888888888888P\"\"\"\"\"\"\"\"\"\"\"baaa,__ ,888888888888888,\n"
                        "            ,adP\"\"\"\"\"\"\"\"\"\"\"9888888888P\"\"^                 ^\"\"Y8888888888888888I\n"
                        "         ,a8\"^           ,d888P\"888P^                           ^\"Y8888888888P'\n"
                        "       ,a8^            ,d8888'                                     ^Y8888888P'\n"
                        "      a88'           ,d8888P'                                        I88P\"^\n"
                        "    ,d88'           d88888P'                                          \"b,\n"
                        "   ,d88'           d888888'                                            `b,\n"
                        "  ,d88'           d888888I                                              `b,\n"
                        "  d88I           ,8888888'            ___                                `b,\n"
                        " ,888'           d8888888          ,d88888b,              ____            `b,\n"
                        " d888           ,8888888I         d88888888b,           ,d8888b,           `b\n"
                        ",8888           I8888888I        d8888888888I          ,88888888b           8,\n"
                        "I8888           88888888b       d88888888888'          8888888888b          8I\n"
                        "d8886           888888888       Y888888888P'           Y8888888888,        ,8b\n"
                        "88888b          I88888888b      `Y8888888^             `Y888888888I        d88,\n"
                        "Y88888b         `888888888b,      `\"\"\"\"^                `Y8888888P'       d888I\n"
                        "`888888b         88888888888b,                           `Y8888P^        d88888\n"
                        " Y888888b       ,8888888888888ba,_          _______        `\"\"^        ,d888888\n"
                        " I8888888b,    ,888888888888888888ba,_     d88888888b               ,ad8888888I\n"
                        " `888888888b,  I8888888888888888888888b,    ^\"Y888P\"^      ____.,ad88888888888I\n"
                        "  88888888888b,`888888888888888888888888b,     \"\"      ad888888888888888888888'\n"
                        "  8888888888888698888888888888888888888888b_,ad88ba,_,d88888888888888888888888\n"
                        "  88888888888888888888888888888888888888888b,`\"\"\"^ d8888888888888888888888888I\n"
                        "  8888888888888888888888888888888888888888888baaad888888888888888888888888888'\n"
                        "  Y8888888888888888888888888888888888888888888888888888888888888888888888888P\n"
                        "  I888888888888888888888888888888888888888888888P^  ^Y8888888888888888888888'\n"
                        "  `Y88888888888888888P88888888888888888888888888'     ^88888888888888888888I\n"
                        "   `Y8888888888888888 `8888888888888888888888888       8888888888888888888P'\n"
                        "    `Y888888888888888  `888888888888888888888888,     ,888888888888888888P'\n"
                        "     `Y88888888888888b  `88888888888888888888888I     I888888888888888888'\n"
                        "       \"Y8888888888888b  `8888888888888888888888I     I88888888888888888'\n"
                        "         \"Y88888888888P   `888888888888888888888b     d8888888888888888'\n"
                        "            ^\"\"\"\"\"\"\"\"^     `Y88888888888888888888,    888888888888888P'\n"
                        "                             \"8888888888888888888b,   Y888888888888P^\n"
                        "                              `Y888888888888888888b   `Y8888888P\"^\n"
                        "                                \"Y8888888888888888P     `\"\"\"\"^\n"
                        "                                  `\"YY88888888888P'\n"
                        "";
    RedisModule_ReplyWithSimpleString(ctx, pandaSrt);
    return REDISMODULE_OK;
}

int SimpleRandCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    long int randNum = rand();
    RedisModule_ReplyWithLongLong(ctx, randNum);
    return REDISMODULE_OK;
}

int GetTimeCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    long int millisecs = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    RedisModule_ReplyWithLongLong(ctx, millisecs);
    return REDISMODULE_OK;
}


int RedisModule_OnLoad(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (RedisModule_Init(ctx, "panda", 1, REDISMODULE_APIVER_1) ==
        REDISMODULE_ERR) {
        return REDISMODULE_ERR;
    }

    RedisModule_Log(ctx, "info", "panda redis module start up");

    if (RedisModule_CreateCommand(ctx, "panda.hello", HelloCommand, "write fast",
                                  1, 1, 1) == REDISMODULE_ERR) {
        return REDISMODULE_ERR;

    }

    if (RedisModule_CreateCommand(ctx, "panda.rand", SimpleRandCommand, "readonly",
                                  1, 1, 1) == REDISMODULE_ERR) {
        return REDISMODULE_ERR;
    }

    if (RedisModule_CreateCommand(ctx, "panda.time", GetTimeCommand, "readonly",
                                  1, 1, 1) == REDISMODULE_ERR) {
        return REDISMODULE_ERR;
    }


    return REDISMODULE_OK;
}
