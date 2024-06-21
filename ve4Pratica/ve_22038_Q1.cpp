#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class LightSaber {
public:
    LightSaber(int size, string color, bool owner=true):size(size), color(color) {
        this->owner = owner ? "jedi" : "sith";
        if(this->owner == "jedi") {
            this->energy = 105;
        } else {
            this->energy = 100;
        }
    }

    void setEnergy(int newEnergy) {
        if(this->owner == "jedi" && newEnergy > 105){
            this->energy = 105;
        } else if(this->owner == "sith" && newEnergy > 100){
            this->energy = 100;
        } else {
            this->energy = newEnergy;
        }
        return;
    }

    operator int() const {
        return energy;
    }

    operator string() const {
        return color;
    }

    LightSaber operator+(LightSaber &obj) {
        int newSize = this->size + obj.size;
        int newEnergy = this->energy + obj.energy;
        bool newOwner = (this->owner == obj.owner && this->owner == "jedi") ? true : false;
        string searchString = this->color + "," + obj.color;
        stringstream ss(searchString);
        char delimiter = ',';

        string token, newColor = "";
        while(getline(ss, token, delimiter)){
            if(newColor.find(token) == std::string::npos) {
                newColor += (token + ",");
            }
        }

        LightSaber newLight = LightSaber(newSize, newColor, newOwner);
        newLight.setEnergy(newEnergy);
        return newLight;
    }

    LightSaber operator*(LightSaber &obj) {
        if(this->size*this->energy > obj.size*obj.energy) {
            int newSize = this->owner == "jedi" ? this->size*0.95 : this->size*0.9;
            bool owner = this->owner == "jedi" ? "jedi" : "sith";
            LightSaber winner = LightSaber(newSize, this->color, owner);
            winner.setEnergy(this->energy-10);
            return winner;
        } else if(this->size*this->energy < obj.size*obj.energy){
            int newSize = obj.owner == "jedi" ? obj.size*0.95 : obj.size*0.9;
            bool owner = obj.owner == "jedi "? "jedi" : "sith";
            LightSaber winner = LightSaber(newSize, obj.color, owner);
            winner.setEnergy(this->energy-10);
            return winner;
        } else {
            int newSize = this->owner == "jedi" ? this->size*0.95 : this->size*0.9;
            bool owner = this->owner == "jedi" ? "jedi" : "sith";
            LightSaber winner = LightSaber(newSize, this->color, owner);
            winner.setEnergy(this->energy-10);
            return winner;
        }
    }

    friend istream& operator >>(istream &is, LightSaber &obj);
    friend ostream& operator <<(ostream &os, LightSaber &obj);

    ~LightSaber() {}
private:
    int size;
    string color;
    int energy;
    string owner;
};

istream& operator>>(istream &is, LightSaber &obj) {
    is >> obj.size >> obj.color >> obj.owner;
    return is;
}

ostream& operator<<(ostream &os, LightSaber &obj) {
    os << "Tamanho: " << obj.size << " Cor(es): " << obj.color << " Energia: " << obj.energy << " Dono: " << obj.owner;
    return os;
}

int main() {
    LightSaber l1 = LightSaber(100, "blue,red", true);
    LightSaber l2 = LightSaber(100, "green,red", false);
    LightSaber l3 = LightSaber(100, "blue,green", true);

    int e1 = l1;
    cout << "Energia de l1: " << e1 << endl;
    string c1 = l1;
    cout << "Cores de l1: " << c1 << endl;
    cout << l1 << endl;

    LightSaber l4 = l1 + l2;
    cout << l4 << endl;
    l4 = l2 + l3;
    cout << l4 << endl;

    l4 = l1 * l3;
    cout << l4 << endl;
    l4 = l1 * l2;
    cout << l4 << endl;

    cin >> l4;
    cout << l4 << endl;
    return 0;
}