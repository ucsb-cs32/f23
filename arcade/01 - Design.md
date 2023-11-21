# Part 1: Design

This is a code-free checkpoint.  Happy Thanksgiving!  But there is a little work
to do to make sure you're ready to start coding when you get back from break.


## Find a Group

First, find a group. It doesn't have to be the same group you worked with on the
previous project, but it can be if you want. It does have the same requirements:
a minimum of two group members, and a maximum of four.

You're advised to form groups of similar skill levels.  This will make sure that
everyone contributes more or less equally, and reduce intra-group conflicts.


## Design a Game

- It must be 2D.  3D graphics  are a lot more work,  we're focusing on the code,
  not the graphics.
- It must use  OpenGL as the graphics library.  Keyboard and  mouse handling are
  available through the  OpenGL Utility Toolkit; you're recommended to use these
  as well.
- It must be real-time: game objects must move on their own, without waiting for
  user input.
- It must be in the "arcade" style,  with simple controls, increasing difficulty
  over time (or per level), no or minimal cutscenes, and fast and easy restarts.
  See [here](https://gaming.stackexchange.com/questions/398347) for a discussion
  of the common features  of arcade games.  You don't need to have  all of these
  properties, but you should have most.
- It must have many -- dozens to hundreds -- of active objects on screen at most
  times during gameplay.  These active objects are things that move or otherwise
  act, not background/landscape objects. Examples would be bullets in a shooting
  game, vehicles in a racing game, customers in a shopping game, etc.

In general, you want to make a game that your TA can sit down and play for five
minutes. And then maybe die, restart, and play another few minutes.  And then be
happy to do it all again the following week.


## Sign Up

Once your group  has decided on a game design,  pick a time slot  on Friday that
your entire group can attend.  You can find the available  slots listed on [this
spreadsheet][signup].  In future checkpoints,  you will meet your TA  in CSIL at
this time to present your work.

For this checkpoint, though, there's no need for a presentation.  For now, enter
the names of your  group members  to one of the  time slots  in the spreadsheet.
Then create a private GitHub repository, and add all group members -- and the TA
in charge of your time slot -- as contributors. Then add the URL of your repo to
the spreadsheet as well.

Finally,  email the TA in charge of your time slot with your game proposal.  Use
the subject line "CS 32 Game Proposal"  and provide the following information in
the message body:

- The names of all group members.
- The time slot your group signed up for.
- A short description of the game you want to make.
- A sketch of a typical moment of gameplay.

Your TA will reply with a confirmation,  and possibly design suggestions to make
your work more manageable or bring it in line with the project requirements.


## Notes

- You will not be graded on your art skills, but your art does have to serve its
  purpose.  Stick figures  are perfectly okay.  White stick figures  on a yellow
  background are not.
- Some classic arcade games you could use for inspiration:
  - [Asteroids](https://en.wikipedia.org/wiki/Asteroids_(video_game))
  - [Centipede](https://en.wikipedia.org/wiki/Centipede_(video_game))
  - [Missile Command](https://en.wikipedia.org/wiki/Missile_Command)
- Some more modern examples:
  - [Luftrausers](https://en.wikipedia.org/wiki/Luftrausers)
  - [Tyrian](https://en.wikipedia.org/wiki/Tyrian_(video_game))
- Some other ideas that'll have plenty of objects on the screen:
  - A racing game in heavy traffic.
  - A market game on a city street with lots of customers.
  - A tower defense game with swarms of weak enemies.
- If you're curious about how crowds of entities move  without running into each
  other,  check out the  [boids](https://en.wikipedia.org/wiki/Boids)  algorithm
  (or "flocking algorithms" in general).


[signup]: https://docs.google.com/spreadsheets/d/1j0vZ91N-0LHXL5b55JSUPONqndUtu6JKhTsqV6h6I3s/edit?usp=sharing
