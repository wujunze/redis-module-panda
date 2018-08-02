#include <stdio.h>
#include <stdlib.h>
#include<sys/time.h>
#include <string.h>
#include "redismodule.h"

int HelloCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    char pandaSrt[30] = "Hello Panda";
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
