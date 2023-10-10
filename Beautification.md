# Code Beautification Guide

When working on larger projects  and/or group projects,  it's extra important to
keep your  code and your Git repo clean.  It'll make your TAs love you  and keep
your group members from murdering you in your sleep.


## Code Hygiene

Code is meant for reading, but reading code is even harder than writing code. So
try to make your code as easy to read as possible.

- Use the same coding style for all the code in the project.  There are a lot of
  choices to make here, so I gave this its own subsection, below.
- Use good function and variable names.  A variable named `cats` is far better
  than a comment explaining that `x` is a vector of cats.
- Use comments judiciously.  This can be tricky; see below.

Another big part of readability is keeping things small. Once things get too big
you can no longer hold them in your head in their entirety, and they become much
harder to think about.

- Try to keep your functions under fifty-ish lines. If they get longer than that
  they're probably doing  discrete sub-tasks  that can be broken out into helper
  functions.
- Try to keep  your files under  a few hundred lines.  If you have a  really big
  file, you probably have  a class that's trying to do too much.  See if you can
  break it up into a few smaller classes.
- Don't let your directories get too big either.  If you have tons of files in a
  directory,  you probably have a few groups of related files, and you can group
  these in sub-directories.


### Coding Style

There are a lot of choices that make up a coding style.  Just for names you have
a choice of `BigCamelCase`, `littleCamelCase`, `snake_case`, `Please_Dont_Do_This_Case`,
`kebab-case` (well, not in C++), and `YELLING`. And the choice can (and should!)
be different for different types of names.

Some of the most important choices  are listed below.  The most important thing,
though, isn't what you choose, but that you use your style consistently.

- Indentation: spaces or tabs?  If spaces, how many?
- Variable and function names: what case rules do you use for...
  - Class (type) names?
  - Member variables?
  - Member functions?
  - Local variables?
  - Enums and constants?
- Curly braces: where do they go on...
  - Conditionals?
  - Function calls?
  - Class definitions?
- Operators and brackets: how does the spacing work?

Once your group has agreed on a style, make sure to use it for all the C++ files
in your project.  Code review  can be helpful here;  if you forget to follow the
style, someone else can catch it.


### Comments

Writing good comments is an art.  The best approach,  in my opinion,  is to make
the code as self-explanatory as possible. Using good function and variable names
will make  most comments  unnecessary.  But when your code  still needs a bit of
explanation, add a comment.

Some useful types of comments:

- Explain any non-obvious assumptions the code is making.
- Explain what algorithm you're using (ideally with a wiki link).
- Explain why the code does something (you can figure out how code works by
  reading the code, but not always _why_ it does that thing).

If you're not sure where you need comments, think about code review.  If there's
a section of code  that you expect your group members will ask you about, that's
a good place for a comment.


## Git Hygiene

Git is for the core files of your project.  This typically means source code. If
a file  (like an executable)  can be generated from other files in your project,
it doesn't belong in  your Git repo.  Files that are specific to  your system or
your editor don't belong in Git either; they're your personal configuration, not
shared configuration.  Conveniently, most of these files have predictable names,
and can be listed in a `.gitignore` file.

Here's a more comprehensive list of things you don't want in your Git repo:

- Compiled code, including object files and executables. These can be built from
  the source code, which is committed, so there's no reason to include them.
- Editor config files.  These belong to the individual programmers; they're not
  part of the project.
- Editor temp files.  Certain editors like to store temporary files with names
  like `whatever~` and `.whatever.swp` in your working directory.  These might
  be useful locally, but in a Git repo they're just junk.
- Code that's been commented out. Just delete it.  If it turns out that it was
  important, you can find it in your Git history.

Git is also how you keep track of  old versions  of your project.  Since you'll
occasionally  want to go back and look at the code from  an earlier version, you
should make sure to use reasonable commit messages. These can be brief, but they
should say what you changed;  if all your commit messages are "dsklfhask" you'll
never be able to find anything.

And finally, Git is how you keep track of the official, working version of your
project: any code on the `master` branch should be known to work and agreed upon
by all group members.  To ensure this, it's important to use feature branches,
pull requests, and code review:

- Never commit directly to the `master` branch.  Create a feature branch and
  work there.  When your feature is complete, open a pull request.
- Always get code review before merging pull requests into `master`.  This
  ensures that everyone has a chance to review and understand your changes.
- Only merge working code into `master`.  Hopefully that's obvious...
- When starting a new feature, always branch off of the `master` branch.  This
  ensures that you start from the latest working version of the project.


## Talking to Strangers

Finally,  you should make sure that  people who are unfamiliar with your project
are able to become familiar with it easily.  In this class,  that means the TAs;
in the real world, this will be people who find your projects on GitHub and want
to use them and/or contribute.

The best way to do this is to have a `README` file in the root of your repo that
gives  an overview of the project  (this is often a `README.md` file;  the `.md`
extension means it uses  Markdown  syntax for prettier  display).  A good readme
will summarize:

- What the project does, and why.
- How to build the project (the fewer commands the better; a single `make`
  command is ideal).
- How to use the executables once they're built.
- An overview of how the code is organized.
