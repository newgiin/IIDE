import os, sys, inspect, types, ast

if len(sys.argv) != 2:
    print "Error, invalid number of arguments for python_parser."
    sys.exit()


def printFunctions(functions):
    print len(functions)
    for function in functions:
        args = ", ".join(function.args.args[i].id for i in range(len(function.args.args)))
        print function.name + "(" + args + ")"
        print inspect.getmembers(function)[2][1]["lineno"]
        
class sfkjl:
    def __init__(self):
        pass
    
if __name__ == "__main__":
    """
        argv[1] - source code to parse
    	prints:
			number of classes (+1 for module level)
			name of next class
                        line number of class (0 for module level)
			number of functions in next class
			list of functions:
				function name with args
				line number of function
    """
    tree = ast.parse(sys.argv[1])

    functions = []
    classes = []
    
    for item in tree.body:
        if isinstance(item, ast.FunctionDef):
            functions.append(item)
        elif isinstance(item, ast.ClassDef):
            classes.append(item)

    print len(classes) + 1
    print "Module"
    print "0"
    printFunctions(functions)
    for c in classes:
        functions = []
        for item in c.body:
            if isinstance(item, ast.FunctionDef):
                functions.append(item)
        print c.name
        print inspect.getmembers(c)[2][1]["lineno"]
        printFunctions(functions)

    
