# Part 2: Persistence

> Debugging is twice as hard as writing the code in the first place.  Therefore,
> if you write code as cleverly as possible, you are,  by definition,  not smart
> enough to debug it. - _Kernighan's Law_


Now that you have a working calculator,  it's time to make it easier to interact
with -- and a little bit  closer to a programming language.  This means  reading
more than  one expression at a time,  being able to save results by storing them
in variables, and using human-friendly infix notation.  Like last lab, this work
is split into two tracks:

- Half of the group will modify the existing lexer and parser to allow variables
  and multiple expressions in the input.

- The other half of the group will create a new parser that expects its input in
  infix notation rather than S expressions.


## Track A: Variables

You'll need a few new features to support variables.  You'll need a way to refer
to them: variable names, or identifiers.  You'll need a way to set their values:
an assignment operator. And you'll need a way to get their values back out: some
way to evaluate them.

To make them truly useful, you'll also want your programs to be able to evaluate
multiple expressions in sequence.  That'll let you set a value in one step, then
re-use that value in any subsequent calculations. For example, you could enter a
series of expressions:

```
(= a b 3)
(- (= b (+ b 5)) 7)
(* a b)
```

Which would correspond to this series of ASTs:

```
  (=)    |       (-)    |    (*)
 / | \   |      /   \   |   /   \
a  b  3  |    (=)    7  |  a     b
         |   /   \      |
         |  b    (+)    |
         |      /   \   |
         |     b     5  |
```

In infix, and evaluated, this would result in:

```
(a = b = 3)
3
((b = (b + 5)) - 7)
1
(a * b)
24
```

To fully support variables,  you'll need to do the following.  First, modify the
lexer from Part 1 to recognize two new types of tokens:

- Identifiers are series of letters, numbers, and underscores.  They must start
  with letters or underscores.
- The assignment operator is the equals sign: `=`

Then modify the S expression parser and AST from Part 1 to support variables:

- The value of an identifier is the value that was most recently stored there.
- The `=` operator  requires at least two arguments;  all but the  rightmost are
  required to be identifiers. It stores the rightmost value in these identifiers
  and "returns" this value.

Finally, modify the `main()` functions from Part 1 as necessary:

- `lex.cpp` should behave as before, but include the new token types.  You might
  not need to make any changes here.
- `parse.cpp` will need a variety of changes:
  - It should still read  (and lex) its entire standard input in one pass before
    handing it off to the parser (as in Part 1).
  - The parser should now expect multiple top-level S expressions,  and return a
    sequence of ASTs.
  - You should then loop over these ASTs one by one, first printing each tree in
    infix notation, then printing its value (as in Part 1).
  - If you encounter a  runtime error,  you should print the error message, then
    exit immediately with exit code three.

### Error Handling

Lexer errors should be handled as in Part 1:  print the error message and exit
with exit code 1.

Parser errors should be handled as in Part 1 as well:  print the error message
and exit with exit code two.  Note that a malformed assignment operation should
be reported as an unexpected token error, as in Part 1.  There are several ways
this can occur:

- If the first operand isn't an identifier, that token is unexpected.
- If there is only one operand, the closing parenthesis is unexpected.
- After a non-identifier operand, only a closing parenthesis is expected.

Runtime errors should also be handled as in Part 1:  print the error message and
exit with exit code three. Now that your code supports variables, however, there
is a new type of runtime error:  accessing a variable to which no value has been
assigned  should  fail with  the message  `Runtime error: unknown identifier ID`
(where `ID` is the identifier).

To ensure consistent behavior, your mathematical operators should evaluate their
operands from left to right. `(+ x (= x 4))` is a runtime error. `(+ (= x 4) x)`
is 8.


## Track B: Infix Notation

S expressions are convenient for LISP programmers, but to make a calculator easy
for humans to use  you'll need to support infix notation.  This is  the notation
that you're familiar with from math class,  where the operators go between their
operands and have a well-defined order of operations.

For now,  our calculator should support  the following operations,  here ordered
from highest precedence to lowest:

- Parentheses.
- Multiplication and division.
- Addition and subtraction.
- Assignment.

Additionally, all operators are left-associative except for assignment, which is
right-associative.  This means that this expression:

```
x = y = 0 + 1 + 2 * 3 - 4 / (5 + 6)
```

Should result in this AST:

```
  (=)
 /   \
x    (=)
    /   \
   y    (-)
       /   \
     (+)   (/)
    / |     | \
  (+)(*)    4 (+)
 / |  | \      | \
0  1  2  3     5  6
```

Your output should be in the same style as Part 1: the input in infix form (with
lots of parentheses) on one line, followed by the value on the next line:

```
(x = (y = (((0 + 1) + (2 * 3)) - (4 / (5 + 6)))))
6.63636
```

To simplify things -- and two allow your two groups  to work in parallel -- only
implement  parentheses and  the four mathematical operators for now.  Meanwhile,
the  Track A group will be adding  lexer and AST support  for variables; you can
take advantage of their work once it's done.

First, create a  new parser that recognizes infix expressions.  Don't modify the
old  S expression parser;  the group working on  Track A  will be using that for
testing.

Then create a new `main()` function in `src/calc.cpp`:

- This program should read standard input one line at a time.  Each line should
  contain exactly one infix expression.
- After reading a line, your program should lex it into tokens.
- It should then parse those tokens into an AST.
- It should then  print the AST in infix form,  as in Part 1  (print parentheses
  around every operation).
- It should then evaluate the AST and print the result.
- When it reaches the end of its input, it should exit with exit code zero.

Once the  group working  on Track A  has finished and  merged their code,  merge
`master` into  your branch.  This will give you the AST nodes and logic you need
to support variables.  Then make sure your code can handle variables correctly.

### Error Handling

Your `calc` program should recognize all of the errors described in the previous
track, but because it runs an interactive loop it shouldn't exit when hitting an
error. Instead, it should print the error message, then wait for another line of
user input.

- The line number should always be line one.
- For lexer and parser errors, only the error message should print.
- For runtime errors, the AST should print in infix form before the error.
- In the case of a runtime error, no variables should be updated.



## Finishing

Once all your changes are code reviewed  and merged into `master`,  you're ready
to submit.  Make sure  your  makefile and readme  are up to date and submit your
`master` branch  to Gradescope.  Remember to add all group members' names to the
submission!


## Notes

- In infix form, all of the operators you support take exactly two operands.
- Writing an infix parser can be hard.  Consider basing yours on one of these:
  - [Recursive Descent Parser](https://en.wikipedia.org/wiki/Recursive_descent_parser)
  - [Operator Precedence Parser](https://en.wikipedia.org/wiki/Operator-precedence_parser)
- In infix form, when an assignment operator doesn't have a variable as its left
  hand operand, it's the assignment operator that's the unexpected token.
