#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Character {
public:
    Character(string name, string classCharacter, int health): name(name), classCharacter(classCharacter), health(health) {}

    bool operator==(Character obj) {
        return this->name == obj.name;
    }

    static Character readFromFile(ifstream &is) {
        string token, newName, newClass, newHealth;
        getline(is, token);
        stringstream ss(token);
        getline(ss, newName, ',');
        getline(ss, newClass, ',');
        getline(ss, newHealth);

        return Character(newName, newClass, atoi(newHealth.c_str()));
    }

    void writeToFile(ofstream &os) {
        if(!os.is_open()) {
            cout << "Arquivo fechado!" << endl;
            return;
        }

        os << this->name << "," << this->classCharacter << "," << this->health << endl;
        return;
    }
private:
    string name;
    string classCharacter;
    int health;
};

int main() {
    vector<Character> fortniteCharacters;
    ifstream input;
    input.open("entrada.txt");

    while(input.good()){
        Character c = Character::readFromFile(input);
        if(find(fortniteCharacters.begin(), fortniteCharacters.end(), c) == fortniteCharacters.end()){
            fortniteCharacters.push_back(c);
        }
    }
    input.close();


    ofstream output;
    output.open("saida.txt");
    for(auto it=fortniteCharacters.begin(); it != fortniteCharacters.end(); ++it){
        it->writeToFile(output);
    }
    output.close();

    return 0;
}