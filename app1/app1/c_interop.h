#pragma once

struct lua_State;

class c_interop
{
public:

	static void run();

	c_interop();
	virtual ~c_interop();

	long long call_lua_int_function(const char* funcname, void* userdata);
	void run_lua_file(const char* filename);
	long long get_lua_int(const char* varname) const;

private:
	lua_State* lua_state;
};