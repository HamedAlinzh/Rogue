#include "rogue.h"

void shuffleDirections(int directions[4][2]) {
    for (int i = 0; i < 4; i++) {
        int j = rand() % 4;
        int tempY = directions[i][0];
        int tempX = directions[i][1];
        directions[i][0] = directions[j][0];
        directions[i][1] = directions[j][1];
        directions[j][0] = tempY;
        directions[j][1] = tempX;
    }
}

int checkpos(int y, int x){
    char temp = mvinch(y, x);
    if (temp == '.' || temp == '|' || temp == '-'){
        return 0;
    }
    else 
        return 1;
}

void pathFind(Position *start, Position *end) {
    int cameFrom[MAX_HEIGHT][MAX_WIDTH];
    int visited[MAX_HEIGHT][MAX_WIDTH] = {0};
    int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} }; // N, S, W, E

    // Initialize BFS queue
    QueueNode queue[MAX_HEIGHT * MAX_WIDTH];
    int front = 0, back = 0;

    // Initialize `cameFrom` and mark all positions as unvisited
    for (int i = 0; i < MAX_HEIGHT; i++) {
        for (int j = 0; j < MAX_WIDTH; j++) {
            cameFrom[i][j] = -1;
            visited[i][j] = 0;
        }
    }

    // Add the start position to the queue
    queue[back++] = (QueueNode){start->y, start->x};
    visited[start->y][start->x] = 1;  // Mark as visited
    cameFrom[start->y][start->x] = -9;  // Mark start position

    // BFS loop
    while (front < back) {
        QueueNode current = queue[front++];
        int y = current.y;
        int x = current.x;

        if (y == end->y && x == end->x) {
            break;  // Stop when the end is reached
        }

        // Shuffle directions for random exploration
        shuffleDirections(directions);

        // Explore neighbors
        // Explore neighbors
        for (int i = 0; i < 4; i++) {
            int ny = y + directions[i][0];
            int nx = x + directions[i][1];

            // Check bounds, unvisited status, and path validity
            if (ny >= 0 && ny < MAX_HEIGHT && nx >= 0 && nx < MAX_WIDTH &&
                !visited[ny][nx] && checkpos(ny, nx)) {
                
                queue[back++] = (QueueNode){ny, nx};
                visited[ny][nx] = 1;
                cameFrom[ny][nx] = y * MAX_WIDTH + x;
            }
        }
    }

    // Trace back the path from `end` to `start`
    int y = end->y;
    int x = end->x;

    while (cameFrom[y][x] != -9) {
        int parent = cameFrom[y][x];
        y = parent / MAX_WIDTH;
        x = parent % MAX_WIDTH;

        // Avoid overlapping the start and end points
        if ((y != start->y || x != start->x) && (y != end->y || x != end->x)) {
            mvprintw(y, x, "#");
        }
    }

    refresh();
    
}