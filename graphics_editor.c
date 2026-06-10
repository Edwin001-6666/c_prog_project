#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 30
#define COLS 60
#define MAX_OBJ 20

char canvas[ROWS][COLS];

#define CIRCLE    1
#define RECTANGLE 2
#define LINE      3
#define TRIANGLE  4

struct Shape {
    int type;
    int x1, y1;
    int x2, y2;
    int x3, y3;
};

struct Shape shapes[MAX_OBJ];
int count = 0;

void fillCanvas();
void showCanvas();
void redraw();
void putPoint(int x, int y);
void drawCircle(int cx, int cy, int r);
void drawRect(int x, int y, int w, int h);
void drawLine(int x1, int y1, int x2, int y2);
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
void drawOneShape(int index);
void addShape();
void deleteShape();
void modifyShape();
void showAllShapes();
void printShapeName(int type);
int isOutOfBound(int x, int y);

int main() {
    int choice;

    fillCanvas();

    printf("\n=== Welcome to 2D Graphics Editor ===\n");

    while (1) {
        printf("\n");
        printf("---------- MENU ----------\n");
        printf("1. Add a shape\n");
        printf("2. Delete a shape\n");
        printf("3. Modify a shape\n");
        printf("4. Display canvas\n");
        printf("5. Show all shapes\n");
        printf("6. Clear everything\n");
        printf("0. Exit\n");
        printf("--------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            addShape();
        }
        else if (choice == 2) {
            deleteShape();
        }
        else if (choice == 3) {
            modifyShape();
        }
        else if (choice == 4) {
            showCanvas();
        }
        else if (choice == 5) {
            showAllShapes();
        }
        else if (choice == 6) {
            count = 0;
            fillCanvas();
            printf("Canvas cleared!\n");
        }
        else if (choice == 0) {
            printf("Bye!\n");
            break;
        }
        else {
            printf("Wrong choice, try again.\n");
        }
    }

    return 0;
}

void fillCanvas() {
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            canvas[i][j] = '_';
        }
    }
}

void showCanvas() {
    int i, j;

    printf("\n");

    printf("    ");
    for (j = 0; j < COLS; j++) {
        if (j % 10 == 0)
            printf("%d", j / 10);
        else
            printf(" ");
    }
    printf("\n");

    printf("    ");
    for (j = 0; j < COLS; j++) {
        printf("%d", j % 10);
    }
    printf("\n");

    printf("   +");
    for (j = 0; j < COLS; j++)
        printf("-");
    printf("+\n");

    for (i = 0; i < ROWS; i++) {
        printf("%2d |", i);
        for (j = 0; j < COLS; j++) {
            printf("%c", canvas[i][j]);
        }
        printf("|\n");
    }

    printf("   +");
    for (j = 0; j < COLS; j++)
        printf("-");
    printf("+\n");
}

void redraw() {
    int i;
    fillCanvas();
    for (i = 0; i < count; i++) {
        drawOneShape(i);
    }
}

void putPoint(int x, int y) {
    if (x >= 0 && x < COLS && y >= 0 && y < ROWS) {
        canvas[y][x] = '*';
    }
}

void drawCircle(int cx, int cy, int r) {
    int x, y, d;

    x = 0;
    y = r;
    d = 1 - r;

    while (x <= y) {
        putPoint(cx + x, cy + y);
        putPoint(cx - x, cy + y);
        putPoint(cx + x, cy - y);
        putPoint(cx - x, cy - y);
        putPoint(cx + y, cy + x);
        putPoint(cx - y, cy + x);
        putPoint(cx + y, cy - x);
        putPoint(cx - y, cy - x);

        if (d < 0) {
            d = d + 2 * x + 3;
        } else {
            d = d + 2 * (x - y) + 5;
            y = y - 1;
        }
        x = x + 1;
    }
}

void drawRect(int x, int y, int w, int h) {
    int i;

    for (i = x; i < x + w; i++)
        putPoint(i, y);

    for (i = x; i < x + w; i++)
        putPoint(i, y + h - 1);

    for (i = y; i < y + h; i++)
        putPoint(x, i);

    for (i = y; i < y + h; i++)
        putPoint(x + w - 1, i);
}

