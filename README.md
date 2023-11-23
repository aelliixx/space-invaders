# SPACE INVADERS

This project is a Space Invaders clone with a few changes to its gameplay.
These include:

- Player has a health range from 0-100 and requires taking four to five hits before dying.
- Octopus enemy can take one to two hits before dying.
- Aliens have a small chance of dropping a health pickup when killed.

This took around 15-18 hours to complete spread over three days.

Core gameplay functionality was done in roughly 5 hours, the rest was spent on polishing,
introducing new alien types, tweaking the visual looks, etc.

## Technical Details

Built with **Unreal Engine 5.3.1**.

No blueprints other than for widget layout.

## How it works

### Player

AShipPlayer is the default pawn class for the game which inherits from APawn. It is
controlled by AShipController. Player pawn initialises player movement, handles input
for pausing and firing projectiles.

AShipController has UHealthModule and UScoreModule:

UHealthModule is used both for player and alien health management. It keeps track of
maximum and current health, enables damaging and killing its owner, and broadcasts a delegate
whenever current health has changed or the owner is killed.

UScoreModules keeps track of player's current score and broadcasts a delegate when it 
changes.

### UI

UI was naturally the focus of this project. Health-bar and score widgets work
by registering a callback when `HealthModule` or `ScoreModule` delegates are broadcasted.
This is a typical implementation seen in most Unreal projects and works quite well for a
small game like this where game logic won't change much. 

`AHUDManager` is a `AHUD` class which handles showing and hiding most UI/HUD elements and
holds pointers to active widgets. On Begin Play, the manager checks what level the player is.
If it is `MainMenu` it adds the `UMainMenu` widget to viewport, otherwise, it adds
`UPlayerHUD` to viewport.

`UPlayerHUD` is a `UUserWidget` class which is merely a container for the health-bar and
score widgets.

All widget logic is done in C++ but the visual look and layout was done in blueprints.

### Enemies

There are two types of enemies: crab and octopus. They're each worth 10 and 20 points 
respectively and fire at random intervals. Aliens are spawned in a grid in stages.

The game starts at stage 1 and it increments each time there are no more living aliens
remaining. The grid layout is defined in a datatable (`DT_GameStages`). Once the player
finishes all stages, the stage counter wraps around back to 1.

Alien grid (`AEnemyGrid`) moves in world-space once every second and wraps around to
the left edge when it reaches the right edge. These edge bounds are also defined
in the datatable.

### Projectiles

Projectiles have a `UProjectileMovementComponent` which facilitates their movement.
When a player or an alien fires a projectile, they set its initial direction, velocity,
and damage range. Projectile collision profiles can either be `PlayerProjectile` or
`EnemyProjectile`. These collision profiles ignore players and enemies respectively but
can destroy other projectiles (including health pickups).

### Saving / loading

When the game starts, we find the save game data named `Leaderboard`. Upon player's death
the leaderboard is updated and saved to the disk.

## If I had more time...

There are certain aspects of this game that I would do differently or add to if I had more
time to do so. These include:

- A more robust and future-proof dataflow for UI state:

While the use of delegates for updating the UI state is fine for a small game like this, it 
wouldn't hold up in a larger project where the gameplay logic may change over the lifetime
of the development. Ideally, the UI should hold it's own state instead of depending on the
game logic to update it.

- Reusable user widgets for common UI elements

I would've liked to created reusable widgets for common elements (such as buttons, text blocks and fields, etc.) that defined their style. This would've reduced the workload
for styling buttons and text blocks.

## Full feature set

- Two alien types: crab and octopus
- Health pickups
- Leaderboard
- Saving and loading leaderboard state between sessions
- Datatable defined enemy grid layout
- Health module
- Score module
- Pausing