#include <stdio.h>

#include "../lib/lua/src/lua.h"
#include "../lib/lua/src/lualib.h"
#include "../lib/lua/src/lauxlib.h"


int main(int argc, char *argv[])
{
    printf("Hello from C.\n");

    lua_State* L = luaL_newstate();

    luaL_openlibs(L);
    luaL_dofile(L, "./scripts/hello.lua");

    lua_close(L);

    return 0;
}
