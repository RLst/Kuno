# Kuno - AI & Pathfinding

Tony Le
2018

This was my first year Artificial Intelligence and Pathfinding assessment at the Academy of Interactive Entertainment.

The original intention of Kuno was to be an isometric point and click real time strategy game similar to the likes of Commandoes or Desperadoes, but set in feudal Japan instead.

Unfortunately, the scope of the project was much more larger than I anticipated. An insane amount of effort was put into this project. There were many late sleepless nights. But considering the allocated duration of the assessment I had, I am pretty proud of the eventual outcome.

Features and functionality implemented:
- AI Behaviour Tree
- A* and Dijkstra pathfinding
- RTS style camera controls
- Sprite z depth sorting so that sprites don't appear incorrectly behind or in front of another sprite
- Isometric systems and functions to convert between various different coordinate systems
- Hand drawn tilesets
- Debug system: see various system values, toggle tile node connections, toggle display of path

Known bugs:
- Upon shutdown of app, will crash while app is trying to clean up memory. Maybe some of the AI classes don't have correctly written destructors.
- Some performance hits (especially in Debug mode) when agents interact with player ie. seek or flee. Causes weird jitters where agents have a hard time moving probably because the frame rate drops so low that delta time goes out of whack.
- A* algorithm doesn't correctly take into account cost
- Dijkstra algorithm tends to add in unnecessary zig-zags

### Updates
17 Oct 2018
Copied repo from bitbucket to github.
Will include AIE bootstrap so that the whole thing works as a unit when pulled.

4 Mar 2019
Big clean up and revamp of the project. Designed a new map with castle, moat, obstacles and paths to better illustrate pathfinding. Brightened up the tiles. Moved all imgui debug windows into one main big window with collapsible panels.
