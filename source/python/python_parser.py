import os, sys, inspect, types, ast

if len(sys.argv) != 2:
	print "Error, invalid number of arguments for python_parser."
	sys.exit()

if __name__ == "__main__":
	tree = ast.parse(sys.argv[1])

	functions = []
	for item in tree.body:
		if isinstance(item, ast.FunctionDef):
			functions.append(item)

	for function in functions:
		args = ", ".join(function.args.args[i].id for i in range(len(function.args.args)))
		print function.name + "(" + args + ")"
		print inspect.getmembers(function)[2][1]["lineno"]
