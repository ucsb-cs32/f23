# Part 1: A Calculator

> A complex system that works is invariably found to have  evolved from a simple
> system  that worked.  A complex system  designed from scratch  never works and
> cannot be patched up to  make it work.  You have to  start over with a working
> simple system. _- John Gall_

We want to write  a programming language.  But writing a programming language is
hard, so we'll start with something simpler: a calculator.  A calculator has two
main parts, and these are the two "tracks" your group will work on this week:

- The **lexer** reads raw text and translates it into a sequence of tokens, like
  `+` or `(` or `4.0026`. This track is mostly about low-level coding and string
  manipulation.  Try to finish the lexer early, because it's used by the parser.

- The **parser** takes a sequence of tokens and builds an "abstract syntax tree"
  (AST)  that represents the calculation  described by the input.  This track is
  mostly about data structure design and recursion.

This AST is the ideal representation  of an expression (or a program).  Once you
have an AST,  most other operations -- like evaluating it or printing it in some
other format -- are extremely easy.


## Background: S Expressions and ASTs

Parsing human-readable expressions is surprisingly difficult,  so we're going to
start with something easier: S expressions. The S expression `(★ a b ... z)` for
binary operator `★` is equivalent to the infix expression `(a ★ b ★ ... ★ z)`.

More formally, an S expression consists of either...

- a left parenthesis, followed by an operator, followed by at least one S
  expression, followed by a right parenthesis; or...
- a number.

For example, take this infix expression and convert it into an S expression:

```
1 + 2 * 3 * 4
```

Depending on whether you treat multiplication as left- or right-associative, you
should end up with  one of the top two S expressions.  Or, if you take advantage
of S expressions' ability to condense repeated operations, you can get the third
S expression as well.  All of these evaluate to the same value: 25.

```
(+ 1 (* (* 2 3) 4))
(+ 1 (* 2 (* 3 4)))
(+ 1 (* 2 3 4))
```

Each of these expressions  has a different order of operations,  and this can be
seen in their abstract syntax trees:

```
  (+)       |    (+)          |    (+)
 /   \      |   /   \         |   /   \
1    (*)    |  1    (*)       |  1    (*)
    /   \   |      /   \      |      / | \
  (*)    4  |     2    (*)    |     2  3  4
 /   \      |         /   \   |
2     3     |        3     4  |
```

Each node  in an AST is either  a constant or  an operation.  The children of an
operation node are  its operands.  To evaluate an  AST node, first  evaluate its
children,  then perform  that node's operation on the results.  The operation at
the root is always performed last.

For a more complicated example, see the parser section (Track B).


## Setup

Since this is  the first time  you've worked on this project,  you'll need to do
some setup work before you're ready to work on features.

### GitHub Setup

- Make sure all your group members have GitHub accounts.
- Have an arbitrary group member create a GitHub repo for this project.
- Add all the other group members as collaborators on the repo.
- Find a TA for your group and add your TA as a collaborator as well.

### Directory Setup

- Inside your repo, create the nested folders `src` and `src/lib`.
  - C++ files with `main()` functions should go directly inside `src`.
  - All other C++ files (including headers) should go inside `src/lib`.
- Create a `README.md` file at the root of your repo.

### Interface Setup

- Working as a whole group, create header files for the following objects:
  - A token struct that contains information about one token.  This should be at
    least: the line and column numbers  of the first character of the token; and
    the text of the token exactly as it appears in the input. The token type may
    be helpful as well.
  - A lexer that takes an input stream and outputs a sequence of tokens.
  - A parser that takes a sequence of tokens and outputs an AST.

Once you think you have all the public functions and members you'll need, you're
ready to split into  feature groups.  Commit your interface code  and push it to
your `master` branch. Then split your group in half, and choose who will work on
each of the following features.  Make sure to work in Git branches!


## Track A: The Lexer

The lexer is in charge of reading text input and transforming it into a sequence
of tokens.  These tokens are the "atoms" of the syntax:  the smallest parts that
an expression can be  broken into  and still  make sense.  The infix  expression
`38 + 4`, for example,  could be broken down into the tokens `38`, `+`, and `4`;
but breaking it into  `3`, `8`, `+`, and `4`  would not make sense,  because the
number `38` is a single entity.

Your lexer should recognize the following tokens.  These may or may not be
separated by whitespace characters in the input.

- Left and right parentheses: `(` and `)`
- Any of the basic binary operators: `+`, `-`, `*`, and `/`
- Any simple floating point number.  These are series of digits, and may contain
  a single decimal point between two digits (but not at the beginning or end).
- A special token that marks the end of the input: `END`

To show that your lexer works,  write a main function in `src/lex.cpp` that runs
your lexer on a file.  This program should take  no command line arguments, read
text from standard input,  and convert that text into a  sequence of tokens.  It
should then print those tokens and their line and column numbers,  one token per
line.  For example, given this input (which ends with a newline):

