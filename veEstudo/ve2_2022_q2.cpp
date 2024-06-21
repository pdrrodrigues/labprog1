#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class vetorOrdenado {
public:
    vetorOrdenado(int size): size(size) {}

    vector<int> getVetor() const {
        return orderedVector;
    }

    void operator<<(string &fileName) {
        ifstream inputFile;
        inputFile.open(fileName.c_str(), ios::in);

        if(!inputFile.is_open()){
            cout << "O arquivo nao abriu!" << endl;
            return;
        }

        string s;
        int count = 0;
        while(getline(inputFile, s, ',') && count < size) {
            if(!inputFile.fail()) {
                orderedVector.push_back(atoi(s.c_str()));
                ++count;
            }
        }

        sort(orderedVector.begin(), orderedVector.end());
        return;
    }

    int operator+(int num) {
        auto endItr = orderedVector.end();
        auto it = find(orderedVector.begin(), orderedVector.end(), num);
        if (endItr == it) {
            cout << "Elemento nao encontrado!" << endl;
            return -1;
        } 

        return distance(orderedVector.begin(), it);
    }

    int operator-(int num) {
        int found = std::count_if(orderedVector.begin(), orderedVector.end(), [num](int i){ return i < num; });
        return found;
    }

    friend ostream& operator<<(ostream &os, vetorOrdenado& v);
private:
    int size;
    vector<int> orderedVector;
};

ostream& operator<<(ostream &os, vetorOrdenado& v) {
    stringstream output;
    for(auto it=v.getVetor().begin(); it != v.getVetor().end(); ++it) {
        output << *it << " ";
    }

    os << output.str();
    return os;
}