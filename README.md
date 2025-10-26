# SQR_TD - Square Tower Defense

A co-op Square Tower Defense game built with Unreal Engine 5.6 C++.

## Project Setup

### Regenerating Project Files

To regenerate the project files after making changes to the Build.cs or Target files:

1. **Using Unreal Editor:**
   - Open the project in Unreal Editor
   - Go to Tools → Refresh Visual Studio Project Files

2. **Using Command Line:**
   ```bash
   # Navigate to your project directory
   cd G:\Github\SQR_TD
   
   # Generate project files
   "C:\Program Files\Epic Games\UE_5.6\Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.exe" -projectfiles -project="G:\Github\SQR_TD\SQR_TD.uproject" -game -rocket -progress
   ```

3. **Using UnrealBuildTool directly:**
   ```bash
   "C:\Program Files\Epic Games\UE_5.6\Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.exe" -projectfiles -project="G:\Github\SQR_TD\SQR_TD.uproject" -game -rocket -progress
   ```

### Project Structure

- **Core/**: Main game classes (GameMode, GameState, PlayerState, PlayerController, HUD)
- **Managers/**: Wave and enemy management systems
- **Enemies/**: Enemy base classes and AI controllers
- **Towers/**: Tower base classes and projectiles
- **Building/**: Building system components
- **Data/**: Data assets for waves, enemies, and towers
- **UI/**: Base UI widget classes

### Gameplay Tags

The project uses the following gameplay tags:
- **Enemy Types**: Enemy.Basic, Enemy.Fast, Enemy.Armored, Enemy.Flying, Enemy.Boss
- **Effects**: Effect.Slow, Effect.Burn, Effect.Stun
- **Tower Types**: Tower.SingleTarget, Tower.AoE, Tower.Utility

### Building the Project

1. Open the generated Visual Studio solution file (`SQR_TD.sln`)
2. Build the project in Development Editor configuration
3. Launch the project from Unreal Editor

### Notes

- All classes are designed for server-authoritative co-op gameplay
- Classes use UE5.6 C++ standards with proper replication
- Blueprint integration points are marked with BlueprintCallable/BlueprintAssignable
- Performance optimizations include timer-based updates instead of ticking
