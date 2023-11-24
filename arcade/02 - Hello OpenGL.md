# Part 2: Hello OpenGL

In this checkpoint,  you'll lay the foundations of your game code.  You'll start
by writing code to open an OpenGL window. Once this is done, you'll add a player
object that the user can control and some NPCs that move automatically.


## Track A: The Window

Before  you can do any graphics work at all,  you'll need to open a window.  The
code to do this  will be the "shared basis" of your Git repo;  your entire group
should work together on this,  and push the finished code to `master` as soon as
possible. Once this is done, you can split into two subgroups and work on Tracks
B and C.

First, figure out how to open a window using OpenGL and GLUT (the OpenGL Utility
Toolkit). Then, once you're able write a program that opens a window, add a main
loop.  This simple loop is the heart of most games: it sleeps for a frame, calls
an  `update()` function that  updates the states of all the objects in the game,
then calls a `render()` function that draws all of the objects to the screen.

```cpp
int main() {
  // initialization

  while(running) {
    sleep(33); // 33 ms = ~30 fps
    update();
    render();
  }

  // cleanup
}
```

While it's possible to process and draw objects in a single function,  it is not
recommended.  To keep your program manageable,  your functions should follow the
same philosophy as the Linux  command line tools (`ls`, `mkdir`, etc.):  Do _one
thing_ and do it well.

Once you have your window code running, push it directly to your `master` branch
so you can use it as the base for your feature branches.


## Track B: The Player

Now it's time  to add some agency.  Create an object to represent the player and
draw it to the screen (just a box is enough for now, although an image will make
it more satisfying to mess around with).  Then add user input handling that lets
the user move the player object with the keyboard and/or mouse.


## Track C: Some NPCs

The game world should have some agency as well. Create at least three non-player
objects  (these can all be instances of  the same C++ class)  to represent other
entities in the game world.  Draw them to the screen.  Then add logic that makes
them move automatically as the game runs.


## Submission

Once you've finished and merged all three tracks, submit your `master` branch to
Gradescope.  There is no auto-grader for this project; your submission is simply
a placeholder where were can attach scores from manual grading.

During your selected time slot on Friday,  your TA will download your submission
from Gradescope,  build it on a CSIL computer, and play your game.  Your TA will
follow your documentation  while doing this,  so make sure you have instructions
for compiling, running, and interacting with your game.


## Notes

- You are encouraged to work on your local computer  to avoid networking trouble
  and for a  generally better experience (running graphics over SSH is possible,
  but choppier than running locally).  However...
- Your code _must_ compile and run on the physical computers in CSIL. The Phelps
  3525 (CSTL)  computers are configured  the same as the CSIL computers,  so any
  program that runs on one should run on the other.
- The CSIL computers have OpenGL version 4.3 installed.
- Only the  features listed above are  required for this checkpoint,  but if you
  want to add other things that your final game will need,  you're encouraged to
  do so.  The next checkpoint will be a minimal playable game, so anything extra
  you do here will give you a head start.
