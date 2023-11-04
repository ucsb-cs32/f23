# Part 4: Completion

> In the long run every program becomes rococo - then rubble. - _Alan Perlis_


Now that we have  basic control flow  taken care of,  it's time to add some more
powerful  language features:  functions and (resizable) arrays.  Either of these
would make our language Turing complete -- able to calculate anything that could
possibly be  calculated.  And they're critical for human-friendly programming as
well, so let's do both.


## Track A: Support

The main tracks for this checkpoint  have some things in common.  To avoid extra
work (and merge conflicts),  you should implement  the following before starting
on the feature tracks. You can merge these to `master` if you want, but remember
to use a pull request and get code review if you do.

- Add lexer support for two new tokens: the comma (`,`) and the semicolon (`;`).
- Update your parser so that  all statements that end with expressions (for now,
  that's `print` and bare expressions) require a trailing semicolon. Update your
  AST printing function to match.
- Update your parser and AST so that  assignments to non-variables (like `1 = 2`
  or `x + 3 = 4`) no longer cause parse errors, but are reported at runtime with
  the message `Runtime error: invalid assignee.` instead.
- Update your `==` and `!=` operators so that two values of different types will
  always compare as not equal (as opposed to throwing a type error).


## Track B: Functions

To support functions,  you'll need to add  two new types of statements,  one new
type of expression,  and two new value types.  The new  statements are  function
definition  and  `return`.  The new expression is a  function call.  And the new
types are functions and `null`.  The function type allows functions to be stored
in variables; `null` is what functions with no explicit return value return.

Once you have functions implemented, you'll be able to accept code like this:

```
z = 42;

def foo(x, y) {
  def square(value) {
    return value * value;
  }

  print square(x + y + z);
}

z = 108;
f = foo;

result = f(1, 2);
if result != null {
  print result;
}
```

Run through `format.cpp` it'll look like this:

```
(z = 42);
def foo(x, y) {
    def square(value) {
        return (value * value);
    }
    print square(((x + y) + z));
}
(z = 108);
(f = foo);
(result = f(1, 2));
if (result != null) {
    print result;
}
```

And when evaluated, it'll print:

```
2025
```

More formally, a function definition statement consists of...
- the keyword `def`, followed by...
- an identifier (the name of the function), followed by...
- a left parenthesis, followed by...
- a comma-separated list of zero or more identifiers, followed by...
- a right parenthesis, followed by...
- a braced block (the function body; see Part 3).

A return statement consists of...
- the keyword `return`, followed by...
- zero or one expressions, followed by...
- a semicolon.

And a function call consists of...
- an expression, followed by...
- a left parenthesis, followed by...
- a comma-separated list of zero or more expressions, followed by...
- a right parenthesis.

Note that the  left parenthesis can now serve two roles.  If it appears after an
operator (or at the beginning of an expression), it acts as it has since Part 2.
But if it appears after a value, it results in a function call. You can think of
it as an operator with two forms:  as a prefix operator, it does grouping; as an
infix operator,  it calls functions.  It has a higher precedence  than any other
operator.

### Scope

Until now,  all variables have been in a  single scope -- what you might as well
call global scope.  Now that we have functions, though, we also have the concept
of local variables:  variables defined inside a function should be local to that
function,  and shouldn't pollute the  global scope.  That is, all our non-global
variables have what's called "function scope."

When a program starts,  the current scope -- or enclosing scope -- is the global
scope. All variable assignments and function definitions will modify this scope.
But when evaluating a function call, the function gets a fresh scope.  Variables
created  or updated inside  the function will  modify this local scope,  keeping
the outer scope clean.  When the function returns,  its local scope is discarded
and the scope that was active before the function call becomes active again.

Our functions are closures; when a function definition is evaluated, it captures
all of the variables currently accessible in its enclosing scope.  Variables are
captured by value; if a variable in the enclosing scope gets a new value after a
function is defined, the function will continue to use the old value.

### Evaluation

Evaluating a function definition  creates a new function,  but does not evaluate
it.  It then stores the function in a variable in the enclosing scope;  the name
of this variable is the function name. Finally, it captures all variables in the
enclosing scope, and stores the captured values with the new function.

Evaluating  a function call  creates a  new scope.  This new scope  is initially
populated with  the variables that were captured when the  function was created.
Then  the values passed  in to the function call are  assigned  to the variables
named as arguments in the function definition.  Then the body of the function is
evaluated  in this new context.  The value  of the function call  depends on the
return statement  that terminates the function.

Evaluating a  return statement  with no expression  terminates the  function and
returns `null`. Evaluating a return statement with an expression first evaluates
the  expression,  then terminates  the function;  it returns the  value that the
expression evaluated to.

If execution reaches the end of a function  without reaching a return statement,
that function call returns `null`.

### Error Handling

Functions introduce a few new types of runtime errors.

- Trying to call  something that isn't a function,  like `7(9)`,  should throw a
  runtime error with the message `Runtime error: not a function.`
- Trying to call a function with an incorrect number of arguments should throw a
  runtime error with the message `Runtime error: incorrect argument count.`
- A return statement at the top level (not inside of any function) should result
  in a runtime error with the message `Runtime error: unexpected return.`


## Track C: Arrays

To support  arrays, you'll  need to add a  new value  type and two or  three new
expression types.  The value type is,  predictably, arrays.  The expressions are
array literals,  array lookups,  and array assignments.  These mostly  behave as
you're used to from other languages.

But note that arrays behave like they do in C and Python!  The value of an array
variable is a pointer to its data, and only the pointer is copied on assignment,
so modifying the items of a "copy" will change the items of the original.

```
array = [true, 2, 1+1+1, 4, [5]];
print array[2];
print array;

arref = array;
temp  = arref[1];
arref[1] = arref[3];
arref[3] = temp;
print array;
```

Run through `format.cpp`, this would become:

```
(array = [true, 2, ((1 + 1) + 1), 4, [5]]);
print array[2];
print array;
(arref = array);
(temp = arref[1]);
(arref[1] = (0 - arref[3]));
(arref[3] = (0 - temp));
print array;
```

And when evaluated, it would print:

```
3
[true, 2, 3, 4, [5]]
[true, -4, 3, -2, [5]]
```

For a formal definition, an array literal expression consists of...
- a left square bracket (`[`), followed by...
- zero or more comma-separated expressions, followed by...
- a right square bracket (`]`).

And an array lookup expression consists of...
- an expression, followed by...
- a left square bracket, followed by...
- an expression, followed by...
- a right square bracket.

An  array assignment has the  same syntax as an array lookup,  but it appears on
the left hand side  of an assignment operator.  It may or may not be  a separate
AST node type from array lookups, depending on how you structure your code.

Like parentheses,  square brackets mean  different things depending on  where in
the input  you encounter them.  A prefix square bracket  is an array literal; an
infix left bracket is an array lookup. Array lookups have the same precedence as
function calls: very high.  See Track B for more details.

### Evaluation

To evaluate an  array literal,  evaluate each sub-expression from left to right,
then create an array containing all the results.

To evaluate an array lookup, first evaluate the expression in the square
brackets.  Then use this value as an index into the array, and return the value
at that index.

To evaluate an array assignment, first evaluate the value on the right hand side
of the assignment operator.  Then calculate the array index  as you would for an
array lookup.  Finally, replace the item at that index with the new value.

### Utility Functions

To make your arrays  more user-friendly,  we'll add some  utility functions that
let you use them like stacks.  These are special functions -- they can do things
that aren't supported in our syntax -- but they don't get keywords. Instead, add
them to the global scope as variables before you start executing any program.

- `len(array)` returns a number: the length of `array`.
- `pop(array)` pops the value  with the highest index  out of `array`,  reducing
  its length by one.  It returns the popped value.
- `push(array, value)`  pushes a value  onto the end of `array`,  increasing its
  length by one.  It returns `null`.

### Error Handling

Arrays introduce a surprising number of ways in which things can go wrong. These
should all be reported as runtime errors:

- Using a  non-number value  as an array index  should result in a runtime error
  with the message `Runtime error: index is not a number.`
- Using a number with a non-zero fractional part (use the `modf()` function from
  `cmath` to check this) as an array index should result in a runtime error with
  the message `Runtime error: index is not an integer.`
- Using an  array lookup  (or assignment)  on a value that isn't an array should
  result in a runtime error with the message `Runtime error: not an array.`
- Using an integer that does not correspond to  an item in  an array (because it
  is less than zero,  or because it is greater than or equal to the  size of the
  array) should result in a runtime error with the message `Runtime error: index
  out of bounds.`
- Calling any  of the array utility functions  with a first argument that is not
  an array should result in a runtime error with the message `Runtime error: not
  an array.`
- Trying to pop  from an empty array  should result in a  runtime error with the
  message `Runtime error: underflow.`


## Type Notes

Most of the new types have  minimal operator support, but this wasn't explicitly
stated above.  Here's the complete specification,  plus some additional notes on
the types and how to print them.

### Null

- The `null` value is the only value of its type.
- It only supports the (in)equality  comparison operators: `==` and `!=`.  It is
  only equal to itself.
- It prints as `null`.

### Functions

- Function values do not support  any arithmetic or logical operators.  They may
  or may not support the (in)equality operators; this is not tested.
- Printing a function gives the same output as `format.cpp`,  but without any of
  the surrounding code or extra indentation.

### Arrays

- Note that closures can modify the contents of captured arrays!
- Arrays only support the  (in)equality operators.  Two arrays  compare as equal
  when they have the same length and contain items which compare as equal.
- Arrays print on one line, enclosed in square brackets, with items separated by
  a comma and a space.


## Other Notes

- Commas only occur in function definitions, function calls, and array literals.
- If you need a way to deal with semicolons on bare expressions, consider adding
  a `DoNode`  AST subclass.  This is a statement node  that wraps an expression.
  Evaluating it evaluates the expression;  printing it prints the expression and
  adds the semicolon.
- What if you implemented `return` with C++ exceptions?
- The  [`std::variant`](https://en.cppreference.com/w/cpp/utility/variant)  is a
  tagged union provided by the standard library.  Useful for storing values!
- Memory management  is getting tricky  with scopes and array references.  Using
  [`std::shared_ptr`s](https://en.cppreference.com/w/cpp/memory/shared_ptr)  may
  simplify things.
- You can pass most of the array tests  without having the utility functions, so
  you can start working on arrays before the Track B group finishes.
- The autograder won't create cycles with array references, so you don't need to
  worry about that particular memory leak.
- <https://xkcd.com/312/>
