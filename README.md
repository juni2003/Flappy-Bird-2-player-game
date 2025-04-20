# Flappy Bird for Two Players - SFML (C++)

![Flappy Bird Multiplayer Game](https://img.shields.io/badge/Game-2%20Player%20Flappy%20Bird-blue)  
![Built with SFML](https://img.shields.io/badge/Framework-SFML-orange)  
![Language: C++](https://img.shields.io/badge/Language-C%2B%2B-red)  

## 📌 Overview  
**Flappy Bird for Two Players** is a competitive adaptation of the classic *Flappy Bird* game, built using **SFML (Simple and Fast Multimedia Library)** in **C++**. This project introduces **real-time multiplayer mechanics**, allowing two players to compete simultaneously—one using the **Space key** and the other the **Up Arrow key**. The game features **collision detection, dynamic pipe generation, score tracking, and win/lose conditions**, making it an engaging and interactive experience.

## 🎮 Key Features  

### 1️⃣ Dual-Player Mechanics  
- **Player 1:** Controls a bird using the **Space key** to flap  
- **Player 2:** Uses the **Up Arrow key** to navigate  
- **Independent physics** for both birds (gravity, velocity, collision)  

### 2️⃣ Dynamic Obstacle Generation  
- **Randomized pipe spawns** with varying gaps  
- **Smooth scrolling** for continuous gameplay  

### 3️⃣ Collision & Scoring System  
- **Bounding-box collision detection** between birds and pipes  
- **Score increments** when a bird successfully passes a pipe  
- **Game Over** condition triggered on collision with pipes or ground  

### 4️⃣ UI & Visual Feedback  
- **Real-time score display** for both players  
- **Game Over screen** with winner declaration  
- **"Press R to Restart"** functionality for replayability  

### 5️⃣ SFML-Based Graphics & Animation  
- **Texture rendering** for birds, pipes, and backgrounds  
- **Sprite animation** (bird flapping)  
- **Smooth frame-rate control** (60 FPS)  

## 🛠 Technologies Used  

| Component            | Technology      | Purpose |
|----------------------|----------------|---------|
| **Graphics & Audio** | SFML 2.6.x     | Handles rendering, input, and window management |
| **Programming**      | C++ (OOP)      | Core game logic, collision, and state management |
| **Build System**     | CMake (Optional) | For cross-platform compilation |

## ⚙️ SFML Setup Guide  

### 📥 Downloading SFML  
1. **Official SFML Website**: [https://www.sfml-dev.org/download.php](https://www.sfml-dev.org/download.php)  
2. **Version**: **SFML 2.6.x (GCC/MinGW)** (Compatible with most C++ compilers)  
3. **Choose**:  
   - **32-bit** if using older systems  
   - **64-bit** for modern Windows (recommended)  

### 🔧 Installation Steps  
1. **Extract SFML** to a folder (e.g., `C:\SFML-2.6.0`)  
2. **Link SFML in your project**:  
   - **Include Path**: `C:\SFML-2.6.0\include`  
   - **Library Path**: `C:\SFML-2.6.0\lib`  
   - **DLLs**: Copy `.dll` files from `SFML-2.6.0\bin` to your project folder  

### 🚀 Compiling & Running  
- **Using GCC/MinGW**:  
  ```sh
  g++ main.cpp Game.cpp Bird.cpp Pipe.cpp -o flappy_bird.exe -IC:\SFML-2.6.0\include -LC:\SFML-2.6.0\lib -lsfml-graphics -lsfml-window -lsfml-system


## 📂 Project Structure
```sh
Flappy-Bird-for-2-players/
├── assets/                # Game textures, fonts, and audio
│   ├── bg.png             # Background image
│   ├── bird1_win.png      # Player 1 victory sprite
│   ├── bird2_win.png      # Player 2 victory sprite
│   ├── gamefont.ttf       # UI font
│   └── ...                # Other assets
├── src/
│   ├── Bird.cpp           # Bird physics & rendering
│   ├── Game.cpp           # Main game loop & logic
│   ├── Pipe.cpp           # Pipe generation
│   └── main.cpp           # Entry point
├── CMakeLists.txt         # Build configuration (optional)
└── README.md              # Project documentation
```

## 🎯 Why This Project?

- **OOP Implementation**: Demonstrates clean class architecture (Bird, Pipe, Game)
- **SFML Mastery**: Practical application of graphics rendering, input handling, and collision detection
- **Multiplayer Innovation**: Unique two-player adaptation of classic Flappy Bird mechanics
- **Educational Value**: Ideal for learning game development fundamentals in C++

## 🔍 Related Searches
- "Two Player Flappy Bird SFML Implementation"
- "C++ Multiplayer Game Tutorial"
- "SFML 2D Game Development Guide"
- "Object-Oriented Game Design Patterns"

## 📜 License
MIT Licensed - Open for collaboration and customization

## 🚀 Quick Start

1. Clone repository:
```bash
git clone https://github.com/yourusername/Flappy-Bird-for-2-players.git
```
2.Compile with:

```
g++ src/*.cpp -o flappy_bird -lsfml-graphics -lsfml-window -lsfml-system
Launch game:
```
```bash
./flappy_bird
```
##💖 Support the Project
Give this repo a ⭐ if you find it valuable!