void drawLine(int x1, int y1, int x2, int y2) {
    int dx, dy, sx, sy, err, e2;

    dx = x2 - x1;
    if (dx < 0) dx = -dx;

    dy = y2 - y1;
    if (dy < 0) dy = -dy;

    if (x1 < x2)
        sx = 1;
    else
        sx = -1;

    if (y1 < y2)
        sy = 1;
    else
        sy = -1;

    err = dx - dy;

    while (1) {
        putPoint(x1, y1);

        if (x1 == x2 && y1 == y2)
            break;

        e2 = 2 * err;

        if (e2 > -dy) {
            err = err - dy;
            x1 = x1 + sx;
        }
        if (e2 < dx) {
            err = err + dx;
            y1 = y1 + sy;
        }
    }
}

void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    drawLine(x1, y1, x2, y2);
    drawLine(x2, y2, x3, y3);
    drawLine(x3, y3, x1, y1);
}

void drawOneShape(int index) {
    struct Shape s = shapes[index];

    if (s.type == CIRCLE) {
        drawCircle(s.x1, s.y1, s.x2);
    }
    else if (s.type == RECTANGLE) {
        drawRect(s.x1, s.y1, s.x2, s.y2);
    }
    else if (s.type == LINE) {
        drawLine(s.x1, s.y1, s.x2, s.y2);
    }
    else if (s.type == TRIANGLE) {
        drawTriangle(s.x1, s.y1, s.x2, s.y2, s.x3, s.y3);
    }
}

int isOutOfBound(int x, int y) {
    if (x < 0 || x >= COLS || y < 0 || y >= ROWS) {
        return 1;
    }
    return 0;
}

void addShape() {
    int choice;
    struct Shape s;

    if (count >= MAX_OBJ) {
        printf("Sorry, maximum %d shapes allowed.\n", MAX_OBJ);
        return;
    }

    printf("\nWhat shape do you want to add?\n");
    printf("1. Circle\n");
    printf("2. Rectangle\n");
    printf("3. Line\n");
    printf("4. Triangle\n");
    printf("Choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        s.type = CIRCLE;
        printf("Enter center X (0 to %d): ", COLS - 1);
        scanf("%d", &s.x1);
        printf("Enter center Y (0 to %d): ", ROWS - 1);
        scanf("%d", &s.y1);
        printf("Enter radius: ");
        scanf("%d", &s.x2);
        s.y2 = 0;
        s.x3 = 0;
        s.y3 = 0;

        if (isOutOfBound(s.x1, s.y1)) {
            printf("Coordinates out of bound! X must be 0-%d, Y must be 0-%d.\n",
                   COLS - 1, ROWS - 1);
            return;
        }
        if (s.x2 <= 0) {
            printf("Radius must be greater than 0.\n");
            return;
        }
    }
    else if (choice == 2) {
        s.type = RECTANGLE;
        printf("Enter top-left X (0 to %d): ", COLS - 1);
        scanf("%d", &s.x1);
        printf("Enter top-left Y (0 to %d): ", ROWS - 1);
        scanf("%d", &s.y1);
        printf("Enter width: ");
        scanf("%d", &s.x2);
        printf("Enter height: ");
        scanf("%d", &s.y2);
        s.x3 = 0;
        s.y3 = 0;

        if (isOutOfBound(s.x1, s.y1)) {
            printf("Coordinates out of bound! X must be 0-%d, Y must be 0-%d.\n",
                   COLS - 1, ROWS - 1);
            return;
        }
        if (isOutOfBound(s.x1 + s.x2 - 1, s.y1 + s.y2 - 1)) {
            printf("Coordinates out of bound! Rectangle goes outside the canvas.\n");
            return;
        }
        if (s.x2 <= 0 || s.y2 <= 0) {
            printf("Width and height must be greater than 0.\n");
            return;
        }
    }
    else if (choice == 3) {
        s.type = LINE;
        printf("Enter start X (0 to %d): ", COLS - 1);
        scanf("%d", &s.x1);
        printf("Enter start Y (0 to %d): ", ROWS - 1);
        scanf("%d", &s.y1);
        printf("Enter end X (0 to %d): ", COLS - 1);
        scanf("%d", &s.x2);
        printf("Enter end Y (0 to %d): ", ROWS - 1);
        scanf("%d", &s.y2);
        s.x3 = 0;
        s.y3 = 0;

        if (isOutOfBound(s.x1, s.y1)) {
            printf("Coordinates out of bound! Start point is outside the canvas.\n");
            return;
        }
        if (isOutOfBound(s.x2, s.y2)) {
            printf("Coordinates out of bound! End point is outside the canvas.\n");
            return;
        }
    }
    else if (choice == 4) {
        s.type = TRIANGLE;
        printf("Enter point 1 X (0 to %d): ", COLS - 1);
        scanf("%d", &s.x1);
        printf("Enter point 1 Y (0 to %d): ", ROWS - 1);
        scanf("%d", &s.y1);
        printf("Enter point 2 X (0 to %d): ", COLS - 1);
        scanf("%d", &s.x2);
        printf("Enter point 2 Y (0 to %d): ", ROWS - 1);
        scanf("%d", &s.y2);
        printf("Enter point 3 X (0 to %d): ", COLS - 1);
        scanf("%d", &s.x3);
        printf("Enter point 3 Y (0 to %d): ", ROWS - 1);
        scanf("%d", &s.y3);

        if (isOutOfBound(s.x1, s.y1)) {
            printf("Coordinates out of bound! Point 1 is outside the canvas.\n");
            return;
        }
        if (isOutOfBound(s.x2, s.y2)) {
            printf("Coordinates out of bound! Point 2 is outside the canvas.\n");
            return;
        }
        if (isOutOfBound(s.x3, s.y3)) {
            printf("Coordinates out of bound! Point 3 is outside the canvas.\n");
            return;
        }
    }
    else {
        printf("Invalid choice.\n");
        return;
    }

    shapes[count] = s;
    drawOneShape(count);
    count++;

    printf("Shape added! (total shapes: %d)\n", count);
    showCanvas();
}

