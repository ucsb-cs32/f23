# Hacking 101

In class,  I've been compiling and running  these binaries in a Docker container
running Ubuntu 18.04.  They should work on any Linux system,  but code addresses
will change! The exploit scripts probably won't work on newly compiled binaries,
as the internal layout will be different.

If you want to try hacking these, the following references will be invaluable:

- ASCII Table: <https://xavierholt.github.io/cheatsheets/ascii.html>
- Pwntools Cheatsheet: <https://xavierholt.github.io/cheatsheets/pwntools.html>
- GDB Cheatsheet: <https://xavierholt.github.io/cheatsheets/gdb.html>


## The Challenges

- `echo1`  A simple echo server with a classic buffer overflow. Use `readelf` or
  `objdump` to get your target address,  then smash the stack and  overwrite the
  saved instruction pointer.

- `echo2`  Like `echo1`,  but with a loop and a stack canary.  Now you'll need a
  leak so you can overwrite the stack canary with the expected value.

- `echo3` Like `echo2`, but with address space layout randomization. You'll need
  to leak a code address so you can calculate your target address.

- `echo4`  Like `echo3`,  but without that  oh-so-convenient `debug()` function.
  Assemble some shellcode, write it to the (executable!) stack, and jump to it.

- `echo5`  Like `echo4`, but the stack is no longer executable.  Use `onegadget`
  to find an address in `libc` that you can jump to,  then leak a `libc` address
  to calculate its current location.
