#include <lua.hpp>
#include "c_interop.h"
#include <iostream>

void c_interop::run() {
	c_interop c;
	c.run_example1();
	std::cout << "C++ gets v = " << c.get_lua_int("v") << "\n";
}

c_interop::c_interop() {
	lua_state = lua_open();
	luaL_openlibs(lua_state);
}

c_interop::~c_interop() {
	lua_close(lua_state);
}

void c_interop::run_example1() {
	luaL_dofile(lua_state, "example1.lua");
}

long long c_interop::get_lua_int(const char* name) const {
	lua_getglobal(lua_state, name);
	return lua_tointeger(lua_state, -1);
}