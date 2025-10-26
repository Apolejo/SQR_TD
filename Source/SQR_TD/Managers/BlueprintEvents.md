# Blueprint Events Documentation

This document describes all Blueprint events available in the WaveManager and EnemySpawner classes for VFX, UI, and gameplay integration.

## Table of Contents
- [WaveManager Events](#wavemanager-events)
- [EnemySpawner Events](#enemyspawner-events)
- [Event Usage Examples](#event-usage-examples)
- [Integration Guidelines](#integration-guidelines)

---

## WaveManager Events

The `ATDWaveManager` class provides events for wave lifecycle, enemy management, and token system operations.

### Wave Lifecycle Events

#### `OnWaveInitialized(int32 WaveIndex)`
**Triggered:** When a wave is set up and ready to start
**Parameters:**
- `WaveIndex` - The index of the wave being initialized (0-based)

**Use Cases:**
- Pre-load wave-specific assets
- Set up wave-specific UI elements
- Initialize wave-specific VFX systems

#### `OnWaveStarted(int32 WaveIndex)`
**Triggered:** When wave spawning begins
**Parameters:**
- `WaveIndex` - The index of the wave starting

**Use Cases:**
- Play wave start sound effects
- Show wave start UI animations
- Trigger wave-specific particle effects
- Update wave counter display

#### `OnWaveEnded(int32 WaveIndex)`
**Triggered:** When wave completes (all enemies spawned and destroyed)
**Parameters:**
- `WaveIndex` - The index of the wave that ended

**Use Cases:**
- Play wave completion sounds
- Show wave completion UI
- Trigger celebration effects
- Update score displays

#### `OnWavePaused(int32 WaveIndex)`
**Triggered:** When wave spawning is paused
**Parameters:**
- `WaveIndex` - The index of the paused wave

**Use Cases:**
- Show pause indicators
- Mute wave-specific audio
- Display pause UI elements

#### `OnWaveResumed(int32 WaveIndex)`
**Triggered:** When wave spawning resumes from pause
**Parameters:**
- `WaveIndex` - The index of the resumed wave

**Use Cases:**
- Hide pause indicators
- Resume wave-specific audio
- Hide pause UI elements

### Enemy Management Events

#### `OnEnemySpawnedGlobal(int32 TotalAliveEnemies)`
**Triggered:** When any enemy spawns in any lane
**Parameters:**
- `TotalAliveEnemies` - Current total count of alive enemies

**Use Cases:**
- Update enemy counter UI
- Play enemy spawn sound effects
- Trigger global spawn particle effects
- Update difficulty scaling indicators

#### `OnEnemyDestroyedGlobal(int32 TotalAliveEnemies)`
**Triggered:** When any enemy is destroyed
**Parameters:**
- `TotalAliveEnemies` - Current total count of alive enemies

**Use Cases:**
- Update enemy counter UI
- Play enemy death sound effects
- Trigger global death particle effects
- Update kill streak counters

### Token System Events

#### `OnTokensGranted(int32 TokensGranted, int32 RemainingTokens)`
**Triggered:** When spawn tokens are granted to spawners
**Parameters:**
- `TokensGranted` - Number of tokens just granted
- `RemainingTokens` - Total tokens remaining in the pool

**Use Cases:**
- Show token availability UI
- Play token grant sound effects
- Update spawning rate indicators
- Visual feedback for spawning capacity

#### `OnTokensExhausted()`
**Triggered:** When no spawn tokens are available
**Parameters:** None

**Use Cases:**
- Show "spawning paused" indicators
- Play token exhaustion sound
- Display spawning capacity warnings
- Visual feedback for spawning limits

### Intermission Events

#### `OnIntermissionStarted(float Duration)`
**Triggered:** When intermission period begins between waves
**Parameters:**
- `Duration` - Length of intermission in seconds

**Use Cases:**
- Show intermission countdown timer
- Play intermission music
- Display wave preparation UI
- Trigger intermission particle effects

#### `OnIntermissionEnded(int32 NextWaveIndex)`
**Triggered:** When intermission ends and next wave begins
**Parameters:**
- `NextWaveIndex` - The index of the wave starting

**Use Cases:**
- Hide intermission UI
- Transition to wave music
- Show next wave preview
- Trigger wave transition effects

### Spawner Events

#### `OnAllSpawnersFinished(int32 WaveIndex)`
**Triggered:** When all spawners have completed their groups
**Parameters:**
- `WaveIndex` - The index of the wave that finished

**Use Cases:**
- Trigger wave completion sequence
- Show "wave complete" UI
- Play wave completion audio
- Start intermission countdown

---

## EnemySpawner Events

The `ATDEnemySpawner` class provides lane-specific events for spawning control and enemy management.

### Spawning Control Events

#### `OnSpawningStarted(int32 SpawnLaneID)`
**Triggered:** When spawning begins for this lane
**Parameters:**
- `SpawnLaneID` - Unique identifier for this spawn lane

**Use Cases:**
- Play lane-specific spawn sounds
- Show lane activation effects
- Update lane status indicators
- Trigger lane-specific particle systems

#### `OnSpawningStopped(int32 SpawnLaneID)`
**Triggered:** When spawning stops for this lane
**Parameters:**
- `SpawnLaneID` - Unique identifier for this spawn lane

**Use Cases:**
- Stop lane-specific audio
- Hide lane activation effects
- Update lane status indicators
- Trigger lane completion effects

#### `OnSpawningPaused(int32 SpawnLaneID)`
**Triggered:** When spawning pauses for this lane (usually due to token limits)
**Parameters:**
- `SpawnLaneID` - Unique identifier for this spawn lane

**Use Cases:**
- Show lane pause indicators
- Play pause sound effects
- Display lane status warnings
- Visual feedback for spawning limits

#### `OnSpawningResumed(int32 SpawnLaneID)`
**Triggered:** When spawning resumes for this lane
**Parameters:**
- `SpawnLaneID` - Unique identifier for this spawn lane

**Use Cases:**
- Hide lane pause indicators
- Resume lane-specific audio
- Clear lane status warnings
- Show lane reactivation effects

### Enemy Spawning Events

#### `OnEnemySpawned(AActor* SpawnedEnemy, int32 SpawnLaneID)`
**Triggered:** When a specific enemy spawns in this lane
**Parameters:**
- `SpawnedEnemy` - Reference to the spawned enemy actor
- `SpawnLaneID` - Unique identifier for this spawn lane

**Use Cases:**
- Attach enemy-specific VFX to the spawned actor
- Play enemy-specific spawn sounds
- Apply lane-specific effects to the enemy
- Update lane-specific enemy counters

#### `OnGroupStarted(int32 GroupIndex, int32 SpawnLaneID)`
**Triggered:** When a spawn group begins in this lane
**Parameters:**
- `GroupIndex` - Index of the group starting (0-based)
- `SpawnLaneID` - Unique identifier for this spawn lane

**Use Cases:**
- Show group-specific UI indicators
- Play group start sound effects
- Trigger group-specific particle effects
- Update group progress displays

#### `OnGroupFinished(int32 GroupIndex, int32 SpawnLaneID)`
**Triggered:** When a spawn group completes in this lane
**Parameters:**
- `GroupIndex` - Index of the group that finished (0-based)
- `SpawnLaneID` - Unique identifier for this spawn lane

**Use Cases:**
- Show group completion effects
- Play group completion sounds
- Update group progress displays
- Trigger group-specific celebration effects

#### `OnAllGroupsFinished(int32 SpawnLaneID)`
**Triggered:** When all spawn groups complete in this lane
**Parameters:**
- `SpawnLaneID` - Unique identifier for this spawn lane

**Use Cases:**
- Show lane completion effects
- Play lane completion sounds
- Update lane status to "complete"
- Trigger lane-specific celebration effects

### Token Management Events

#### `OnTokenRequested(int32 RequestedTokens, int32 SpawnLaneID)`
**Triggered:** When this lane requests spawn tokens
**Parameters:**
- `RequestedTokens` - Number of tokens requested
- `SpawnLaneID` - Unique identifier for this spawn lane

**Use Cases:**
- Show token request indicators
- Play token request sounds
- Display spawning queue status
- Visual feedback for token requests

#### `OnTokensGranted(int32 GrantedTokens, int32 SpawnLaneID)`
**Triggered:** When tokens are granted to this lane
**Parameters:**
- `GrantedTokens` - Number of tokens granted
- `SpawnLaneID` - Unique identifier for this spawn lane

**Use Cases:**
- Show token grant effects
- Play token grant sounds
- Update lane spawning status
- Visual confirmation of spawning resumption

#### `OnTokensDenied(int32 RequestedTokens, int32 SpawnLaneID)`
**Triggered:** When token request is denied for this lane
**Parameters:**
- `RequestedTokens` - Number of tokens that were requested
- `SpawnLaneID` - Unique identifier for this spawn lane

**Use Cases:**
- Show token denial indicators
- Play token denial sounds
- Display spawning queue status
- Visual feedback for spawning limits

---

## Event Usage Examples

### Basic VFX Integration
```cpp
// In Blueprint Event Graph
Event: OnEnemySpawned
├── Spawn Particle System at Enemy Location
├── Play Enemy Spawn Sound
└── Update Enemy Counter UI

Event: OnWaveStarted
├── Play Wave Start Music
├── Show Wave Number UI
└── Trigger Screen Shake Effect
```

### Lane-Specific Effects
```cpp
// In Blueprint Event Graph
Event: OnSpawningStarted (LaneID: 0)
├── Activate Lane 0 Particle System
├── Play Lane 0 Spawn Sound
└── Show Lane 0 Status Indicator

Event: OnSpawningPaused (LaneID: 0)
├── Show Lane 0 Pause Effect
├── Play Lane 0 Pause Sound
└── Update Lane 0 Status to "Paused"
```

### UI Integration
```cpp
// In Blueprint Event Graph
Event: OnTokensExhausted
├── Show "Spawning Paused" UI
├── Play Warning Sound
└── Update Spawning Status Display

Event: OnWaveEnded
├── Show "Wave Complete" UI
├── Play Victory Sound
└── Start Intermission Countdown
```

---

## Integration Guidelines

### Performance Considerations
- **Avoid heavy operations** in event handlers - use timers for delayed effects
- **Cache references** to frequently accessed actors/components
- **Use object pooling** for particle effects and UI elements
- **Limit audio sources** to prevent audio channel overflow

### Best Practices
- **Use lane-specific effects** for EnemySpawner events to create visual variety
- **Combine multiple events** for complex sequences (e.g., wave start + lane activation)
- **Use event parameters** to customize effects (e.g., different sounds per lane)
- **Test with multiple players** to ensure events work correctly in multiplayer

### Common Patterns
- **Wave Start Sequence**: `OnWaveInitialized` → `OnWaveStarted` → `OnSpawningStarted` (per lane)
- **Enemy Spawn Sequence**: `OnTokenRequested` → `OnTokensGranted` → `OnEnemySpawned`
- **Wave End Sequence**: `OnAllSpawnersFinished` → `OnWaveEnded` → `OnIntermissionStarted`

### Debugging Tips
- **Add debug prints** to event handlers to trace execution flow
- **Use different colors** for different lane effects to identify issues
- **Monitor event frequency** to ensure performance is acceptable
- **Test edge cases** like rapid pause/resume cycles

---

*This documentation covers all Blueprint events available in the WaveManager and EnemySpawner classes. Use these events to create rich, responsive VFX and UI that enhances the tower defense gameplay experience.*
