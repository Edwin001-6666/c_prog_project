# 2D Graphics Editor (C Project)

## About
This is a simple **menu-driven graphics editor** made in C language.
It uses a **2D character array** as a drawing canvas.
- Empty spaces are shown as `_` (underscore)
- Shapes are drawn using `*` (asterisk)

## What It Can Do
- **Draw shapes** - Circle, Rectangle, Line, Triangle
- **Add** new shapes to the canvas
- **Delete** any shape (canvas redraws automatically)
- **Modify** any shape (change its size/position)
- **Display** the canvas with all shapes
- **List** all shapes you have added
- **Clear** the whole canvas

## How Shapes Are Drawn
- **Circle** - Uses the midpoint circle algorithm to draw a circle outline
- **Rectangle** - Draws four sides (top, bottom, left, right)
- **Line** - Uses Bresenham's line algorithm
- **Triangle** - Draws three lines connecting three points

## Canvas Size
- **30 rows** and **60 columns**
- Coordinates start from (0,0) at top-left corner
- X goes right (0 to 59), Y goes down (0 to 29)

## How to Compile and Run

### Using GCC (Linux/Mac/MinGW)
```
gcc -o graphics_editor graphics_editor.c -lm
./graphics_editor
```

### Using GCC on Windows
```
gcc -o graphics_editor.exe graphics_editor.c -lm
graphics_editor.exe
```

### Using Turbo C
1. Open Turbo C
2. Open the file `graphics_editor.c`
3. Press Alt+F9 to compile
4. Press Ctrl+F9 to run

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

## Example
1. Choose option 1 (Add shape)
2. Choose 2 (Rectangle)
3. Enter: X=5, Y=3, Width=15, Height=8
4. Choose option 1 again (Add shape)
5. Choose 1 (Circle)
6. Enter: Center X=40, Center Y=15, Radius=6
7. Choose option 4 to see both shapes on canvas

## Files
- `graphics_editor.c` - The main C program
- `README.md` - This file

## Data Structures Used
- **2D char array** (`canvas[30][60]`) - stores the picture
- **struct Shape** - stores type and coordinates of each shape
- **Array of structs** (`shapes[20]`) - stores all shapes (max 20)

## How Delete and Modify Work
When you delete or modify a shape, the program:
1. Clears the whole canvas (fills with `_`)
2. Redraws all remaining shapes from scratch

This way the canvas always looks correct even after changes.

## Made By
Student Project - C Programming