void deleteShape() {
    int num, i;

    if (count == 0) {
        printf("No shapes to delete.\n");
        return;
    }

    showAllShapes();

    printf("Enter shape number to delete (1 to %d): ", count);
    scanf("%d", &num);

    if (num < 1 || num > count) {
        printf("Invalid number.\n");
        return;
    }

    for (i = num - 1; i < count - 1; i++) {
        shapes[i] = shapes[i + 1];
    }
    count--;

    redraw();

    printf("Shape deleted! Canvas redrawn.\n");
    showCanvas();
}

void modifyShape() {
    int num;
    struct Shape *s;
    struct Shape old;

    if (count == 0) {
        printf("No shapes to modify.\n");
        return;
    }

    showAllShapes();

    printf("Enter shape number to modify (1 to %d): ", count);
    scanf("%d", &num);

    if (num < 1 || num > count) {
        printf("Invalid number.\n");
        return;
    }

    s = &shapes[num - 1];
    old = *s;

    printf("\nModifying shape #%d (", num);
    printShapeName(s->type);
    printf(")\n");
    printf("Enter new values:\n");

    if (s->type == CIRCLE) {
        printf("New center X (0 to %d): ", COLS - 1);
        scanf("%d", &s->x1);
        printf("New center Y (0 to %d): ", ROWS - 1);
        scanf("%d", &s->y1);
        printf("New radius: ");
        scanf("%d", &s->x2);

        if (isOutOfBound(s->x1, s->y1)) {
            printf("Coordinates out of bound! Keeping old values.\n");
            *s = old;
            return;
        }
        if (s->x2 <= 0) {
            printf("Radius must be greater than 0. Keeping old values.\n");
            *s = old;
            return;
        }
    }
    else if (s->type == RECTANGLE) {
        printf("New top-left X (0 to %d): ", COLS - 1);
        scanf("%d", &s->x1);
        printf("New top-left Y (0 to %d): ", ROWS - 1);
        scanf("%d", &s->y1);
        printf("New width: ");
        scanf("%d", &s->x2);
        printf("New height: ");
        scanf("%d", &s->y2);

        if (isOutOfBound(s->x1, s->y1)) {
            printf("Coordinates out of bound! Keeping old values.\n");
            *s = old;
            return;
        }
        if (isOutOfBound(s->x1 + s->x2 - 1, s->y1 + s->y2 - 1)) {
            printf("Coordinates out of bound! Rectangle goes outside canvas. Keeping old values.\n");
            *s = old;
            return;
        }
        if (s->x2 <= 0 || s->y2 <= 0) {
            printf("Width and height must be greater than 0. Keeping old values.\n");
            *s = old;
            return;
        }
    }
    else if (s->type == LINE) {
        printf("New start X (0 to %d): ", COLS - 1);
        scanf("%d", &s->x1);
        printf("New start Y (0 to %d): ", ROWS - 1);
        scanf("%d", &s->y1);
        printf("New end X (0 to %d): ", COLS - 1);
        scanf("%d", &s->x2);
        printf("New end Y (0 to %d): ", ROWS - 1);
        scanf("%d", &s->y2);

        if (isOutOfBound(s->x1, s->y1)) {
            printf("Coordinates out of bound! Start point outside canvas. Keeping old values.\n");
            *s = old;
            return;
        }
        if (isOutOfBound(s->x2, s->y2)) {
            printf("Coordinates out of bound! End point outside canvas. Keeping old values.\n");
            *s = old;
            return;
        }
    }
    else if (s->type == TRIANGLE) {
        printf("New point 1 X (0 to %d): ", COLS - 1);
        scanf("%d", &s->x1);
        printf("New point 1 Y (0 to %d): ", ROWS - 1);
        scanf("%d", &s->y1);
        printf("New point 2 X (0 to %d): ", COLS - 1);
        scanf("%d", &s->x2);
        printf("New point 2 Y (0 to %d): ", ROWS - 1);
        scanf("%d", &s->y2);
        printf("New point 3 X (0 to %d): ", COLS - 1);
        scanf("%d", &s->x3);
        printf("New point 3 Y (0 to %d): ", ROWS - 1);
        scanf("%d", &s->y3);

        if (isOutOfBound(s->x1, s->y1)) {
            printf("Coordinates out of bound! Point 1 outside canvas. Keeping old values.\n");
            *s = old;
            return;
        }
        if (isOutOfBound(s->x2, s->y2)) {
            printf("Coordinates out of bound! Point 2 outside canvas. Keeping old values.\n");
            *s = old;
            return;
        }
        if (isOutOfBound(s->x3, s->y3)) {
            printf("Coordinates out of bound! Point 3 outside canvas. Keeping old values.\n");
            *s = old;
            return;
        }
    }

    redraw();

    printf("Shape modified! Canvas redrawn.\n");
    showCanvas();
}

