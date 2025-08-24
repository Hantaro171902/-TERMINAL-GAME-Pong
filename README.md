# 🏓 Pong (ASCII Edition)

✨ A retro Pong game brought to life in your terminal. Written in C++ with an OOP twist and ANSI-powered visuals.
✅ A clean, object-oriented implementation of the classic Pong game in C++ for the terminal.

---

# 📸 Preview

<img width="960" height="647" alt="image" src="https://github.com/user-attachments/assets/f9835828-93af-49ef-8781-62986e7b4e54" />

---

## 🎮 Features

- **Classic Pong gameplay** — two paddles, one ball, infinite rivalry 🏓  
- **Fully OOP structured:**
  - `PongObject` → base class for shared properties (position, size, movement, rendering)
  - `Paddle` and `Ball` extend `PongObject`, each with their own physics logic
- **Smooth ball–paddle collision** with realistic bounce angles 🎯  
- **Vertical & horizontal paddle movement** (not just up and down)  
- **Clean, colorful rendering** with borders and score display 🌈  
- **Play until 10 points for the win!** 🏆  

---

## 🧩 OOP Structure

The game is built around **object-oriented design**:

- **`PongObject` (Base Class)**  
  Defines the common properties of all in-game objects:
  - Position (`x`, `y`)
  - Size (`width`, `height`)
  - Velocity (`vx`, `vy`)
  - `render()` & `clear()` functions

- **`Paddle` (Child Class)**  
  Inherits from `PongObject` and adds player-controlled movement:
  - Movement in **all directions**: up, down, left, right
  - X/Y boundaries prevent crossing into enemy territory

- **`Ball` (Child Class)**  
  Extends `PongObject` with its own physics engine:
  - Moves continuously with velocity
  - Detects collisions with paddles & walls
  - Bounces off surfaces with direction reversal

This structure keeps the code **modular** and **reusable**, with physics and rendering encapsulated inside each class.

---

## ⚡ Physics & Collision

- **Wall collisions**  
  - The ball bounces off the **top** and **bottom** walls automatically.

- **Paddle collisions**  
  - X-direction reverses on impact  
  - Y-direction changes slightly depending on where the ball hits the paddle (classic Pong mechanic 🎯)

- **Scoring system**  
  - If the ball crosses the **left or right boundary**, the opposite player scores a point.  
  - First to **10 points wins!** 🏆

---

## 🕹️ Controls

| Key       | Action (Player 1) | Action (Player 2) |
|-----------|------------------|------------------|
| **W / ⬆️** | Move Up           | ↑ Arrow          |
| **S / ⬇️** | Move Down         | ↓ Arrow          |
| **A / ⬅️** | Move Left         | ← Arrow          |
| **D / ➡️** | Move Right        | → Arrow          |
| **Q / ESC** | Quit Game         | Quit Game        |

---
## Using CMake

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

## License

This project is open source and available under the MIT License.

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add tests if applicable
5. Submit a pull request

