#include <iostream>
#include <vector>
#include <sstream>
#include <utility>
#include <iomanip>
#include <memory>
using namespace std;

template <typename CONTAINER, typename FN>
string map_join(const CONTAINER& container, FN fn, string sep = ", ", string prefix = "[", string suffix = "]") {
    stringstream ss;
    for (auto it = container.begin(); it != container.end(); ++it) {
        ss << (it != container.begin() ? sep : "") << fn(*it);
    }
    return prefix + ss.str() + suffix;
}

// Enum para os rótulos das moedas
enum class Label { C10, C25, C50, C100 };

// Funções para converter entre Label e string
string labelToString(Label label) {
    switch (label) {
        case Label::C10: return "C10";
        case Label::C25: return "C25";
        case Label::C50: return "C50";
        case Label::C100: return "C100";
        default: return "???";
    }
}

Label stringToLabel(const string& str) {
    if (str == "C10") return Label::C10;
    if (str == "C25") return Label::C25;
    if (str == "C50") return Label::C50;
    if (str == "C100") return Label::C100;
    throw runtime_error("Label inválido");
}

// Classe Coin
class Coin {
public:
    double value;
    int volume;
    Label label;

    Coin(double v, int vol, Label l) : value(v), volume(vol), label(l) {}

    string toString() const {
        stringstream ss;
        ss  << fixed << setprecision(2) << value << ":" << volume;
        return ss.str();
     //   return to_string(value) + ", " + to_string(volume);
    }

    double getValue() const { return value; }
    int getVolume() const { return volume; }
    string getLabel() const { return labelToString(label); }

    // Moedas predefinidas
    static const Coin C10;
    static const Coin C25;
    static const Coin C50;
    static const Coin C100;
};

// Inicialização das moedas
const Coin Coin::C10(0.10, 1, Label::C10);
const Coin Coin::C25(0.25, 2, Label::C25);
const Coin Coin::C50(0.50, 3, Label::C50);
const Coin Coin::C100(1.0, 4, Label::C100);


class Item{
    string label;
    int volume;
public:
    Item(string label, int vol) : label(label), volume(vol) {}
    
    string getLabel() const {
        return label;
    }
    int getVolume() const {
        return volume;
    }
    void setLabel(string newLabel) {
        label = newLabel;
    }
    void setVolume(int vol) {
        volume = vol;
    }
    string str() const {
        stringstream ss;
        ss << label << ":" << volume;
        return ss.str();
    }
};
//ŧeste teste teste

class Porquinho{
    bool broken;
    int volumeMax;
    vector<Coin> coins;
    vector<Item> items;
public:
    Porquinho(int volumeMax) : broken(false), volumeMax(volumeMax) {}

    void addCoin(const Coin& coin) {
        if(broken){
            cout << "fail: the pig is broken" << endl;
            return;
        }
        if(getTotalVolume() + coin.getVolume() > volumeMax){
            cout << "fail: the pig is full" << endl;
            return;
        }
        coins.push_back(coin);
        return;
    }
    void addItem(Item item) {
        if(broken){
            cout << "fail: the pig is broken" << endl;
            return;
        }
        if(getTotalVolume() + item.getVolume() > volumeMax){
            cout << "fail: the pig is full" << endl;
            return;
        }
        items.push_back(item);
        return;
    }

    vector <Coin> extract(){
        if(!broken){
            cout << "fail: you must break the pig first" << endl;
            cout << "[]" << endl;
            return{};
        }
        vector<Coin> tirado = coins;
        coins.clear();
        cout << map_join(tirado, [](const Coin& coin) { return coin.toString();}) << endl;
        return tirado;
    }
    vector <Item> extractItem(){
        if(!broken){
            cout << "fail: you must break the pig first" << endl;
            cout << "[]" << endl;
            return{};
        }
        vector<Item> retirado = items;
        items.clear();
        cout << map_join(retirado, [](const Item& item){
            return item.str();
        }) << endl;
        return {};
    }
    bool quebrar(){
        broken = !broken;
        //item.setVolume()
        return true;
    }


    int getTotalVolume() const {
        if(broken){
            return 0;
        }
        int totalVolume = 0;
        for (const auto& item : items) {
            totalVolume += item.getVolume();
        }
        for (const auto& coin : coins) {
            totalVolume += coin.getVolume();
        }
        return totalVolume;
    }
    double getTotalValue() const {
        double totalValue = 0;
        for (const auto& coin : coins) {
            totalValue += coin.getValue();
        }
        return totalValue;
    }




    string str() const{
        stringstream ss;
        ss << "state=" << (broken ? "broken " : "intact ") << ": " << "coins=" << map_join(coins, [](const Coin& coin) { return coin.toString(); }) << " : " << "items=" << map_join(items, [](const Item& item) { return item.str(); })
         << " :" << " value=" << fixed << setprecision(2) <<getTotalValue() << " : " << "volume=" << getTotalVolume() << "/" << volumeMax;
        return ss.str();
    }
};

int main() {
    Porquinho porquinho(10);
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;
        } else if (cmd == "init") {
             int volumeMax;
             ss >> volumeMax;
             porquinho = Porquinho(volumeMax);
            
        } else if (cmd == "show") {
            cout << porquinho.str() << endl;
        } else if (cmd == "break") {
            porquinho.quebrar();
        } else if (cmd == "addCoin") {
             string label;
             ss >> label;
                if(label == "10"){
                    porquinho.addCoin(Coin::C10);
                }else if(label == "25"){
                    porquinho.addCoin(Coin::C25);
                }else if(label == "50"){
                    porquinho.addCoin(Coin::C50);
                }else if(label == "100"){
                    porquinho.addCoin(Coin::C100);
                }else{
                    cout << "fail: invalid label" << endl;
                }
        } else if (cmd == "addItem") {
             string label;
             int volume;
             ss >> label >> volume;
             porquinho.addItem(Item(label, volume));
            
        } else if (cmd == "extractItems") {
            porquinho.extractItem();
        } else if (cmd == "extractCoins") {
            porquinho.extract();
        } else {
            cout << "fail: invalid command\n";
        }
    }
}
