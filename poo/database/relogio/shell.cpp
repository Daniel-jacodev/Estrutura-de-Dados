#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

class Relogio {
int hora;
int minuto;
int segundo;

public:

Relogio(int h = 0, int m = 0, int s = 0) {
setHora(h);
setMinuto(m);
setSegundo(s);
}


void setHora(int h) {
    if (h >= 0 && h <= 23) {
    hora = h;
    } else {
    cout << "fail: hora invalida" << endl;
    }
}

int getHora() const {
    return hora;
}


void setMinuto(int m) {
if (m >= 0 && m <= 59) {
    minuto = m;
} else {
    cout << "fail: minuto invalido" << endl;
}
}

int getMinuto() const {
return minuto;
}


void setSegundo(int s) {
    if (s >= 0 && s <= 59) {
    segundo = s;
    } else {
    cout << "fail: segundo invalido" << endl;
    }
}

int getSegundo() const {
    return segundo;
}


string str() const {
stringstream ss;
ss << setfill('0') << setw(2) << hora << ":";
ss << setfill('0') << setw(2) << minuto << ":";
ss << setfill('0') << setw(2) << segundo;
return ss.str();
}


void nextSecond() {
segundo++;
if (segundo == 60) {
    segundo = 0;
    minuto++;
    if (minuto == 60) {
    minuto = 0;
    hora++;
    if (hora == 24) {
        hora = 0;
    }
    }
}
}
};

int main() {
Relogio time; 

while (true) {
string line, cmd;
getline(cin, line);
cout << "$" << line << endl;

stringstream ss(line);
ss >> cmd;

if (cmd == "end") {
    break;
} else if (cmd == "set") {
int hora, minuto, segundo;
ss >> hora >> minuto >> segundo;
time.setHora(hora);
time.setMinuto(minuto);
time.setSegundo(segundo);
} else if (cmd == "init") {
int hora, minuto, segundo;
ss >> hora >> minuto >> segundo;
time = Relogio(hora, minuto, segundo);
} else if (cmd == "show") {
cout << time.str() << endl;
} else if (cmd == "next") {
time.nextSecond();
} else {
cout << "fail: comando invalido" << endl;
}
}

return 0;
}

