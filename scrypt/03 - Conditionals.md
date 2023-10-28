# Part 3: Conditionals

> I don't know how to stop it, there was never any intent to write a programming
> language  [...] I have absolutely no idea how to write a programming language,
> I just kept adding the next logical step on the way. - _Rasmus Lerdorf_


Now that you have a calculator that supports variables,  you're ready to add the
first big feature of a real programming language: control flow.  But in order to
support this, you'll need another feature first. Statements like `if` or `while`
need their conditions to evaluate  not to numbers,  but to true or false.  So in
order to implement branching and loops, you'll first need to implement Booleans.

These features  will require  more coordination within your group  than the last
batch.  The conditional statements from Track B  require the Boolean values from
Track A, so it's important that Track A  (or at least minimal support for bools)
gets finished early.

_Note:_  Starting with this checkpoint,  `parse.cpp` and the S expression parser
are deprecated, and will no longer be tested.


## Track A: Booleans

In order to support conditionals, you need a new data type:  Booleans, or bools.
These  represent  truth  values; the only  values  they can hold  are `true` and
`false`.

You'll also need  some new operators:  comparison operators for generating bools
and logical operators for manipulating them.  To allow for more interesting test
cases,  we'll  also  add the  modulo operator,  `%`  (implement  this  with  the
`std::fmod()` function  from `cmath`).  The full set of operators you'll need to
support, from highest precedence to lowest, is now:

- Parentheses (`(` and `)`).
- Multiplication, division, and modulo (`*`, `/`, and `%`).
- Addition and subtraction (`+` and `-`).
- Ordered comparison (`<`, `<=`, `>`, and `>=`).
- Equality and inequality (`==` and `!=`).
- Logical and (`&`).
- Logical exclusive or (`^`).
- Logical inclusive or (`|`).
- Assignment (`=`).

The arithmetic operators only work on numbers,  and return numbers.  The ordered
comparison operators  only work on numbers,  and return bools.  The (in)equality
operators work on either two numbers or two bools, and return bools.

To add support for bools, you'll need to do the following.

- Update your lexer to recognize all the new operators and two new constants:
  `true` and `false`.
- Update `lex.cpp` (if necessary) to handle the new tokens.
- Update your infix parser to support all of the new operations.
- Update your evaluation functions so that they can return bools as well as
  numbers.
- Update `calc.cpp` as necessary.

### Error Handling

For now, treat type errors as runtime errors. If you try to perform an operation
but find an operand of the wrong type (or if you try to evaluate an (in)equality
and the operands are of different types), raise a runtime error with the message
`Runtime error: invalid operand type.`


## Track B: Statements

Until now, every AST you've parsed has been what's called an expression:  a tree
of operations that can be evaluated  and produces a value.  The constructs we're
about to introduce  are not expressions;  they do not produce values.  These are
known as statements, and are strictly higher level than expressions. Expressions
cannot contain statements.  Statements can contain expressions.

You'll be adding  three statements to the language:  `if`, `while`, and `print`.
These basically work as you expect; they're defined formally below the example.

```
x     = 42
steps = 0

while x > 1 {
  steps = steps + 1
  if x % 2 == 0 {
    x = x / 2
  }
  else {
    x = 3 * x + 1
  }
}

print steps
```

To simplify the important definitions, we'll first define blocks:

- A **block** is a sequence of any number of statements (as defined below).
- A **braced block** is a block enclosed in curly braces (`{` and `}`).

A statement is then defined as any one of the following:

- An **if statement**:  the token `if`, followed by an expression, followed by a
  braced block. An if statement _may_ be followed by the token `else`; if it is,
  this `else` must be followed by either another if statement or a braced block.
- A **while statement**:  the token `while`, followed by an expression, followed
  by a braced block.
- A **print statement**: the token `print` followed by an expression.
- An expression.

Evaluating these works as you'd expect:

- To evaluate an if statement,  first evaluate its condition.  If that evaluates
  to true, evaluate the statements in the braced block. Otherwise, if the if has
  an else, evaluate the statements in the else block.
- To evaluate a while statement, first evaluate its condition. If that evaluates
  to true, evaluate the statements in the braced block.  Then repeat.
- To evaluate a print statement,  evaluate its expression, then print the result
  to standard output, followed by a newline.
- To evaluate an expression, simply evaluate it as you normally would.

To add support for statements, you'll need to do the following.

- Update the lexer to add the new keywords you need (and curly braces).
- Update the infix parser to support statements.
- Note that `calc.cpp` expects each line of input to be an expression. It should
  not support statements!
- Add a new `main()` function in `src/format.cpp`.  It should read in its entire
  input, build an AST of the program,  and then print it.  Each statement should
  go on its own line. Statements within braced blocks should be indented by four
  spaces.  Expressions should print as they did in Part 2.
- Add a new `main()` function in `src/scrypt.cpp`. This is your new interpreter!
  It should read its entire input, build an AST of the program, and evaluate it.
  If there are no errors,  its only output should be  what is explicitly printed
  by print statements.

When run through `format.cpp`, the example program above should display as:

```
(x = 42)
(steps = 0)
while (x > 1) {
    (steps = (steps + 1))
    if ((x % 2) == 0) {
        (x = (x / 2))
    }
    else {
        (x = ((3 * x) + 1))
    }
}
print steps
```

When run through `scrypt.cpp`, it should produce:

```
8
```

### Error Handling

If the condition  to an if or while statement does not evaluate to a bool, raise
a runtime error with the message `Runtime error: condition is not a bool.`

In the case of a  lexer error,  both `format.cpp` and `scrypt.cpp`  should print
the error message and  exit with exit code one.  In case of a parse error, print
the message and exit with exit code two.  Only `scrypt.cpp` should encounter any
runtime errors;  if it does, it should print the message and exit with exit code
three.


## Notes

- Keywords like `true` or `while` are now "reserved words" in our language; they
  can no longer be used as variable names like they could in Part 2.
- When lexing, always read as much as you can into one token before moving on to
  the next. The input `=====` should lex to `==`, `==`, and `=`.
- None of the operators  "short circuit"  like the `&&` and `||`  operators from
  C++. They evaluate all of their operands from left to right, even if they have
  an inevitable result and could safely terminate early.
- As in Part 2,  all operators are left-associative except for the `=` operator,
  which is right-associative.
- If you want to  use templates for  AST nodes,  the "Operator Classes" from the
  [functional](https://cplusplus.com/reference/functional/) header may help.
- When printing bools, print either `true` or `false`.
- When printing `if` / `else if` / `else` blocks, an `else if` should print with
  the `if` nested inside the curly braces of the `else`.
- The quote is funnier if you know who Rasmus Lerdorf is.
