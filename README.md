# Cozy Interpreter

Interpreter of Cozy - a simple structural language, created for learning purposes.

## Getting Started

Instructions of installation are made for Linux like systems.

### Prerequisites

To compile Cozy interpreter you need `cc` compiler and `make`. 

### Installing

Clone Cozy interpreter repo

```
git clone https://github.com/FranciszekPin/cozy-interpreter
```

Go to src directory and compile cozy interpreter

```
cd cozy-interpreter/src
make
make clear
```

In `/src` directory you should obtain `ci` program. To run interpreter type:

```
./ci path_to_your_source_code_file.coz
```

`samples/` directory contains few code examples of cozy language. To run for example game.coz type:

```
./ci ../samples/game.coz
```

## Cozy Language syntax

Brief description of all language features. In samples/ directory there are examples of source code files written in cozy.

Every Cozy language source code should contain `program:` clause with instructions to run and **may** contain `define:` clause where variables can be defined.
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

The newline character plays the role of instruction separator. 
Indentation is not required but increases readability.
However, there can not be any instruction in the same line with `define:` or `program:` clause.
Also, remember to put every instruction in a new line. 
Examples of the **wrong** syntax:

```
define: int var
    int varAnother
program:
    var = 10 varAnother = 30
```

Variables should be defined with `int` keyword each in new line.
They are interpreted as integer type variables.
For now, there is no other type supported. 
Look at two examples of wrong variable declaration:

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

Syntax of assigning value to a variable:

```
variable-name = expression
```

Assigning value works similarly to C, but note that there are spaces required before and after '=' characters.
Also, chaining assignments is impossible.
See examples of wrong syntax below to better understand:

```
var= 7
var =7
var = another = 11
```

### printVar instruction

`printVar variableName` will print variableName value with adding automatically newline character.
Note, that using expressions in `printVar` is forbidden. Example of wrong use of `printVar`:

```
printVar a*10
```

instead, you have to calculate expression at first:

```
a = a*10
printVar a
```

### printStr instruction

`printStr` works similarly to `printVar`, but it prints given string instead of variable. For example:
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

### While instruction

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

