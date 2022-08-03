#include <stdio.h>

#include "../lib/lua/src/lua.h"
#include "../lib/lua/src/lualib.h"
#include "../lib/lua/src/lauxlib.h"

// --------------------------------------------------
// -- Just open a file with a print inside
// --------------------------------------------------
void lua_example_dofile(void)
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    luaL_dofile(L, "./scripts/hello.lua");
    lua_close(L);
}

// --------------------------------------------------
// -- Put a var in the stack and get it
// --------------------------------------------------
void lua_example_getvar(void)
{
    lua_State* L = luaL_newstate();
    luaL_dostring(L, "some_var = 486");
    lua_getglobal(L, "some_var");
    lua_Number some_var_in_c = lua_tonumber(L, -1);

    printf("(in C) The value of some_var is: %d\n ", (int)some_var_in_c);

    lua_close(L);
}
// --------------------------------------------------
// -- Fill the stack and read
// --------------------------------------------------
void lua_example_stack(void)
{
    lua_State* L = luaL_newstate();
    lua_pushnumber(L, 286); //stack[1] or stack[-3]
    lua_pushnumber(L, 386); //stack[2] or stack[-2]
    lua_pushnumber(L, 486); //stack[3] or stack[-1]

    lua_Number element;
    element = lua_tonumber(L, -1);
    printf("The last added element is %d\n ", (int)element);

    lua_close(L);
}

// --------------------------------------------------
// -- Call a function inside a lua file
// --------------------------------------------------
void addition_in_lua(int a, int b)
{
    lua_State* L = luaL_newstate();
    if (luaL_dofile(L, "./scripts/addition.lua") != LUA_OK){
        luaL_error(L, "Error : %s\n", lua_tostring(L, -1));
    }

    lua_getglobal(L, "addition");
    if (lua_isfunction(L, -1))  // last stack position
    {
        lua_pushnumber(L, a);   // 1st argument : a
        lua_pushnumber(L, b);   // 2nd argument : b

        const int NUM_ARGS = 2;
        const int NUM_RETURNS = 1;

        if (lua_pcall(L, NUM_ARGS, NUM_RETURNS, 0) != LUA_OK){
            luaL_error(L, "Error: %s\n", lua_tostring(L, -1));
        } else {
        lua_Number random_return = lua_tonumber(L, -1);

        printf("%d + %d = %d\n", a, b, (int)random_return);
        }
    }
    lua_close(L);
}

// --------------------------------------------------
// -- Send a function to lua
// --------------------------------------------------
int soustraction_in_c(lua_State* L)
{
    // Be carreful with the stack order !
    lua_Number b = lua_tonumber(L, -1);
    lua_Number a = lua_tonumber(L, -2);

    lua_pushnumber(L, a - b);
    return 1;   // The number of returned values
}
void send_soustraction_to_lua(int a, int b)
{
    lua_State* L = luaL_newstate();

    lua_pushcfunction(L, soustraction_in_c);
    lua_setglobal(L, "soustraction_in_c");

    luaL_dofile(L, "./scripts/read_c_function.lua");
    lua_getglobal(L, "soustraction");

    if (lua_isfunction(L, -1)){
        lua_pushnumber(L, a);  // 1st argument : a
        lua_pushnumber(L, b);  // 2nd argument : b

        const int NUM_ARGS = 2;
        const int NUM_RETURNS = 1;
        if (lua_pcall(L, NUM_ARGS, NUM_RETURNS, 0) != LUA_OK){
            luaL_error(L, "Error: %s\n", lua_tostring(L, -1));
        } else {
            printf("C soustration : %d\n", (int)lua_tonumber(L, -1));
        }
    }
}


// --------------------------------------------------
// --------------------------------------------------
int main(int argc, char *argv[])
{
    printf("Hello from C.\n");
    lua_example_dofile();
    lua_example_getvar();
    lua_example_stack();
    addition_in_lua(4, 6);

    send_soustraction_to_lua(100, 84);

    return 0;
}
