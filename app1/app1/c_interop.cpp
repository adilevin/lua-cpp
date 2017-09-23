#include <lua.hpp>
#include "c_interop.h"
#include <iostream>
#include <exception>

void c_interop::run_example1() {

	std::cout << "EXAMPLE 1\n";
	c_interop c;
	c.run_lua_file("example1.lua");
	std::cout << "C++ gets v = " << c.get_lua_int("v") << "\n";
	std::cout << "C++ gets dummy_int_func(nullptr) = " << c.call_lua_int_function("dummy_int_func", nullptr) << "\n";
}

void c_interop::run_example2() {


	std::cout << "\n\nEXAMPLE 2\n";

	class Person {
	public:
		Person(int age) : m_age(age) {}
		int get_age() const { return m_age;  }
		static int age(lua_State* lua_state) {
			int n = lua_gettop(lua_state);
			if (n != 1)
				throw std::exception("Wrong number of arguments to C function age()");
			if (!lua_islightuserdata(lua_state, 1))
				throw std::exception("Wrong userdata sent to C function age()");
			const Person* p = (const Person*)lua_touserdata(lua_state, 1);
			lua_pushinteger(lua_state, p->get_age());
			return 1;
		}

	private:
		int m_age;
	};


	Person p1(12), p2(20);

	c_interop c;
	c.register_c_function("age", Person::age);
	c.run_lua_file("example2.lua");
	long long is_eligible = c.call_lua_int_function("check_eligibility", &p1);
	std::cout << "C++ gets check_eligibility(p1) = " << is_eligible << "\n";
	is_eligible = c.call_lua_int_function("check_eligibility", &p2);
	std::cout << "C++ gets check_eligibility(p2) = " << is_eligible << "\n";
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

void c_interop::validate_lua_errorcode(int errorcode) const
{
	switch (errorcode) {
	case LUA_ERRRUN:
		throw std::exception("LUA runtime error"); break;
	case LUA_ERRMEM:
		throw std::exception("LUA memory allocation error"); break;
	case LUA_ERRERR:
		throw std::exception("LUA error while running the error handler function"); break;
	case 0:
		break;
	default:
		throw std::exception("LUA unrecognized error code");
	}
}

long long c_interop::call_lua_int_function(const char* funcname, void* userdata) {
	lua_getglobal(lua_state, funcname);
	lua_pushlightuserdata(lua_state, userdata);
	validate_lua_errorcode(lua_pcall(lua_state, 1, 1, 0));
	if (!lua_isnumber(lua_state, -1))
		throw std::exception((std::string("Failed to get output of LUA function ") + std::string(funcname)).c_str());
	return lua_tointeger(lua_state, -1);
}

void c_interop::register_c_function(const char* funcname, lua_CFunction f)
{
	lua_register(lua_state, funcname, f);
}


