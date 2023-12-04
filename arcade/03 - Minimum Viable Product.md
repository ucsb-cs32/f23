# Part 3: Minimum Viable Product

In this checkpoint,  you'll take your  proof-of-concept window from the previous
checkpoint and turn it into a complete and playable game.  It doesn't need to be
complex, but it should have all the things a game needs.


## Required Features

Your final game should have all of the features described below. Exactly how you
divide these up  will depend on how  your game and  your group are organized, so
they aren't divided into tracks; divvy them up as you see fit.


### Mechanics

First of all, make sure your game mechanics are complete.  Consider the simplest
possible version of the game you're trying to make. What interactions need to be
part of that game?

Some mechanics will be consistent across all games.  They all need a way to move
the player character, and logic to control the non-player characters.  But other
mechanics will depend on the game:

- In a shopping game, you'll need to be able to buy and sell thing.  You'll also
  need to be able to see your inventory and the amount of money you have.
- In a shooting game,  you'll need to be able to shoot  and be shot.  Any object
  that gets hit by a bullet  -- you or an enemy --  should take damage,  and any
  object that takes enough damage should die.
- In a car racing game,  the user should be  able to control  not just steering,
  but also shifting and acceleration.  Going off the intended route or colliding
  with other racers should slow you down or throw you off course.

### Scoring

Like all classic arcade games, your game should have some way to keep score. The
scoring mechanism will depend on your game.  Some examples:

- In a racing game, time taken to complete the race.
- In a fighting game, you could kill enemies to earn points.
- In a survival game, the longer you survive, the higher your score.
- Many games have collectibles that give you points, like the coins in Mario.

Your score should be visible on screen while playing the game.

### Game Over

Your game also needs to end.  Games that go on forever  aren't very interesting;
you'll want a way to  bring the game naturally to a close.  This too will depend
on the type of game you're writing:

- Level-based games have a  natural ending:  the end of a level.  Once you cross
  the finish line  in a racing game  or defeat the boss  in a fighting game, the
  game is over.
- Deadline-based game also have a built-in ending: the deadline. If your game is
  "type as many of these words as you can  in one minute"  then the game is over
  after one minute.
- Survival games are trickier. There's often no natural ending, and the player's
  goal is to survive as long as possible. If your game is one of these, make the
  difficulty of your game increase over time; this way, better players will last
  longer, but everyone will eventually lose.

Since we're aiming for fast and simple games  (and fast and simple grading), try
to make an average game last between one and two minutes.

### End Screen

Game over.  Now what?

When the game ends,  your program shouldn't  just stop.  There should be a "Game
Over" screen that lets the player rest and shows some vital stats:

- Did you win or lose?
- What was your final score?

And while it's not required, it's a good idea for this screen to give the player
an easy way to either exit the game or to play again.


## Bonus Features

Finished early?  Here are some features you can add for extra credit.

### Start Screen

It can be a bit jarring to be dropped into a running game as soon as you start a
program. It's better to have a "Ready" screen that waits for the player to start
the game by performing some action.  This screen is also a good place to display
the controls you use to play the game.

### Varied NPCs

Make your game more interesting by adding more types of NPCs.  These NPCs should
behave differently from the ones you added for the simple mechanics section.

### Leaderboard

Classic arcade games keep track of the highest scores  that players have managed
to earn.  Add this feature  to your game.  Your end screen  should show how  the
current score compares to the top scores; if the current score qualifies, add it
to the list.  You don't need to record player names alongside the scores.


## Notes

- FreeGLUT includes some functions that can draw text to the screen.
- Not sure which  OpenGL functions to use?  This page is a great write-up of the
  history of OpenGL,  and implicitly shows which sets of functions  go together:
  <https://io7m.com/documents/history-vertex-spec/index.xhtml>
- Is your  player character's motion  spastic  because it's tied to the OS's key
  repeat settings?  Try turning off key repeat in GLUT and tracking the state of
  the motion keys in separate variables (or track velocity directly).  Then move
  the player character in your `update()` function.
