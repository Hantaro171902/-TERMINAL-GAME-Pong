# Pong Game

A clean, object-oriented implementation of the classic Pong game in C++ for the terminal.

## Features

- **Clean OOP Design**: Well-structured classes with clear separation of concerns
- **Terminal Graphics**: ASCII-based rendering with smooth animations
- **AI Opponent**: Computer-controlled second player with intelligent paddle movement
- **Collision Detection**: Accurate physics-based collision handling
- **Score Tracking**: Real-time score display and game over detection
- **Cross-platform**: Works on Linux/Unix systems with terminal support

## Project Structure

```
pong/
├── src/
│   ├── headers/           # Header files (.hpp)
│   │   ├── Game.hpp       # Main game controller
│   │   ├── World.hpp      # Game world and physics
│   │   ├── Screen.hpp     # Terminal display management
│   │   ├── InputHandler.hpp # Keyboard input handling
│   │   ├── GameObject.hpp # Base class for game entities
│   │   ├── Ball.hpp       # Ball entity
│   │   ├── Paddle.hpp     # Paddle entity
│   │   └── Vector2D.hpp   # 2D vector mathematics
│   ├── main.cpp           # Program entry point
│   ├── Game.cpp           # Game implementation
│   ├── World.cpp          # World physics implementation
│   ├── Screen.cpp         # Terminal display implementation
│   ├── InputHandler.cpp   # Input handling implementation
│   ├── GameObject.cpp     # Base game object implementation
│   ├── Ball.cpp           # Ball behavior implementation
│   └── Paddle.cpp         # Paddle behavior implementation
├── CMakeLists.txt         # CMake build configuration
├── Makefile              # Make build configuration
└── README.md             # This file
```

## Class Design

### Core Classes

1. **Game**: Main controller that orchestrates the entire game
2. **World**: Manages game physics, collisions, and scoring
3. **Screen**: Handles terminal display and rendering
4. **InputHandler**: Processes keyboard input and key bindings
5. **GameObject**: Base class for all game entities
6. **Ball**: Represents the game ball with physics behavior
7. **Paddle**: Represents player paddles with movement and AI
8. **Vector2D**: 2D vector mathematics for positions and velocities

### Design Principles

- **Single Responsibility**: Each class has a single, well-defined purpose
- **Encapsulation**: Internal state is protected, public interfaces are clean
- **Inheritance**: Ball and Paddle inherit from GameObject
- **Composition**: Game contains World, Screen, and InputHandler
- **RAII**: Proper resource management with constructors/destructors

## Building the Game

### Prerequisites

- C++17 compatible compiler (GCC 7+, Clang 5+, or MSVC 2017+)
- CMake 3.10+ (optional, for CMake build)
- Make (optional, for Makefile build)
- Linux/Unix system with terminal support

### Using CMake

```bash
# Create build directory
mkdir build && cd build

# Configure and build
cmake ..
make

# Run the game
./bin/pong
```

### Using Make

```bash
# Build the game
make

# Run the game
make run

# Clean build files
make clean

# Build debug version
make debug

# Build release version
make release
```

### Direct Compilation

```bash
g++ -std=c++17 -Wall -Wextra -O2 -Isrc/headers \
    src/*.cpp -o pong -lpthread
```

## How to Play

### Controls

- **W/S**: Move Player 1 paddle up/down
- **ESC**: Quit the game
- **Space**: Start the game (when prompted)

### Game Rules

1. Control the left paddle (Player 1) using W and S keys
2. The right paddle (Player 2) is controlled by AI
3. Prevent the ball from passing your paddle
4. Score points by getting the ball past your opponent's paddle
5. First player to reach 10 points wins

### Game Features

- **Realistic Physics**: Ball bounces off paddles and walls
- **AI Opponent**: Computer player with intelligent movement
- **Score Display**: Real-time score tracking
- **Game Over Screen**: Winner announcement when game ends

## Technical Details

### Architecture

The game follows a component-based architecture:

```
Game (Main Controller)
├── World (Physics & Logic)
│   ├── Ball
│   ├── Paddle 1 (Player)
│   └── Paddle 2 (AI)
├── Screen (Rendering)
└── InputHandler (Input)
```

### Key Features

- **Frame-based Timing**: Consistent 50ms frame rate
- **Collision Detection**: AABB collision detection for accurate physics
- **Terminal Management**: Proper terminal setup/cleanup
- **Non-blocking Input**: Responsive keyboard handling
- **Memory Management**: RAII with smart pointers

### Performance

- **Efficient Rendering**: Double-buffered terminal output
- **Minimal CPU Usage**: Frame-limited game loop
- **Memory Efficient**: Smart pointer usage prevents memory leaks

## Extending the Game

### Adding New Features

1. **Power-ups**: Extend GameObject class for power-up entities
2. **Multiple Balls**: Modify World class to handle multiple balls
3. **Different AI Levels**: Add difficulty settings to Paddle AI
4. **Sound Effects**: Integrate with audio libraries
5. **Network Multiplayer**: Add networking capabilities

### Code Organization

- **Headers**: All class declarations in `src/headers/`
- **Implementation**: All class implementations in `src/`
- **Build Systems**: Both CMake and Makefile support
- **Documentation**: Comprehensive comments and README

## Troubleshooting

### Common Issues

1. **Terminal Size**: Ensure terminal is at least 80x30 characters
2. **Permissions**: May need sudo for installation
3. **Compiler**: Ensure C++17 support is available
4. **Dependencies**: pthread library should be available by default

### Debug Mode

Build with debug symbols for troubleshooting:

```bash
make debug
# or
cmake -DCMAKE_BUILD_TYPE=Debug ..
```

## License

This project is open source and available under the MIT License.

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add tests if applicable
5. Submit a pull request

## Version History

- **v1.0.0**: Initial release with basic Pong functionality
  - Clean OOP design
  - Terminal-based graphics
  - AI opponent
  - Collision detection
  - Score tracking
