# SQR_TD
Square tower defense game

Project-level setup (once)

Enable: Replication, Gameplay Tags, Niagara, UMG, Navigation System.

Create tag sets (Gameplay Tags):

Enemy.Basic, Enemy.Fast, Enemy.Armored, Enemy.Flying, Enemy.Boss

Effect.Slow, Effect.Burn, Effect.Stun

Tower.SingleTarget, Tower.AoE, Tower.Utility

Create Data folders: /Core, /Managers, /Enemies, /Towers, /Data, /UI, /Maps.

Core Blueprints & exact fields
1) BP_GameMode_TD (server authority)

Purpose: Rules, wave lifecycle, validating build/upgrade.

Variables

bMatchActive (bool)

LoseOnLivesZero (bool, default true)

StartingGoldPerPlayer (int)

TeamLives (int)

WaveManagerRef (BP_WaveManager reference)

Events / Functions

StartMatch(), EndMatch(bool bVictory)

Server_StartNextWave() (call WaveManager)

ValidateBuild(FBuildRequest) -> bool

ApplyGoldToPlayer(PlayerState, Amount)

OnEnemyReachedGoal(BP_EnemyBase) → decrement TeamLives; check defeat

Replication: none (use GameState for shared state)

2) BP_GameState_TD (replicates to everyone)

Purpose: Single source of truth for UI-relevant state.

Replicated Variables

CurrentWave (int)

AliveEnemies (int)

MaxConcurrentEnemies (int)

WaveTimeRemaining (float)

IntermissionTimeRemaining (float)

PlayersReadyCount (int), TotalPlayers (int)

TeamLives (int)

Events (Multicast or RepNotify hooks)

OnWaveStarted(int WaveIndex)

OnWaveEnded(int WaveIndex, bool bVictorySoFar)

OnAliveEnemiesChanged(int NewCount)

OnTeamLivesChanged(int NewLives)

3) BP_PlayerState_TD

Replicated Variables

Gold (int)

Score (int)

Kills (int)

Assists (int)

Events

OnGoldChanged(int NewGold) (for UI)

OnScoreChanged(int NewScore)

4) BP_PlayerController_TD

Purpose: Input → server requests, ping, build.

Components: BP_BuildSystemComponent (see below)

RPCs (Client→Server)

Server_RequestBuildTower(FTowerBuildSpec Spec)

Server_RequestUpgradeTower(AActor* Tower)

Server_RequestSellTower(AActor* Tower)

Server_SetPlayerReady(bool bReady)

Client/UI events

Client_ShowError(FText)

Client_PlayPing(FVector Location)

5) BP_TDHUD + UI Widgets

Widgets

WBP_TopBar: CurrentWave, AliveEnemies/MaxConcurrent, TeamLives, Timer

WBP_BuildPanel: tower cards, cost, description, upgrade tree

WBP_WavePreview: next wave enemy icons/tags

WBP_ReadyCheck: button + status list

Bindings: pull from GameState & PlayerState only (no direct manager calls)

Managers
6) BP_WaveManager (Actor in level, or convert later to Subsystem)

Purpose: Orchestrates waves, spawns, pacing, cap.

Variables

Waves (Array of DA_Wave or DataTable rows)

CurrentWaveIndex (int)

AliveEnemies (int) ← keep in sync with GameState

MaxConcurrentEnemies (int) (copy to GameState)

AvailableTokens (int) (derived: MaxConcurrentEnemies - AliveEnemies)

bWaveRunning (bool)

WaveBudgetRemaining (int) (sum of groups’ points or counts)

IntermissionDuration (float)

PlayerCountScalingCurve (CurveFloat) (optional)

SpawnerRefs (Array<BP_EnemySpawner>)

Events / Functions

InitWave(int WaveIndex) → read DA_Wave, compute budget, configure spawners

StartWave() → set bWaveRunning, start timers on spawners

PauseSpawning() / ResumeSpawning() (broadcast to spawners)

TryGrantTokens(int Requested) -> int (token bucket)

OnEnemySpawned() → AliveEnemies++; update GameState/AvailableTokens

OnEnemyGone() (death/despawn/reached goal) → AliveEnemies--

OnGroupFinished(BP_EnemySpawner) → check if all groups done AND AliveEnemies==0 → end wave

EndWave() → update GameState, start intermission countdown

