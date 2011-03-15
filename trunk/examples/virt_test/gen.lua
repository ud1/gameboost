#!/usr/bin/lua

n = 9
k = 4
meth_cnt = math.pow(2, k)
cnt = math.pow(2, n-k)

io.output("virt_test.h")

for i = 1, cnt do
	io.write(string.format("struct Test%d\n", i))
	io.write("{\n")
	io.write(string.format("\tTest%d();\n", i))
	for j = 1, meth_cnt do
		io.write(string.format("\tint calc%d();\n", j))
	end
	for j = 1, n do
		io.write(string.format("\tint var%d;\n", j))
	end
	io.write(string.format("};\n\n"))
	
	io.write(string.format("struct VirtTest%d\n", i))
	io.write("{\n")
	io.write(string.format("\tVirtTest%d();\n", i))
	for j = 1, meth_cnt do
		io.write(string.format("\tvirtual int calc%d();\n", j))
	end
	for j = 1, n do
		io.write(string.format("\tint var%d;\n", j))
	end
	io.write(string.format("};\n\n"))
end

io.close()


io.output("virt_test.cpp")

io.write(string.format("#include \"virt_test.h\"\n\n"))

for i = 1, cnt do
	io.write(string.format("Test%d::Test%d()\n", i, i))
	io.write("{\n")
	for j = 1, n do
		io.write(string.format("\tvar%d=%d;\n", j, j))
	end
	io.write("}\n\n")
	
	for j = 1, meth_cnt do
		io.write(string.format("int Test%d::calc%d()\n", i, j))
		io.write("{\n")
		io.write("\treturn 0")
		val = (i-1)*meth_cnt + j-1
		for k = 1, n do
			if (val % 2 == 1) then
				io.write(string.format(" + var%d", k))
			end
			val = math.floor(val / 2)
		end
		io.write(string.format(";\n"))
		io.write(string.format("}\n\n"))
	end

	
	io.write(string.format("VirtTest%d::VirtTest%d()\n", i, i))
	io.write("{\n")
	for j = 1, n do
		io.write(string.format("\tvar%d=%d;\n", j, j))
	end
	io.write("}\n\n")
	
	for j = 1, meth_cnt do
		io.write(string.format("int VirtTest%d::calc%d()\n", i, j))
		io.write("{\n")
		io.write("\treturn 0")
		val = (i-1)*meth_cnt + j-1
		for k = 1, n do
			if (val % 2 == 1) then
				io.write(string.format(" + var%d", k))
			end
			val = math.floor(val / 2)
		end
		io.write(string.format(";\n"))
		io.write(string.format("}\n\n"))
	end
end

io.close()


io.output("test.cpp")

io.write(string.format("#include \"virt_test.h\"\n\n"))
for i = 1, cnt do
	io.write(string.format("Test%d test%d;\n", i, i))
	io.write(string.format("VirtTest%d virt_test%d;\n", i, i))
end
io.write(string.format("\n"))
io.write(string.format("int test()\n"))
io.write(string.format("{\n"))
io.write(string.format("\tint result = 0;\n"))
for i = 1, cnt do
	for j = 1, meth_cnt do
		io.write(string.format("\tresult += test%d.calc%d();\n", i, j))
	end
end
io.write(string.format("\treturn result;\n"))
io.write(string.format("}\n\n"))


io.write(string.format("int virt_test()\n"))
io.write(string.format("{\n"))
io.write(string.format("\tint result = 0;\n"))
for i = 1, cnt do
	for j = 1, meth_cnt do
		io.write(string.format("\tresult += virt_test%d.calc%d();\n", i, j))
	end
end
io.write(string.format("\treturn result;\n"))
io.write(string.format("}\n\n"))

io.close()