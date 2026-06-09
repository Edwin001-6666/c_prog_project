# 2D Graphics Editor (C Project)

## About
This is a simple **menu-driven graphics editor** made in C language.
It uses a **2D character array** as a drawing canvas.
- Empty spaces are shown as `_` (underscore)
- Shapes are drawn using `*` (asterisk)

## What It Can Do
- **Draw shapes** - Circle, Rectangle, Line, Triangle
- **Add** new shapes to the canvas (with automatic bounds checking)
- **Delete** any shape (canvas redraws automatically)
- **Modify** any shape (change its size/position, with automatic bounds checking)
- **Display** the canvas with all shapes
- **List** all shapes you have added
- **Clear** the whole canvas

## How Shapes Are Drawn
- **Circle** - Uses the midpoint circle algorithm to draw a circle outline
- **Rectangle** - Draws four sides (top, bottom, left, right)
- **Line** - Uses Bresenham's line algorithm
- **Triangle** - Draws three lines connecting three points

## Canvas Size & Coordinate System
- **30 rows** and **60 columns**
- Coordinates start from `(0,0)` at the top-left corner
- **X** goes right (`0` to `59`), **Y** goes down (`0` to `29`)

## Bounds Checking (Input Validation)
The program automatically validates coordinates when adding or modifying shapes:
- **Circle**: Center `(X, Y)` must be within the canvas boundaries, and the radius must be greater than `0`.
- **Rectangle**: Top-left corner `(X, Y)` and bottom-right corner must be within the canvas boundaries, and both width and height must be greater than `0`.
- **Line**: Both start `(X1, Y1)` and end `(X2, Y2)` coordinates must be within the canvas boundaries.
- **Triangle**: All three points `(X1, Y1)`, `(X2, Y2)`, and `(X3, Y3)` must be within the canvas boundaries.

If coordinates are out of bounds, the editor displays an error message: `"Coordinates out of bound!"` and cancels the operation (or retains the old shape values if modifying).

## How to Compile and Run on Windows

### Option 1: Using GCC on Windows (MinGW/MSYS2)
Compile:
```cmd
gcc -o graphics_editor.exe graphics_editor.c -lm
```
Run:
```cmd
graphics_editor.exe
```

### Option 2: Using Microsoft Visual Studio Compiler (MSVC)
Open Developer Command Prompt, Compile:
```cmd
cl graphics_editor.c
```
Run:
```cmd
graphics_editor.exe
```

### Option 3: Using Turbo C
1. Open Turbo C / Turbo C++ IDE.
2. Open the file `graphics_editor.c`.
3. Press `Alt + F9` to compile.
4. Press `Ctrl + F9` to run.

## Menu Options
```
---------- MENU ----------
1. Add a shape
2. Delete a shape
3. Modify a shape
4. Display canvas
5. Show all shapes
6. Clear everything
0. Exit
--------------------------
```

## Data Structures Used

### Canvas Array
- `char canvas[30][60]` - stores the drawing grid

### Shape Structure
- `struct Shape` stores the type and coordinates:
```c
struct Shape {
    int type;       // 1=circle, 2=rect, 3=line, 4=triangle
    int x1, y1;     // first point, top-left corner, or center
    int x2, y2;     // second point, width/height, or radius
    int x3, y3;     // third point (only used for triangle)
};
```
- `struct Shape shapes[20]` - array storing all active shapes (maximum 20 shapes)

## How Delete and Modify Work
When you delete or modify a shape, the program:
1. Clears the whole canvas (fills with `_`)
2. Redraws all remaining shapes from scratch

This guarantees that the canvas always displays a correct preview.

## Made By
Student Project - C Programming
