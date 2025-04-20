
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

template <typename CONTAINER, typename FUNC>
string map_join(const CONTAINER& container, FUNC func, string separator = " ") {
    stringstream ss;
    for (auto it = container.begin(); it != container.end(); it++) {
        ss << (it == container.begin() ? "" : separator);
        ss << func(*it);
    }
    return ss.str();
}

pair<string, string> decodeFone(string phone) {
    stringstream ss(phone);
    string identifier, number;
    getline(ss, identifier, ':');
    getline(ss, number);
    return {identifier, number};
}

class Fone {
    string identifier;
    string number;
public:
    Fone(string identifier = "", string number = "") : identifier(identifier), number(number) {}

    string getId() { return identifier; }
    string getNumber() { return number; }

    bool isValid() {
        string validChars = "0123456789().-";
        for (char c : number) {
            if (validChars.find(c) == string::npos) {
                cout << "fail: invalid number" << endl;
                return false;
            }
        }
        return true;
    }

    string toString() { return identifier + ":" + number; }
};

class Contact {
    string name;
    bool favorited;
    vector<Fone> phones;
public:
    Contact(string name = "") : name(name), favorited(false) {}

    string getName() { return name; }
    void setName(string name) { this->name = name; }
    bool isFavorited() { return favorited; }
    void toggleFavorited() { favorited = !favorited; }
    vector<Fone> getPhones() { return phones; }

    void addFone(string identifier, string number) {
        Fone fone(identifier, number);
        if (fone.isValid()) {
            phones.push_back(fone);
        }
    }

    void rmFone(int index) {
        if (index >= 0 && index < (int)phones.size()) {
            phones.erase(phones.begin() + index);
        }
    }

    string toString() {
        stringstream ss;
        ss << (favorited ? "@ " : "- ") << name << " [" 
           << map_join(phones, [](Fone f) { return f.toString(); }, ", ") << "]";
        return ss.str();
    }
};

class Agenda {
    vector<Contact> contacts;

    int findPosByName(string name) {
        for (size_t i = 0; i < contacts.size(); i++) {
            if (contacts[i].getName() == name)
                return i;
        }
        return -1;
    }

public:
    void addContact(string name, vector<Fone> phones) {
        int pos = findPosByName(name);
        if (pos != -1) {
            for (auto& f : phones) {
                contacts[pos].addFone(f.getId(), f.getNumber());
            }
        } else {
            Contact contact(name);
            for (auto& f : phones) {
                contact.addFone(f.getId(), f.getNumber());
            }
            contacts.push_back(contact);
            sort(contacts.begin(), contacts.end(), [](Contact a, Contact b) {
                return a.getName() < b.getName();
            });
        }
    }

    Contact* getContact(string name) {
        int pos = findPosByName(name);
        if (pos != -1) return &contacts[pos];
        return nullptr;
    }

    void rmContact(string name) {
        int pos = findPosByName(name);
        if (pos != -1) {
            contacts.erase(contacts.begin() + pos);
        }
    }

    vector<Contact> search(string pattern) {
        vector<Contact> result;
        for (auto& c : contacts) {
            if (c.toString().find(pattern) != string::npos) {
                result.push_back(c);
            }
        }
        return result;
    }

    vector<Contact> getFavorited() {
        vector<Contact> result;
        for (auto& c : contacts) {
            if (c.isFavorited()) {
                result.push_back(c);
            }
        }
        return result;
    }

    vector<Contact> getContacts() { return contacts; }

    string toString() {
        return map_join(contacts, [](Contact c) { return c.toString(); }, "\n");
    }
};

int main() {
    Agenda agenda;
    string line, command;
    while (true) {
        try {
            getline(cin, line);
            cout << "$" << line << endl;
            stringstream ss(line);
            ss >> command;

            if (command == "end") {
                break;
            } else if (command == "add") {
                string name, token;
                ss >> name;
                vector<Fone> phones;
                while (ss >> token) {
                    auto [identifier, number] = decodeFone(token);
                    phones.push_back(Fone(identifier, number));
                }
                agenda.addContact(name, phones);
            } else if (command == "show") {
                cout << agenda.toString() << endl;
            } else if (command == "rmFone") {
                string name;
                int index;
                ss >> name >> index;
                Contact* contact = agenda.getContact(name);
                if (contact) {
                    contact->rmFone(index);
                }
            } else if (command == "rm") {
                string name;
                ss >> name;
                agenda.rmContact(name);
            } else if (command == "search") {
                string pattern;
                ss >> pattern;
                cout << map_join(agenda.search(pattern), [](Contact c) { return c.toString(); }, "\n") << endl;
            } else if (command == "tfav") {
                string name;
                ss >> name;
                Contact* contact = agenda.getContact(name);
                if (contact) {
                    contact->toggleFavorited();
                }
            } else if (command == "showFav") {
                cout << map_join(agenda.getFavorited(), [](Contact c) { return c.toString(); }, "\n") << endl;
            } else if (command == "favs") {
                vector<Contact> favorites = agenda.getFavorited();
                cout << map_join(favorites, [](Contact c) { return c.toString(); }, "\n") << endl;
            } else {
                cout << "fail: comando invalido" << endl;
            }
        } catch (exception& e) {
            cout << "fail: " << e.what() << endl;
        }
    }
}