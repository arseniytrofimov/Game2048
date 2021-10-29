#include "game.h"

Game2048::Game2048(): data(4) {
    for (unsigned i = 0; i < 4; ++i) {
        data[i] = std::vector<unsigned>(4, 0);
    }
}

void Game2048::swap(unsigned &a, unsigned &b) {
    if (a == 0 && b == 0) {
        return;
    }
    unsigned c = a;
    a = b;
    b = c;
}

bool Game2048::checkEndGame() {
    std::vector<std::vector<unsigned>> copy = data;
    up();
    if (data != copy) {
        data = copy;
        return false;
    }
    down();
    if (data != copy) {
        data = copy;
        return false;
    }
    left();
    if (data != copy) {
        data = copy;
        return false;
    }
    right();
    if (data != copy) {
        data = copy;
        return false;
    }
    return true;
}

void Game2048::addRandom() {
    std::vector<bool> rowHasEmptyCells(4, false);
    for (unsigned i = 0; i < 4; ++i) {
        for (unsigned j = 0; j < 4; ++j) {
            if (data[i][j] == 0) {
                rowHasEmptyCells[i] = true;
                break;
            }
        }
    }
    unsigned k = 0;
    for (unsigned i = 0; i < 4; ++i) {
        if (rowHasEmptyCells[i]) {
            k++;
        }
    }
    unsigned r;
    while (!(rowHasEmptyCells[r = rand() % 4]));
    unsigned c;
    while (data[r][c = rand() % 4] != 0);
    k = rand() % 100;
    if (k <= 74) {
        data[r][c] = 2;
    } else {
        data[r][c] = 4;
    }
}


void Game2048::up() {
    std::vector<std::vector<unsigned>> copy = data;
    for (unsigned i = 0; i < 4; ++i) {
        if ((data[0][i] != 0) && (data[1][i] == data[0][i])) {
            data[0][i] = data[0][i] << 1;
            data[1][i] = 0;
            if ((data[2][i] != 0) && (data[2][i] == data[3][i])) {
                data[2][i] = data[2][i] << 1;
                data[3][i] = 0;
            }
        } else {
            if ((data[1][i] != 0) && (data[1][i] == data[2][i])) {
                data[1][i] = data[1][i] << 1;
                data[2][i] = 0;
            } else {
                if ((data[1][i] == 0) && (data[0][i] != 0) && (data[0][i] == data[2][i])) {
                    data[0][i] = data[0][i] << 1;
                    data[2][i] = 0;
                } else {
                    if ((data[1][i] == 0) && (data[2][i] == 0) &&
                        (data[0][i] != 0) && (data[0][i] == data[3][i])) {
                        data[0][i] = data[0][i] << 1;
                        data[3][i] = 0;
                    } else {
                        if ((data[2][i] != 0) && (data[2][i] == data[3][i])) {
                            data[2][i] = data[2][i] << 1;
                            data[3][i] = 0;
                        } else {
                            if ((data[1][i] != 0) && (data[2][i] == 0) &&
                                (data[1][i] == data[3][i])) {
                                data[1][i] = data[1][i] << 1;
                                data[3][i] = 0;
                            }
                        }
                    }
                }
            }
        }
        if (data[2][i] == 0) {
            swap(data[2][i], data[3][i]);
        }
        if (data[1][i] == 0) {
            swap(data[1][i], data[2][i]);
            swap(data[2][i], data[3][i]);
        }
        if (data[0][i] == 0) {
            swap(data[0][i], data[1][i]);
            swap(data[1][i], data[2][i]);
            swap(data[2][i], data[3][i]);
        }
    }
    if (copy != data) {
        addRandom();
    }
}

void Game2048::down() {
    std::vector<std::vector<unsigned>> copy = data;
    for (unsigned i = 0; i < 4; ++i) {
        if ((data[3][i] != 0) && (data[2][i] == data[3][i])) {
            data[3][i] = data[3][i] << 1;
            data[2][i] = 0;
            if ((data[1][i] != 0) && (data[1][i] == data[0][i])) {
                data[1][i] = data[1][i] << 1;
                data[0][i] = 0;
            }
        } else {
            if ((data[2][i] != 0) && (data[2][i] == data[1][i])) {
                data[2][i] = data[2][i] << 1;
                data[1][i] = 0;
            } else {
                if ((data[2][i] == 0) && (data[3][i] != 0) && (data[3][i] == data[1][i])) {
                    data[3][i] = data[3][i] << 1;
                    data[1][i] = 0;
                } else {
                    if ((data[2][i] == 0) && (data[1][i] == 0) &&
                        (data[3][i] != 0) && (data[3][i] == data[0][i])) {
                        data[3][i] = data[3][i] << 1;
                        data[0][i] = 0;
                    } else {
                        if ((data[1][i] != 0) && (data[1][i] == data[0][i])) {
                            data[1][i] = data[1][i] << 1;
                            data[0][i] = 0;
                        } else {
                            if ((data[2][i] != 0) && (data[1][i] == 0) &&
                                (data[2][i] == data[0][i])) {
                                data[2][i] = data[2][i] << 1;
                                data[0][i] = 0;
                            }
                        }
                    }
                }
            }
        }
        if (data[1][i] == 0) {
            swap(data[1][i], data[0][i]);
        }
        if (data[2][i] == 0) {
            swap(data[2][i], data[1][i]);
            swap(data[1][i], data[0][i]);
        }
        if (data[3][i] == 0) {
            swap(data[3][i], data[2][i]);
            swap(data[2][i], data[1][i]);
            swap(data[1][i], data[0][i]);
        }
    }
    if (copy != data) {
        addRandom();
    }
}

