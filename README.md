## Execute:
<br>1.Create a build folder(mkdir build)
<br>2.cd into build folder(cd build)
<br>3.run : cmake ..
<br>4.run make all
<br>5.compile ./graphic_asgn1

## CONTROLS:
<br>SpaceBar- Jump
<br>Left/Right Arrows- Navigation
<br>Up/Down- Shoot waterballoons in Up/Downwards

## How Game Works?
<br>-> By collecting coins of different colours your score is increased accordingly.
<br>-> Magnets and Circular Rings Randomnly appear which effect your movement.
<br>-> Once when enter the Semicircular Ring you tend to move in semicircular path and you are protected from the enemies.
<br>-> The game has 4 enemies Firelines, Firebeams, Bomerang and Viserion when collided with your player, loses lives.
<br>-> Your plauer can use Up/Down keys to throw waterballoons on Firelines and Firebeams to kill them.
<br>-> There are 3 different kinds of SpecialObjects, when collected gives you bonus like Shield, SpeedUp, Knives respectively.
<br>-> Shield protects you from all the enemies.
<br>-> Using knives you can kill all your enemies (except Viserion)
<br>-> The 4th Enemy Viserion (has no death) moves according to your player's height and throw Iceballs. Player when collides with the Iceball loses life.

## OBJECTS:
<br>->Platform
<br>->Wall
<br>->Player
<br>->Coins
<br>->Enemy1 (Firelines)
<br>->Enemy2 (Firebeams)
<br>->Enemy3 (Bomerang)
<br>->Enemy4 (Viserion)
<br>->FLying Object 1
<br>->Flying Object 2
<br>->Flyinig Object 3
<br>->Magnets
<br>->Circular Ring
<br>->Waterball
<br>->Iceball

## FEATURES:
<br>-> Implemented Basic Physics (like player experiences Gravity, Projectile motion etc..)
<br>-> Player moves in any direction (Using Up/Down)
<br>-> Can Jump by activating his jetpack (On Press Space)
<br>-> Jetpack emits fire
<br>-> Can Zoom In/Out by mouse scroll.
<br>-> Panning of the screen is automatically done when player reaches end
<br>-> Water ballons
<br>-> Score display using 7 segment
<br>-> Different Stages(levelup) and Increase in difficulty with score.
<br>-> Safe zone when inside Semicircular ring.

## BONUS:
<br>->Implemented Enemy4(VISERION) moves according to the player(Y direction) and throw Iceballs on to the player.
<br>->SpeedUp with special flying object 1.
<br>->Knives with special flying object 2.
<br>->Shield with special flying object 3.
<br>->Seven segment display for Score