void printShapeName(int type) {
    if (type == CIRCLE)
        printf("Circle");
    else if (type == RECTANGLE)
        printf("Rectangle");
    else if (type == LINE)
        printf("Line");
    else if (type == TRIANGLE)
        printf("Triangle");
    else
        printf("Unknown");
}

void showAllShapes() {
    int i;

    if (count == 0) {
        printf("\nNo shapes added yet.\n");
        return;
    }

    printf("\n--- List of Shapes ---\n");

    for (i = 0; i < count; i++) {
        struct Shape s = shapes[i];
        printf("  #%d  ", i + 1);
        printShapeName(s.type);

        if (s.type == CIRCLE) {
            printf(" - center=(%d,%d), radius=%d", s.x1, s.y1, s.x2);
        }
        else if (s.type == RECTANGLE) {
            printf(" - top-left=(%d,%d), width=%d, height=%d",
                   s.x1, s.y1, s.x2, s.y2);
        }
        else if (s.type == LINE) {
            printf(" - from (%d,%d) to (%d,%d)",
                   s.x1, s.y1, s.x2, s.y2);
        }
        else if (s.type == TRIANGLE) {
            printf(" - (%d,%d), (%d,%d), (%d,%d)",
                   s.x1, s.y1, s.x2, s.y2, s.x3, s.y3);
        }

        printf("\n");
    }

    printf("----------------------\n");
}
