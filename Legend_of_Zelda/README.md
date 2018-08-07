3D Game "Legend of Zelda" in Opengl(GLFW)
=================

### Compiling the game:

```
cmake CMakeLists.txt
make
```

### Running the game:

```
./graphics_asgn1
```

### Rules of the game:

* Move the boat using arrow keys.
* Kill the different types of monsters to score points.
* After killing 3 monsters, a boss will appear who is difficult to kill (Get killed in 3 shots and will reduce your health by higher amount then normal monster).
* There are rocks on the sea. Colliding with them reduces your health. 
* You can destroy the rocks/monsters/boss by shooting with cannon balls.
* A wind appears at certain intervals of time and it can move the boat along its direction which can be any of the four directions.
* There are barrels floating on the sea with gifts above them which can be collected by jumping over them.
* On killing a boss,  a booster appears which when taken increases your speed for some amount of time.
* The game can be viewed through different camera views such as Follow, Helicopter, Boat, etc.

### Controls :
* Game can be played by keyboard using following controls.
* Helicopter view can be accessed using mouse.

#### Keyboard Controls

|     KEY     |      ACTION      |
| :---------: | :--------------: |
|      f      | Fire Cannon Ball |
|    Space    |       Jump       |
|  q or esc   |       Quit       |
|  up arrow   |   Move Forward   |
|      c      |   Change View    |
| left arrow  |   Rotate left    |
| right arrow |   Rotate Right   |

### Features:
* Game has background music.
* Score & Health are shown in window bar.
* Monsters and Boss automatically disappears and appear closer to you to destroy you.