ScaleForPlayers(int Base, int Players) -> int (health, budget, count)

Replication: Manager can be server-only; mirror state via GameState vars.

7) BP_EnemySpawner (one per lane/entry)

Variables

LaneID (name or int)

SpawnPoint (SceneComponent or Transform)

SpawnGroupQueue (queue built from DA_Wave groups assigned to this spawner)

bPausedByCap (bool)

BurstSize (int) (per group)

SpawnInterval (float) (per group)

Events / Functions

ConfigureFromWave(DA_Wave, AssignedGroups)

TickSpawn() via Timer: ask WaveManager.TryGrantTokens(BurstSize) → spawn K enemies

OnPauseRequested() / OnResumeRequested()

NotifyGroupFinished()

Enemies
8) BP_EnemyBase (Actor)

Components: Capsule, Mesh, Movement (AI or Spline follower), Health component (optional)

Variables

MaxHealth (float), CurrentHealth (float)

BountyGold (int)

MoveSpeed (float)

Tags (Gameplay Tags)

LaneID (optional)

Interfaces / Events

IDamageable.ApplyDamage(float Amount, AActor* Source)

OnDeath(AActor* Killer)

OnReachedGoal() (notify GameMode → lives--)

Lifecycle Hooks

On BeginPlay → WaveManager.OnEnemySpawned()

On Death/Destroy/Goal → WaveManager.OnEnemyGone(), pay bounty (GameMode/Currency)

9) BP_EnemyAIController

Variables: Waypoints (Array<Actor>), CurrentIndex

Functions: AdvanceToNextPoint(), immunity handling by tags

Towers & Combat
10) BP_TowerBase (Actor)

Components: Static/Skeletal Mesh, Sphere (Range), Arrow (Muzzle), optional Niagara

Variables

TowerData (DA_Tower reference)

CurrentLevel (int)

TargetingMode (enum: First, Strongest, Closest, Fastest)

FireCooldown (float, derived from data)

bCanFire (bool)

Events / Functions

AcquireTarget() (server decides; run every 0.2–0.5s)

FireAt(AActor* Target) → spawn projectile or hitscan effect (server), then multicast visuals

Upgrade() (validate cost, swap data, refresh stats)

Sell() (refund part cost)

11) BP_ProjectileBase (Actor) or Hitscan Component

Variables: Damage (float), Speed (float), Lifetime (float), Effects (tags)

Events:

On hit: call IDamageable.ApplyDamage, apply tag-based modifiers (e.g., more vs. Enemy.Flying)

On expire: return to pool (if pooling used)

Building & Economy
12) BP_BuildSystemComponent (add to PlayerController)

Variables

PreviewTowerClass (Class)

PreviewActor (Actor ref)

BuildRadius (float) / GridSize (float) if using grid

bIsValidPlacement (bool)

Client Functions

ShowPreview(Type, Location), ValidatePreviewClient()

Server RPCs

Server_RequestBuildTower(FTowerBuildSpec) → calls GameMode ValidateBuild; spawn on success

Validation Rules (server)

Budget (PlayerState.Gold >= Cost)

Overlap (no other towers), Nav corridor not blocked, within build zone(s)

Economy (handled by GameMode or a tiny manager)

On enemy death → DistributeGold(Amount) to team or assist split

On build/upgrade/sell → adjust PlayerState.Gold

Data-Driven Assets (schemas)
DA_Enemy (PrimaryDataAsset)

Name

Mesh / AnimBP / HitFX

Tags (Gameplay Tags)

Stats

BaseHealth, BaseMoveSpeed, BountyGold

DamageToCore (if goal hit)

Resistances (Map<Tag, float> e.g., Effect.Slow -> 0.5)

Scaling

HealthPerWaveCurve (CurveFloat, multiply)

HealthPerPlayerCurve (CurveFloat)

AIProfile (Flying? Uses different path?)

DA_Tower

Name, Icon, Description

CategoryTag (Tower.AoE, etc.)

Costs

BuildCost

UpgradeCosts (Array<int>)

SellRefundPercent (0–1)

Targeting

Range

FireRate (shots/sec) or Cooldown

TargetingModesAllowed (Array<enum>)

Attack

FiringType (Hitscan/Projectile/AoE)

ProjectileClass (if applicable)

BaseDamage

EffectsToApply (Array<Tags> e.g., Effect.Slow)

