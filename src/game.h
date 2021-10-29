#include <iostream>
#include <vector>

class Game2048 {
private:
    std::vector<std::vector<unsigned>> data;

    void addRandom();
    static void swap (unsigned & a, unsigned & b);
    void up();
    void down();
    void left();
    void right();
    void print();
    bool checkEndGame();

public:
    Game2048();
    void startGame();
};