assert(#arg == 1)

local starttime = os.clock()

os.execute(arg[1])

local endtime = os.clock()

print(endtime - starttime)
