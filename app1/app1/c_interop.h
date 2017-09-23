#pragma once

struct lua_State;
typedef int(*lua_CFunction) (lua_State *L);

class c_interop
{
public:

	static void run_example1();
	static void run_example2();

	c_interop();
	virtual ~c_interop();

	long long call_lua_int_function(const char* funcname, void* userdata);
	void run_lua_file(const char* filename);
	long long get_lua_int(const char* varname) const;
	void register_c_function(const char* funcname, lua_CFunction f);

private:

	void validate_lua_errorcode(int errorcode) const;

private:
	lua_State* lua_state;
};