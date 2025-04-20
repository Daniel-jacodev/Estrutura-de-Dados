
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

class Player {
    int id;
    int position;
    bool isFreeStatus;

public:
    Player(int id) : id(id), position(0), isFreeStatus(true) {}

    int getId() {
        return this->id;
    }

    int getPosition() {
        return this->position;
    }

    bool isFree() {
        return this->isFreeStatus;
    }

    void setPosition(int position) {
        this->position = position;
    }

    void setFree(bool isFreeStatus) {
        this->isFreeStatus = isFreeStatus;
    }

    string toString() const {
        stringstream ss;
        ss << "player" << this->id << ": " << this->position << (isFreeStatus ? " (free)" : " (trapped)");
        return ss.str();
    }
};

class Board {
    vector<bool> traps;  
    vector<Player> players; 
    int size;          
    bool isRunning;           
    int currentPlayerIndex;

public:
    
    Board(int numPlayers, int size) : size(size), isRunning(true), currentPlayerIndex(0) {
        traps.resize(size, false);  
        for (int i = 0; i < numPlayers; i++) {
            players.push_back(Player(i + 1)); 
        }
    }

    void addTrap(int position) {
        if (position < 0 || position >= size) {
            cout << "fail: posição inválida\n";
            return;
        }
        traps[position] = true;
    }

    void roll(int value) {
        if (!isRunning) {
            cout << "O jogo já acabou.\n";
            return;
        }

        Player& currentPlayer = players[currentPlayerIndex];
        
        if (!currentPlayer.isFree() && value % 2 == 0) {
            currentPlayer.setFree(true);
            cout << "player" << currentPlayer.getId() << " se libertou\n";
        } else if (!currentPlayer.isFree()) {
            cout << "player" << currentPlayer.getId() << " continua preso\n";
        } else {
            int newPosition = currentPlayer.getPosition() + value;
            
            if (newPosition >= size) {
                cout << "player" << currentPlayer.getId() << " ganhou\n";
                isRunning = false;
                return;
            }
            
            currentPlayer.setPosition(newPosition);
            cout << "player" << currentPlayer.getId() << " andou para " << newPosition << "\n";
            
            if (traps[newPosition]) {
                currentPlayer.setFree(false);
                cout << "player" << currentPlayer.getId() << " caiu em uma armadilha\n";
            }
        }
        
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    }

    void show() {
        for (size_t i = 0; i < players.size(); ++i) {
            cout << "player" << players[i].getId() << ": ";
            for (int j = 0; j < size + 1; ++j) {
                if (j == players[i].getPosition()) {
                    cout << players[i].getId();
                } else {
                    cout << ".";
                }
            }
            cout << "\n";
        }

        cout << "traps__: ";
        for (int j = 0; j < size + 1; ++j) {
            cout << (traps[j] ? 'x' : '.');
        }
        cout << "\n";
    }
};

int main() {
    try {
        Board board(2, 10);
        while (true) {
            string line, command;
            getline(cin, line);
            cout << "$" << line << endl;

            stringstream ss(line);
            ss >> command;

            if (command == "end") {
                break;
            } else if (command == "init") {
                int numPlayers, size;
                ss >> numPlayers >> size;
                board = Board(numPlayers, size);
            } else if (command == "addTrap") {
                int position;
                ss >> position;
                board.addTrap(position);
            } else if (command == "roll") {
                int value;
                ss >> value;
                board.roll(value);
            } else if (command == "show") {
                board.show();
            } else {
                cout << "fail: command not found" << endl;
            }
        }
    } catch (const exception& e) {
        cerr << "Erro inesperado: " << e.what() << endl;
    }

    return 0;
}