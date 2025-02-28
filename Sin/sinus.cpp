#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <cmath>

std::pair<int, int> windowSize() {
    int width = 0;
    int height = 0;

    CONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo;
    if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &lpConsoleScreenBufferInfo)) {
        width = lpConsoleScreenBufferInfo.srWindow.Right - lpConsoleScreenBufferInfo.srWindow.Left + 1;
        height = lpConsoleScreenBufferInfo.srWindow.Bottom - lpConsoleScreenBufferInfo.srWindow.Top + 1;
    }
    return {width, height};
}

std::pair<int, int> info = windowSize();
const int WIDTH = info.first;
const int HEIGHT = info.second;

void gotoxy(int x, int y) {
    COORD cord;
    cord.X = x;
    cord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
}

void drawSystem() {
    for(int i=0; i<WIDTH; i++) {
        gotoxy(i, HEIGHT/2);
        std::cout << "_";
    }
    for(int i=0; i<HEIGHT; i++) {
        gotoxy(WIDTH/2, i);
        std::cout << "|";
    }
}

void update(char ch) {
    int w = WIDTH / 2;
    int h = HEIGHT / 2;
    
    for (int i = 0; i < WIDTH; i++) {  
        double x = (i - w) * (14 * M_PI / WIDTH);  // Scale X to range [-2π, 2π]
        int y = static_cast<int>(4 * std::sin(x) + h);  // Compute sine height

        gotoxy(i, y);
        std::cout << ch;
    }
}


int main() {
    char ch;
    std::cout << "Enter a character: ";
    std::cin >> ch;

    system("CLS");
    drawSystem();

    update(ch);
    gotoxy(WIDTH / 2, HEIGHT);
    return 0;
}