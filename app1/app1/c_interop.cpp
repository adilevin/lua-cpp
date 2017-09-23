#include <lua.hpp>
#include "c_interop.h"
#include <iostream>
#include <exception>

void c_interop::run() {
	c_interop c;
	c.run_lua_file("example1.lua");
	std::cout << "C++ gets v = " << c.get_lua_int("v") << "\n";
	std::cout << "C++ gets dummy_int_func(nullptr) = " << c.call_lua_int_function("dummy_int_func", nullptr) << "\n";
}

c_interop::c_interop() {
	lua_state = lua_open();
	luaL_openlibs(lua_state);
}

c_interop::~c_interop() {
	lua_close(lua_state);
}

void c_interop::run_lua_file(const char* filename) {
	luaL_dofile(lua_state, filename);
}

long long c_interop::get_lua_int(const char* varname) const {
	lua_getglobal(lua_state, varname);
	return lua_tointeger(lua_state, -1);
}

long long c_interop::call_lua_int_function(const char* funcname, void* userdata) {
	lua_getglobal(lua_state, funcname);
	lua_pushlightuserdata(lua_state, userdata);
	if (lua_pcall(lua_state, 1, 1, 0) != 0)
		throw std::exception((std::string("Failed to call LUA function ") + std::string(funcname)).c_str());
	if (!lua_isnumber(lua_state, -1))
		throw std::exception((std::string("Failed to get output of LUA function ") + std::string(funcname)).c_str());
	return lua_tointeger(lua_state, -1);
}