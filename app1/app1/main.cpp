#include <lua.hpp>
#include <iostream>

void main()
{
	std::cout << "Hello!\n-------\n"; 

	lua_State* L = lua_open();
	luaL_openlibs(L);
	luaL_dofile(L, "script.lua");
	lua_getglobal(L, "v");
	long long v = lua_tointeger(L, -1);

	std::cout << "v = " << v << "\n";

	lua_close(L);

	//luaL_dostring(L, "print('Hello from lua!')");

}