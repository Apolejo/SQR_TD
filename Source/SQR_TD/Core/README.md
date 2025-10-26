# Core Classes Implementation

This document describes the implemented C++ classes that mirror Blueprint roles for the Square Tower Defense game.

## ATDGameMode (Server-Only Authority)

**File**: `SQR_TDGameMode.h/cpp`

**Purpose**: Server-only authority for match management and validation

**Fields**:
- `bMatchActive` - Whether the match is currently active
- `bLoseOnLivesZero` - Whether to end game when team lives reach zero (default: true)
- `StartingGoldPerPlayer` - Initial gold amount for each player (default: 100)
- `TeamLives` - Total team lives (default: 20)

**Methods**:
- `StartMatch()` - Begins the match and gives starting gold to players
- `EndMatch(bool bVictory)` - Ends the match with victory/defeat status
- `Server_StartNextWave()` - Triggers the next wave via WaveManager
- `ValidateBuild(const FBuildRequest&)` - Validates tower placement requests
- `ApplyGoldToPlayer(APlayerState*, int32)` - Adds gold to a specific player
- `OnEnemyReachedGoal(AActor*)` - Handles enemy reaching the goal

**Events**:
- `OnEnemyReachedGoal` - Multicast delegate for enemy goal events

## ATDGameState (Replicates to All)

**File**: `SQR_TDGameState.h/cpp`

**Purpose**: Replicates shared state to all clients

**Replicated Properties**:
- `CurrentWave` - Current wave number (RepNotify)
- `AliveEnemies` - Number of alive enemies (RepNotify)
- `MaxConcurrentEnemies` - Maximum concurrent enemy limit
- `WaveTimeRemaining` - Time left in current wave
- `IntermissionTimeRemaining` - Time left in intermission
- `PlayersReadyCount` - Number of ready players
- `TotalPlayers` - Total number of players
- `TeamLives` - Current team lives (RepNotify)

**Events**:
- `OnWaveStarted` - Multicast delegate when wave starts
- `OnWaveEnded` - Multicast delegate when wave ends
- `OnAliveEnemiesChanged` - Multicast delegate when enemy count changes
- `OnTeamLivesChanged` - Multicast delegate when team lives change

**Methods**:
- `SetCurrentWave(int32)` - Server-only wave update
- `SetAliveEnemies(int32)` - Server-only enemy count update
- `SetTeamLives(int32)` - Server-only team lives update
- `UpdatePlayersReadyCount()` - Server-only ready count update

## ATDPlayerState (Individual Player State)

**File**: `SQR_TDPlayerState.h/cpp`

**Purpose**: Manages individual player resources and state

**Replicated Properties**:
- `Gold` - Player's current gold (RepNotify)
- `Score` - Player's current score (RepNotify)
- `Kills` - Player's kill count
- `Assists` - Player's assist count

**Events**:
- `OnGoldChanged` - Multicast delegate when gold changes
- `OnScoreChanged` - Multicast delegate when score changes

**Methods**:
- `AddGold(int32)` - Server-only gold addition
- `SpendGold(int32)` - Server-only gold spending (returns success/failure)
- `AddScore(int32)` - Server-only score addition
- `AddKill()` - Server-only kill tracking
- `AddAssist()` - Server-only assist tracking

## ATDPlayerController (Client-Server Communication)

**File**: `SQR_TDPlayerController.h/cpp`

**Purpose**: Handles input and client-server communication

**Components**:
- `BuildSystem` - UBuildSystemComponent for tower placement

**Server RPCs (Client → Server)**:
- `Server_RequestBuildTower(FTowerBuildSpec)` - Request to build a tower
- `Server_RequestUpgradeTower(AActor*)` - Request to upgrade a tower
- `Server_RequestSellTower(AActor*)` - Request to sell a tower
- `Server_SetPlayerReady(bool)` - Set player ready state

**Client RPCs (Server → Client)**:
- `Client_ShowError(FText)` - Display error message to player
- `Client_PlayPing(FVector)` - Play ping effect at location

**Validation Methods**:
- `CanAffordTower(int32)` - Check if player can afford tower cost
- `IsValidBuildLocation(FVector)` - Validate build location

## ATDHUD (Blueprint Placeholder)

**File**: `SQR_TDHUD.h/cpp`

**Purpose**: Blueprint placeholder for UI implementation

**Blueprint Events**:
- `OnWaveStarted(int32)` - Implementable event for wave start UI
- `OnWaveEnded(int32)` - Implementable event for wave end UI
- `OnGoldChanged(int32)` - Implementable event for gold change UI
- `OnScoreChanged(int32)` - Implementable event for score change UI
- `OnTeamLivesChanged(int32)` - Implementable event for lives change UI
- `OnAliveEnemiesChanged(int32)` - Implementable event for enemy count UI
- `ShowError(FText)` - Implementable event for error display
- `PlayPing(FVector)` - Implementable event for ping effect

## Data Structures

**File**: `TDStructures.h`

**FBuildRequest**:
- `Location` - Build location
- `Rotation` - Build rotation
- `TowerClass` - Tower class to build
- `Cost` - Build cost

**FTowerBuildSpec**:
- `Location` - Build location
- `Rotation` - Build rotation
- `TowerClass` - Tower class to build
- `Cost` - Build cost
- `TowerID` - Unique tower identifier

## Blueprint Integration

All classes are designed for Blueprint integration:

- **BlueprintCallable**: Methods that can be called from Blueprint
- **BlueprintAssignable**: Events that can be bound in Blueprint
- **BlueprintImplementableEvent**: Events to be implemented in Blueprint
- **Blueprintable/BlueprintType**: Classes that can be subclassed in Blueprint

## Replication Notes

- **Server Authority**: GameMode methods are server-only
- **Replicated Properties**: GameState and PlayerState properties replicate to all clients
- **RepNotify**: Critical properties use RepNotify for immediate UI updates
- **RPCs**: PlayerController uses reliable RPCs for client-server communication
- **Authority Checks**: All state-changing methods include authority checks

## Usage in Blueprint

1. Create Blueprint subclasses of these C++ classes
2. Override BlueprintImplementableEvent functions in HUD
3. Bind to BlueprintAssignable events for UI updates
4. Call BlueprintCallable methods from Blueprint graphs
5. Use the data structures as Blueprint types for RPC parameters
