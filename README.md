# Kuno - AI & Pathfinding

Tony Le
2018

This was my first year Artificial Intelligence and Pathfinding assessment at the Academy of Interactive Entertainment.

The original intention of Kuno was to be an isometric point and click real time strategy game similar to the likes of Commandoes or Desperadoes, but set in feudal Japan instead.

Unfortunately, the scope of the project was much more larger than I anticipated and it is incomplete. An insane amount of hours and effort were put into this project. There were many late nights. But considering the total allocated duration of the assessment I had, I am proud of the eventual outcome.

Features and functionality implemented:
- AI Behaviour Tree
- A* and Dijkstra pathfinding
- RTS style camera controls
- Sprite z depth sorting so that sprites don't appear incorrectly behind or in front of another sprite
- Isometric systems and functions to convert between various different coordinate systems
- Hand drawn tilesets (programmer art ;D )
- Debug system: see various system values, toggle tile node connections, toggle display of path

Things that could be improved:
- If an agent is on a path, he is fully commited on that path until he reaches the end and there is no way to cancel out of it as of now. I tried implementing the set path function so that it can be cancelled out or overridden but it led to some weird behaviours. Perhaps look into how Unity implements it?

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
