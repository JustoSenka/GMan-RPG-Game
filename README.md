# GMan-RPG-Game
2.5D RPG game written in C++. 

Gameplay video: ur-link-wip
|

## Controls 

### Main Game

* **WASD** to to move.
* **Spacebar** to attack.
* **C** to open Skills/**C**haracter Panel.
* **I** to open **I**nverntory.
* **B** to open **S**hop panel. (Only available inside starting town)
* **Spacebar** to attack.
* **1-8** Numbers to perform skill from hot bar.

* **Left Mouse Drag and Drop** to buy/sell items from the shop. Equip Items in inventory.
* **Left Click** on Skills Menu to invest skill Point.
* **Right Click** on Skills Panel to place skills in the hot bar.
* **Right Click** on usable items to use them.

* **P** Change game speed.
* **O** Change resolution (Mouse clicks not precises with non native resolution)

### Map Creator

* **Left Mouse Click** Select object. Indicated by red/white square.
* **Right Mouse Click and Drag** Move around.
* **Spacebar or Middle Mouse Button** Deselect all.
* **Drag and Drop** Object from Game view to change position.
* **Up/Down Arrow Keys** Change Object Hot Bar Pages.
* **Ctrl + D** Delete object from Game View.
* **M** Toggle Minimap.
* **+ / - In Hot Bar** To Increase fence size when it's selecetd in Game View

## Known Issues

* Saved games might not load if System Region settings are set to use , (comma) as a decimal sign. If decimal sign is . (dot), should work fine.  
* Mouse clicks not precise with non-native resolution.

## Features

### Main Game

* 2.5D rendering. Character and enemies will render either in from or behind obstacles depending on their position on Y axis.
* Enemy AI will roam around their spawns in groups, will attack and follow main character if in sight. Can walk around simple obstacles.
* Different drops and drop rate on each enemy. Some drop rare loot which cannot be bought from the shop. (no wiki for the drops, it can be inspected in Map Creator)
* Leveling up and skills with Magic and Stamina systems.
* Game speed is tied directly to framerate. Can be changed using **P** key.

#### Trivia

* Default map name **Map1.map** which is loaded on game startup. It's hardcoded and cannot be changed.
* Default save file name is **Save1.sav** which is loaded on startup. Also hardcoded.
* Game is saved automatically on shutdown. To abort save, kill the game with Task Manager or *taskkill /f*
* Buying from is more expensive than selling back same equipment.

### Map Creator

* Change main character position with Menu Item.
* Drag and Drop objects and enemies from Hot Bar.
* Change enemy, item properties, icons and animations in Database, use Menu Item to open database window for editing.
* Enemy drops and drop rates can also be modified in the Database window.
* It is technically possible to add more objects and more enemies, but they will not show up in the Hot Bar automatically without any code changes thus it will be impossible to use those newly added objects.

## Compilation

Project was created with Borland C++ Builder 6 (2002 I believe). It's quite an ancient piece of software which I do not own anymore. I haven't tried to compile it with any modern IDE. It has Borland specific libraries for drawing on Canvas and .bpr project file extension, might not be trivial to migrate to another build system.

## Source Code

Everything is released under MIT License, feel free to use it. Although, the code is in poor quality. The game was originally created somewhere around 2012, I was still learning programming and didn't really know how to use a lot of C++ features (like classes, structs, common data collections and structures etc). Would not advice using this project as an example to learn programming.
