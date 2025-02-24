#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

std::pair<int, int> screenInfo() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int width = 0, height = 0;

    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        width = csbi.srWindow.Right - csbi.srWindow.Left + 1; // Console width in characters
        height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1; // Console height in characters
    }

    return {width, height};
}

// Get console dimensions
std::pair<int, int> info = screenInfo();
const int WIDTH = info.first;   // Console width
const int HEIGHT = info.second; // Console height
const int MAX_DROPS = 200;      // Number of active falling characters

// int main() {
//     std::cout << "Console width: " << WIDTH << ", height: " << HEIGHT << std::endl;
//     return 0;
// }

struct Drop {
    int x, y;   // Position of the drop
    int speed;  // Speed of falling
    char symbol; // The actual character
};

// Store active falling characters
vector<Drop> drops;

// Move cursor in the console
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Generate a random character
char getRandomChar() {
    string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!@#$%^&*";
    return chars[rand() % chars.length()];
}

// Spawn a new falling character at the top
void spawnDrop() {
    if (drops.size() < MAX_DROPS) {
        drops.push_back({rand() % WIDTH, 0, (rand() % 3) + 1, getRandomChar()});
    }
}

// Update all falling characters
void updateRain() {
    for (size_t i = 0; i < drops.size(); i++) {
        // Erase old character (move to position and print space)
        gotoxy(drops[i].x, drops[i].y);
        cout << " ";

        // Move drop down based on speed
        drops[i].y += drops[i].speed;

        // If it hits the bottom, remove it
        if (drops[i].y >= HEIGHT) {
            drops.erase(drops.begin() + i);
            i--;  // Adjust index after deletion
        } 
        // Print new character at updated position
        gotoxy(drops[i].x, drops[i].y);
        cout << drops[i].symbol;
        
    }
}

int main() {
    srand(time(0)); // Seed for randomness

    // Set console text color to green
    system("CLS");
    system("color 0A");

    std::string color1 = "color 0A";
    std::string color2 = "color 02";
    std::string color3 = "color 0C";
    std::string color4 = "color 07";
    std::string color5 = "color 02";
    std::string color6 = "color 03";


    while (true) {
        spawnDrop();  // Add new drops randomly
        updateRain(); // Move drops down
        Sleep(50);    // Control speed
        if(rand() % 7 > 5) {
            std::string whichColor = "color " + std::to_string(rand() % 7);
            system(whichColor.c_str());
        }
    }

    return 0;
}