```
(+(-2 4.444 )
32(* 5 13.45)(
```

Your program should print the following. Columns are line number, column number,
and token; numbers are right-aligned within their columns.

```
   1    1  (
   1    2  +
   1    3  (
   1    4  -
   1    5  2
   1    7  4.444
   1   13  )
   2    1  32
   2    3  (
   2    4  *
   2    6  5
   2    8  13.45
   2   13  )
   2   14  (
   3    1  END
```

If there are invalid characters  (anything that's not a valid token) anywhere in
the input, your program should print  `Syntax error on line L column C.`  (where
`L`  and `C`  are the  line and column numbers of  the unexpected character) and
exit with exit code 1.  Do not print any tokens.  For example, given this input:

```
(/49 50.
12 ($ 7..8 .3))
```

Your program should print only:

```
Syntax error on line 1 column 8.
```

It won't reach the syntax errors on line 2,  but if it did, their column numbers
would be 5, 9, and 12.



## Track B: The Parser

The parser is in charge of reading a sequence of tokens and building an abstract
syntax tree.  For example, given the tokens for this S expression:

```
(* (+ 1 2) 3 (/ 4 5 (- 6 7)))
```

Your parser should construct this abstract syntax tree:

```
     (*)
    / | \
  (+) 3 (/)
 / |   / | \
1  2  4  5 (-)
          /   \
         6     7
```

Note that your parser should always construct  exactly one  AST.  Therefore, its
input  should always contain  exactly one  top-level S expression.  If the input
contains multiple (or no) top-level S expressions, this is a parse error.

To show that your parser works,  write a main function in  `src/parse.cpp`  that
uses the lexer from Track A to turn its standard input into a sequence of tokens
and then  uses  your parser  to turn  that sequence of tokens  into an  abstract
syntax  tree.  Once you  have the  tree,  first  print  it in infix  form  (keep
the parentheses in the same places as in the S expressions,  but print operators
between all of their operands).  Then, on the next line,  print the value of the
expression.  For example, the tree above would print as:

```
((1 + 2) * 3 * (4 / 5 / (6 - 7)))
-7.2
```

In the case of a lexer error,  print the same error message as the `lex` program
would (see Track A) and exit with exit code 1.

In case of a parse error, print an error message and exit with exit code 2.  The
`END` token  (see the lexer section),  makes sure that  all parse errors will be
unexpected token errors, so the error message `Unexpected token at line L column
C: TOKEN` (where `L` and `C` are line and column numbers, and `T` is the text of
the token) will work for all of them.  For example, this input (which does _not_
end in a newline):

```
(- 5 6 (+ 8 9.17 8)
```

Should result in this error message:

```
Unexpected token at line 1 column 20: END
```

You may also encounter an error while evaluating your AST: division by zero.  If
this happens, print  `Runtime error: division by zero.`  and exit with exit code
3.  The full output would look like something this:

```
((1 - 2 - 3) / ((1 + 2) - 3))
Runtime error: division by zero.
```


## Finishing

When your  group  finishes a feature,  open a  pull request  for that feature on
GitHub. Members of the other group should review the pull request before it gets
merged into `master`.  This is their chance to:

- Make sure they understand the code.
- Make sure the code follows the group's coding style.
- Suggest improvements that could make the code cleaner.

Once the reviewers agree that the code looks good, it's ready to merge.

You'll probably want the  lexer group to merge first,  as having a working lexer
will make it easier to test the parser  (in the meantime, though, you can create
token objects directly).

Finally, make sure your repo is clean from an outsider's perspective. You should
have a  `README.md`  file that describes  how your project is organized,  how to
build it (ideally by simply running `make`), and how to use it.  Once this looks
good and all your changes are merged,  you're done.  Submit your `master` branch
to Gradescope.


## Notes

- Tab characters count as one column, just like any other character.
- A whitespace character is anything the [`cctype`](https://cplusplus.com/reference/cctype/)
  functions consider whitespace.
- [`std::istream::peek()`](https://cplusplus.com/reference/istream/istream/peek/)
  may be helpful when writing the lexer.
- See  the [`iomanip`](https://cplusplus.com/reference/iomanip/) header for help
  formatting the output of the `lex` script.
- To make sure your values match the autograder, store your numbers as `double`s
  and use `std::ostream`'s `<<` operator to print them.
- An operator S expression  may have only one argument.  In that case, its value
  is simply the value of that argument.
- When evaluating S expressions with more than two operands, the operator should
  behave as if it were left-associative.  `(- 1 2 3)` should evaluate to `-4`.
- When printing error messages,  make sure there's exactly one newline after the
  message.
- The "exit code" of a program is the value returned from its `main()` function.
  An exit code of zero means success, and non-zero means failure.
- When submitting to Gradescope,  you choose which branch to submit,  so you can
  test code on Gradescope before it gets merged into `master`.
- <https://xkcd.com/297/>
