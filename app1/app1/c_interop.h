#pragma once

struct lua_State;

class c_interop
{
public:

	static void run();

	c_interop();
	virtual ~c_interop();

	void run_example1();
	long long get_lua_int(const char* name) const;

private:
	lua_State* lua_state;
};