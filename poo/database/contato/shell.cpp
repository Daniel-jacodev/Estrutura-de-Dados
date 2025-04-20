#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

template <class CONTAINER, class FUNC>
string map_join(const CONTAINER &cont, FUNC func, string sep = " ")
{
    stringstream ss;
    for (auto it = cont.begin(); it != cont.end(); it++)
    {
        ss << (it == cont.begin() ? "" : sep) << func(*it);
    }
    return ss.str();
}
class Fone{
    string id;
    string number;
public:
    Fone(string id = "", string number = ""){
        this->id = id;
        this->number = number;
    }
    string getId() const{
        return id;
    }
    string getNumber() const{
        return number;
    }
    bool isValid(){
        for (char c: number){
            if(!isdigit(c) && c != '.' && c != '(' && c != ')'){
                cout << "fail: invalid number" << endl;
                return false;
            }
        }
        return true;
    }
    string str() const{
        stringstream ss;
        ss  << id << ":" << number ;
        return ss.str();
    }
};

class Contato{
    bool favorited;
    string name;
    vector<Fone> fones;
public:
    Contato(string name =""){
        this->name = name;
        favorited = false;
    }
    string getName() const{
        return name;
    }
    void addFone(Fone fones){
        if(!fones.isValid()){
            return;
        }
        this->fones.push_back(fones);
    }
    void remover(int index){
        fones.erase(fones.begin() + index);
    }
    void isFavorited(){
        favorited = !favorited;
    }
    string str() const{
        stringstream ss;
        ss << (favorited ? "@ " : "- ") << getName() << " ["
        << map_join(fones, [](Fone fone){return fone.str();}, ", ") << "]";
        return ss.str();
    }

};




int main()
{
    Contato contato("jaco");
    while (true)
    {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;
        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end")
        {
            break;
        }
        else if (cmd == "init")
        {
             string name;
            ss >> name;
            contato = Contato(name);
        }
        else if (cmd == "add")
        {
             string id, number;
             ss >> id >> number;
             contato.addFone(Fone(id, number));
        }
        else if (cmd == "rm")
        {
             int index{};
             ss >> index;
                contato.remover(index);
        }
        else if (cmd == "tfav")
        {
            contato.isFavorited();
        }
        else if (cmd == "show")
        {
            cout << contato.str() << endl;
        }
        else
        {
            cout << "fail: comando invalido" << endl;
        }
    }
}
