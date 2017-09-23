print "LUA script begins"

function mult_by_2(x)
	return x*2
end

function dummy_int_func(userdata)
	return 3
end

print("  LUA says: 10 * 2 = "..mult_by_2(10))

v = 8;

print("  LUA assigned v = "..v)

print "LUA script ends"