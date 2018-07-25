## Overview
View: 2D, isometric
Game style: Ninja stealth based
(stuff in brackets means "maybe to be implemented")

**OBJECTIVE 1: VERY BASIC IMPLEMENTATION for bare minimum assignment criteria (according to my standards)**
- Player can walk, run, sneak, roll, attack and stealth attack only. No special complicated moves like jumping or grappling hook
- Player can throw rocks (to demo Suspicious > Inspect)
- Enemies will not react to ally corpses (enemies fade and despawn soon after death)
- Map only has essentially 2 layers: Ground and Walls

## Agents
### Types
#### Player 
- Okuma Yuna

#### Enemies
- Samurai Swordsman
- Samurai Bowmen
- Lord

### Abilities, states and animations
#### Player
States:
Normal - Walk: Walk, Run: Run, Attack:
Stealth - Sneak: Sneak, Roll: Roll
Attack - Normal Attack: Normal Attacks, Stealth: Stealth Attack

- Walk (normal, slow)
- Run (normal, fast)
- Sneak (stealth, slow)
- Roll (stealth, fast)
- Attack
- Stealth Attack
- Fast stealth attack (
- (Grab ledge)
- (Jump)
- (Grappling hook)

Animations:
Normal - Idle, Walk, Run, Throw
Stealth - Sneak, Roll, Throw
Attack - NormalAttack, StealthAttack

#### Enemy
Normal - Idle: Idle, Patrol: Walk
Suspicious - Inspect: Walk, Return to post: Walk
Alert - Attack: Attack[], Knock back, Shift, Pursue: Run, Seek: Run, Flee: Run, Death: Death

Animations:
- Idle
- Walk
- Run
- Shift
- Attack[]
- Death

### Pathfinding: A*
- Within Map class
- std::vector<pkr::Vector3> getAStarSearch(startPoint, endPoint)
- the A* function returns a path (a list of points) that the agent will go through

### Patrolling 
Patrol paths

## Mapping system
### Node class
Holds essential node data crucial for the pathfinding system such as:
- Parent node
- F/G/H scores
- Connections[]

### Tile class
Holds essential tile data such as:
- Texture
- Texture offset
- Position
- Height?
- 
- (Tint)

### Map class
- Responsible for drawing essentially all non-gui sprites:
map tiles, interactive game objects, player and enemy agents, other images
- Holds an 2 dimensional array of Tiles

### Layers:
1 (Highest)
Wall tiles, game objects, agents
Ground tiles
100 (Lowest)

## GUI
- Called and drawn last (to be placed on top most sprite layer)
- Sprite depth of 0 or 1 (highest)
- Separate group of sprites that follows the camera
- Maybe use imgui for debugging purposes first
- Also controls the camera movement

## Image manager
Holds a copy of each texture so that for example each tile don't have to each hold a texture which will take up unnecessary space

## Animations
Need a way to animate

if (m_animated) 
{
	srcRect.x = srcRect.w * static_cast<int>((deltaTime / m_animationSpeed) % m_frames);
}