void Game2048::left() {
    std::vector<std::vector<unsigned>> copy = data;
    for (unsigned i = 0; i < 4; ++i) {
        if ((data[i][0] != 0) && (data[i][0] == data[i][1])) {
            data[i][0] = data[i][0] << 1;
            data[i][1] = 0;
            if ((data[i][2] != 0) && (data[i][2] == data[i][3])) {
                data[i][2] = data[i][2] << 1;
                data[i][3] = 0;
            }
        } else {
            if ((data[i][1] != 0) && (data[i][1] == data[i][2])) {
                data[i][1] = data[i][1] << 1;
                data[i][2] = 0;
            } else {
                if ((data[i][1] == 0) && (data[i][0] != 0) && (data[i][0] == data[i][2])) {
                    data[i][0] = data[i][0] << 1;
                    data[i][2] = 0;
                } else {
                    if ((data[i][1] == 0) && (data[i][2] == 0) &&
                        (data[i][0] != 0) && (data[i][0] == data[i][3])) {
                        data[i][0] = data[i][0] << 1;
                        data[i][3] = 0;
                    } else {
                        if ((data[i][2] != 0) && (data[i][2] == data[i][3])) {
                            data[i][2] = data[i][2] << 1;
                            data[i][3] = 0;
                        } else {
                            if ((data[i][1] != 0) && (data[i][2] == 0) &&
                                (data[i][1] == data[i][3])) {
                                data[i][1] = data[i][1] << 1;
                                data[i][3] = 0;
                            }
                        }
                    }
                }
            }
        }
        if (data[i][2] == 0) {
            swap(data[i][2], data[i][3]);
        }
        if (data[i][1] == 0) {
            swap(data[i][1], data[i][2]);
            swap(data[i][2], data[i][3]);
        }
        if (data[i][0] == 0) {
            swap(data[i][0], data[i][1]);
            swap(data[i][1], data[i][2]);
            swap(data[i][2], data[i][3]);
        }
    }
    if (copy != data) {
        addRandom();
    }
}

void Game2048::right() {
    std::vector<std::vector<unsigned>> copy = data;
    for (unsigned i = 0; i < 4; ++i) {
        if ((data[i][3] != 0) && (data[i][3] == data[i][2])) {
            data[i][3] = data[i][3] << 1;
            data[i][2] = 0;
            if ((data[i][1] != 0) && (data[i][1] == data[i][0])) {
                data[i][1] = data[i][1] << 1;
                data[i][0] = 0;
            }
        } else {
            if ((data[i][2] != 0) && (data[i][2] == data[i][1])) {
                data[i][2] = data[i][2] << 1;
                data[i][1] = 0;
            } else {
                if ((data[i][2] == 0) && (data[i][3] != 0) && (data[i][3] == data[i][1])) {
                    data[i][3] = data[i][3] << 1;
                    data[i][1] = 0;
                } else {
                    if ((data[i][2] == 0) && (data[i][1] == 0) &&
                        (data[i][3] != 0) && (data[i][3] == data[i][0])) {
                        data[i][3] = data[i][3] << 1;
                        data[i][0] = 0;
                    } else {
                        if ((data[i][1] != 0) && (data[i][1] == data[i][0])) {
                            data[i][1] = data[i][1] << 1;
                            data[i][0] = 0;
                        } else {
                            if ((data[i][2] != 0) && (data[i][1] == 0) &&
                                (data[i][2] == data[i][0])) {
                                data[i][2] = data[i][2] << 1;
                                data[i][0] = 0;
                            }
                        }
                    }
                }
            }
        }
        if (data[i][1] == 0) {
            swap(data[i][1], data[i][0]);
        }
        if (data[i][2] == 0) {
            swap(data[i][2], data[i][1]);
            swap(data[i][1], data[i][0]);
        }
        if (data[i][3] == 0) {
            swap(data[i][3], data[i][2]);
            swap(data[i][2], data[i][1]);
            swap(data[i][1], data[i][0]);
        }
    }
    if (copy != data) {
        addRandom();
    }
}

void Game2048::print() {
    for (unsigned i = 0; i < 4; ++i) {
        for (unsigned j = 0; j < 4; ++j) {
            std::cout << data[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

void Game2048::startGame() {
    addRandom();
    print();
    bool endGame = false;
    while (!endGame) {
        char c;
        std::cin >> c;
        switch (c) {
            case 'd':
                right();
                print();
                endGame = checkEndGame();
                break;
            case 'a':
                left();
                print();
                endGame = checkEndGame();
                break;
            case 'w':
                up();
                print();
                endGame = checkEndGame();
                break;
            case 's':
                down();
                print();
                endGame = checkEndGame();
                break;
            case 'q':
                return;
        }
    }
    std::cout << "Game is ended!" << std::endl;
}