EffectValues (Map<Tag, float> e.g., Slow=0.35, Stun=1.0s)

SplashRadius (if AoE)

PierceCount (optional)

Levels

PerLevelDamage, PerLevelRange, PerLevelEffects (Arrays)

MeshPerLevel / VFXPerLevel (optional)

Synergies (optional)

Map<Tag, float> (bonus vs Enemy.Armored)

DA_Wave

WaveIndex

IntermissionOverride (optional)

MaxConcurrentOverride (optional)

BudgetPoints (int) or TotalEnemies (int)

Groups (Array of WaveGroup)

GroupID

EnemyType (DA_Enemy)

Count

BurstSize

SpawnInterval (seconds)

StartDelay (seconds)

AssignedSpawnerID (int/name)

Weight (optional if using budget-spend logic)

Modifiers (e.g., “+20% fast enemies”, “flying only”)

BossInfo (optional)

Token-bucket cap (operational checklist)

Initialize: GameState.MaxConcurrentEnemies = N; WaveManager.AvailableTokens = N.

Spawner tick:

Request BurstSize tokens → receives K = min(BurstSize, AvailableTokens).

Spawn K enemies; after each spawn: WaveManager.OnEnemySpawned() → AliveEnemies++; AvailableTokens--; update GameState.

If 0 tokens, pause this spawner until OnEnemyGone() fires.

Enemy death/despawn/goal:

Call WaveManager.OnEnemyGone() → AliveEnemies--; AvailableTokens++; update GameState; signal spawners to resume if paused.

Wave end condition:

All groups finished AND AliveEnemies == 0.

UI bindings (minimal)

WBP_TopBar ← bind to GameState.CurrentWave, AliveEnemies, MaxConcurrentEnemies, TeamLives, WaveTimeRemaining.

WBP_WavePreview ← query DA_Wave.Groups, display enemy icons + tags.

WBP_BuildPanel ← iterate DA_Tower assets; disabled state if PlayerState.Gold < Cost.

Co-op scaling knobs (add now for later)

HealthMultiplierPerExtraPlayer (float, default 0.6) → applied via DA_Enemy.HealthPerPlayerCurve or a simple formula.

BudgetMultiplierPerExtraPlayer (float, default 0.5) → applied to DA_Wave.BudgetPoints.

GoldSplitMode (enum: Even / LastHit / WeightedByDamage). Start with Even.

Validation rules (server)

Build: within allowed volume, on grid if enabled, no overlap with reserved path, Gold >= Cost.

Upgrade: Tower.Owner == RequestingPlayer (if ownership matters), Gold >= UpgradeCost, within upgrade limits.

Sell: optional cooldown; refund Cost * SellRefundPercent.

Performance guardrails

Set Net Cull Distance on enemies; reduce frequency for far actors.

Use Timers for behavior loops (no per-tick scans).

Pool Projectile actors & common impact FX.

Limit sphere overlaps for targeting (0.2–0.5s cadence).

Prefer hitscan for fast-rate towers.

First playable “Vertical Slice” (order of work)

Core state: GameMode, GameState, PlayerState; hook TopBar UI.

WaveManager + one EnemySpawner; DA_Wave with a single group; cap = 20; token bucket live.

EnemyBase w/ spline or simple waypoint path; death and goal events hooked to WaveManager & GameMode.

Economy: kill bounty → PlayerState.Gold; simple even split.

TowerBase hitscan; build system with server validation; one upgrade level.

Intermission & Ready-up: 10–20s delay; Server_SetPlayerReady gated start.

Add second enemy (fast/low HP) & second tower (slow debuff) to test tags/effects.

Loss condition: TeamLives reaches 0.

QA / Testing checklist

Host + 1 client in PIE with artificial latency (e.g., 80–120ms).

Verify: building denied/approved correctly; gold sync; AliveEnemies never exceeds cap.

Pull token stress test: 3 spawners bursting simultaneously.

Intermission timer doesn’t drift between clients (show GameState value).

Join-in-progress (optional): new client sees correct counts & UI.

Optional niceties (when time allows)

Ping/Marker: PC RPC → multicast world widget for 3s.

Tower targeting priorities UI.

Wave mutators (e.g., “Armored Week”).

Save meta-progress in GameInstanceSubsystem (unlocks).

Analytics: log wave fail wave#, enemy type causing most leaks, average player gold spend.