PACMAN Killer in OpenGL (GLFW)
=================

### Compiling the Game:

```
cmake CMakeLists.txt
make
```

### Running the game:

```
./graphics_asgn1
```

### About the Game and bonus implemented:

* Basic aim of the game is to score as much as you can by killing the enemy balls.
* 3 lives are given to complete the game.
* There are 7 levels in the game.
* A magnet appears randomly in either side of the game from level 2 onwards and attracts the ball towards itself with constant acceleration.
* There is a porcupine which appears from level 3 onwards. Touching this porcupine will reduce your life.
* The trampoline can be used to jump higher than normal.
* There is a semi-circular pond in which motion slows down.
* The player gets reflected by the plank which appear on some enemy balls according to laws of reflection.
* To reach a particular state, you have to score required points in required time.
* You will lose the game if you lose all your lives or you didn't scored required points in given time.
* Score, level, lives remaining and time left is shown.
* Apart from these there are two special enemy balls:
  * *Green*: If you destroy this ball, all the surrounding enemy balls gets destroyed and you will get points accordingly.
  * *Black*: If you land on this ball, then you will lose your one life and all the surrounding enemy balls disappear for a while and you will not get any points for them.

### Controls :
* Player can play by keyboard.
* Zooming and Panning can be done using the mouse.

##### Keyboard :

|     KEY     |     ACTION     |
| :---------: | :------------: |
|    SPACE    | Move Up / Jump |
|      A      |   Move Left    |
|      D      |   Move Right   |
|  q or esc   |      Quit      |
|  up arrow   |     Pan Up     |
| down arrow  |    Pan Down    |
| left arrow  |    Pan Left    |
| right arrow |   Pan Right    |


#####Mouse :
* Scroll down to Zoom out.
* Scroll up to Zoom in.
* Mouse click and drag for panning.
