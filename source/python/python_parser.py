import os, sys, inspect, types

if len(sys.argv) != 2:
	print "Error, invalid number of arguments for python_parser."
	sys.exit()

if __name__ == "__main__":
	sys.path.append(os.path.abspath("."))

	try:
		mod = __import__(os.path.relpath(sys.argv[1][:-3]))
	except SyntaxError:
		sys.exit()
	funcs = [mod.__dict__.get(a) for a in dir(mod)
		if isinstance(mod.__dict__.get(a), types.FunctionType)]
	for func in funcs:
		print func.__name__

