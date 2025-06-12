# 🚕 Rush Hour

**Rush Hour** is a 2D time-based taxi and delivery driving game built with OpenGL. Players navigate through a dynamic city grid, picking up passengers or delivering packages while managing fuel, time, and traffic.

![Gameplay GIF](media/gameplay.gif)

## 🎮 Game Overview

Choose your role and race against the clock:

- **Taxi Driver**: Pick up passengers and drop them at their destinations.
- **Delivery Driver**: Pick up packages and deliver them to drop-off points.

Earn points and money for each successful job, and use your earnings to refuel. Collisions, obstacles, and traffic reduce your score!

## 🧠 Features

- 🏙️ **Dynamic City Grid**:
  - Randomly placed buildings, roads, and obstacles.
  - Randomized fuel stations and job locations.
- 🎮 **Two Game Modes**: Taxi and Delivery.
- ⛽ **Fuel Management**:
  - Fuel drains over time.
  - Refill at stations using money earned.
- 📈 **Scoring & Leaderboard**:
  - Tracks score and earnings.
  - Stores top 10 high scores in a binary file.
- ⏱️ **Time-Based Gameplay**:
  - 3-minute game timer.
- 🚗 **NPC Traffic & Obstacles**:
  - Increasing difficulty as game progresses.
- 🧱 **Collision Detection**
  - Avoid accidents to maintain your score
- 🏁 **Win/Lose Conditions**
  - Score 100 points in 3 minutes
  - Or avoid losing (fuel out, time up, or negative score)

## 🕹️ Controls

| Key         | Action                                      |
|-------------|---------------------------------------------|
| Arrow Keys  | Move vehicle                                 |
| Spacebar    | Pick up / Drop off (passenger or package)    |
| **P**       | Change role at a mode station                |
| **F**       | Debug key to refill fuel                     |
| **R**       | Reset the game                               |
| **ESC**     | Exit the game                                |

---

## 🧾 Scoring System

### Taxi Mode
| Action                     | Points |
|---------------------------|--------|
| Successful drop-off       | +10    |
| Hit a pedestrian          | -5     |
| Hit an obstacle           | -2     |
| Hit another car           | -3     |

### Delivery Mode
| Action                     | Points |
|---------------------------|--------|
| Successful delivery        | +20    |
| Hit a pedestrian           | -8     |
| Hit an obstacle            | -4     |
| Hit another car            | -5     |

> 💰 Each job earns money, which is used for refueling.

## 🏁 Game End Conditions

- Time runs out (3 minutes).
- Fuel runs out.
- Score drops below 0.
- Score reaches 100 → **You win!** 🎉

## 🛠️ Build Instructions

### Requirements

Ensure the following dependencies are installed on your system:

- **g++** (C++ compiler)
- **make**
- **OpenGL**
- **FreeImage**
- **GLUT**
- **SDL2**

> 💡 On Debian/Ubuntu, you can install them with:
> ```bash
> sudo apt-get install g++ make freeglut3-dev glew-utils libglew-dev libfreeimage-dev libsdl2-mixer-dev libsdl2-dev
> ```

### 🔧 Compiling the Game

Use the provided **Makefile** to build the project:

```bash
make
```
Once the game is built, you can run it with:

```bash
./rush_hour
```