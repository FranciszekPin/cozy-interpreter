# Cozy Interpreter

Interpreter of simple structural language defined below

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

To compile cozy interpreter you need `gcc` compiler and `make`. 

### Installing

Clone cozy interpreter repo

```
git clone https://github.com/FranciszekPin/cozy-interpreter
```

Go to src directory and compile cozy interpreter

```
cd cozy-interpreter/src
make
make clear
```

In `/src` directory you should obtain `ci` program. To run interpreter just type:

```
./ci path_to_your_source_code_file.coz
```

`samples/` directory contains few code examples of cozy language. To run for example game.coz type:

```
./ci ../samples/game.coz
```

## Running the tests

`tests/` directory contains tests for each module. If you want to run them, add `run_test()` at the beginning of `main()` function in `src/main.c`. Yes, I know the testing system is a little primitive, I'm planning to make it better.

## Cozy Language syntax

Every Cozy language source code should contain `program:` clause containing instruction to run and may contain `define:` clause where variables can be defined.
Example of simple source code:

```
define:
    int someNumber
    
program:
    someNumber = 10
    printVar someNumber
    printStr Assignment works.
```

should produce output:

```
10
Assignment works.
```

As you see, the separation character is new line character. Indentation is not required, but increases readability.
However, there can not be any instruction in the same line with `define:` or `program:` clause.
Also remember to put every instruction in new line. Examples of **wrong** syntax:

```
define: int var
    int varAnother
program:
    var = 10 varAnother = 30
```

Variables should be defined with `int` keyword each in new line.
For now, there is no other types supported. Look at two examples of wrong variable declaration:

```
define:
    var
    string number
    int a int b
```

Each of the variables is initialized with `0` value.
Variable names are not case-sensitive, so someNumber and SOMENUMBER is interpreted as the same variable:

```
define:
    int someNumber
program:
    printVar SOMENUMBER
    printVar someNumber
```

output will be:

```
0
0
```

### Expressions

Cozy language accepts expressions in form similar to C language. 
Available operators are: `+ - / * % && || == != <= >= < >`. Examples of legal expressions:

```
(3 * someVar) <= a
(5*5/7) - var1 != 123456
```

### Assignment

Syntax of assigning value to variable:

```
variable-name = expression
```

Assigning value works in similar way to C, but note that there are spaces required before and af after '=' characters.
Also chaining assignments is impossible.
See examples of wrong syntax below to better understand:

```
var= 7
var =7
var = another = 11
```

### printVar instruction

`printVar variableName` will print variableName value with adding automatically newline character.
Note, that using expressions in `printVar` forbidden. Example of wrong use of `printVar`:

```
printVar a*10
```

instead you have to calculate expression at first:

```
a = a*10
printVar a
```

### printStr instruction

`printStr` works in similar way to `printVar`, but it prints given string instead of variable. For example:
```
printStr Hello world!
```

will print 'Hello world!'.

### if instruction

Syntax of if instruction:

```
if condition
    instruction1
    instruction2
    ...
end
```

For example:

```
if a > b * 10
    printVar a
end
```

if-else variant is also available:

```
if n % 2 == 0
    printStr n is even
else
    printStr n is odd
end
```

### while instruction

syntax of while instruction:

```
while condition
    instruction1
    instruction2
    ...
end
```

for example:

```
n = 10
while n > 10
    printVar n
    n = n-1
end
```

## Modules

* source_code_reader
    * `load_source_code()` - loads source code from file to program's data structure 

* parser:
    * `load_defined_variables()` - loads variable to variable register
    * `parse_program()` - generates instruction tree
    
* program_runner
    * `run_program()` - interprets instruction tree parsed by parser
    
* variable_register
    * `define_variable()` - defines variable with given name
    * `get/set _variable_val()` - gets/sets variable value with given name
    
* error_manager
    * `throw_error()` - prints proper error message and terminates interpreting
    
* evaluation
    * `evaluate_expression()` - return expression's value