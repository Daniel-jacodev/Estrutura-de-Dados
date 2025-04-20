#include "fn.hpp"
using namespace std;
struct Car {
    int pass = 0, passMax = 2, gas = 0, gasMax = 100, km = 0;

    Car() {}

    void enter() {
        pass += 1;
        if (pass > passMax) {
            pass = passMax;
            cout << "fail: limite de pessoas atingido" << endl;
        }
    }

    void leave() {
        if (pass > 0) {
            pass -= 1;
        } else {
            cout << "fail: nao ha ninguem no carro" << endl;
        }
    }

    void fuel(int q) {
        if ((gas + q) <= gasMax) {
            gas += q;
        } else {
            gas = gasMax;
;
        }
    }

    void drive(int q) {
        if (gas == 0) {
            cout << "fail: tanque vazio\n";
            return;
        }
        if (pass == 0) {
            cout << "fail: nao ha ninguem no carro\n";
            return;
        }
        if ((gas - q) >= 0) {
            gas -= q;
            km += q;
        } else {
            km += gas;
            cout << "fail: tanque vazio apos andar " << gas << " km\n";
            gas = 0;
        }
    }

    std::string str() const {
        return "pass: " + to_string(pass) + ", gas: " + std::to_string(gas) + ", km: " + std::to_string(km);
    }
};

struct Student {
    Car car;
    Student() {}

    void enter() {
        car.enter();
    }
    void leave() {
        car.leave();
    }
    void fuel(int q) {
        car.fuel(q);
        (void) q;
    }
    void drive(int q) {
        car.drive(q);
        (void) q;
    }
    void show() {
        std::cout << car.str() << std::endl;
    }
};
struct Debug {
    // Se a variável debug for true, os testes não serão executados
    // Apenas o conteúdo do método run() será executado
    // Você pode usar isso para testar seu código manualmente
    static const bool debug = false;
    static void run() {
        std::cout << "Debug ativado" << std::endl;
    }
};
