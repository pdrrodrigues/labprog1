#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

class Character {
public:
    Character(string nome, string profissao) {
        this->nome = nome;
        setProfissao(profissao);
    }

    string getNome() {
        return this->nome;
    }

    string getProfissao() {
        return this->profissao;
    }

    void setProfissao(string profissao) {
        this->profissao = profissao;
        return;
    }

private:
    string nome;
    string profissao;
};

class CharacterDatabase {
public:
    CharacterDatabase() {}

    void addCharacter(Character &ch) {
        int index = this->searchDatabase(ch.getNome());

        if(index >= 0) {
            cout << "Personagem já cadastrado!" << endl;
        } else {
            this->database.push_back(&ch);
        }
        
        return;
    }

    void deleteCharacter(string nome) {
        int index = this->searchDatabase(nome);

        if(index < 0) {
            cout << "Personagem não existente no banco de dados" << endl;
            return;
        } else {
            this->database.erase(database.begin() + index);
        }

        for(int j = 0; j<this->relation.size(); j++){
            if(this->relation[j].second.first.getNome() == nome || this->relation[j].second.second.getNome() == nome) {
                this->relation.erase(relation.begin()+j);
            }
        }

        cout << "Personagem deletado com sucesso!" << endl;
        return;
    }

    void editCharacter(string nome, string novaProfissao) {
        int index = this->searchDatabase(nome);

        if(index < 0) {
            cout << "Personagem não existente no banco de dados" << endl;
        } else {
            this->database[index]->setProfissao(novaProfissao);
            cout << "Personagem editado com sucesso!" << endl;
        }

        return;
    }

    string searchCharacter(string nome) {
        int index = this->searchDatabase(nome);

        if(index < 0) {
            return "Personagem nao existente no banco de dados";
        } else {
            return this->database[index]->getProfissao();
        }
    }

    void relate(Character &c1, Character &c2, string relationship) {
        bool exist = this->searchDatabase(c1.getNome()) < 0 ? true : false; 

        if(exist) {
            cout << "Personagem " << c1.getNome() << " não Cadastrado!" << endl;
            return;
        }

        exist = this->searchDatabase(c2.getNome()) < 0 ? true : false;

        if(exist) {
            cout << "Personagem " << c2.getNome() << " não Cadastrado!" << endl;
            return;
        }

        this->relation.push_back(make_pair(relationship, make_pair(c1, c2)));
        return;
    }

    void imprimir() {
        cout << "Personagens: " << endl;
        for(int i=0; i<database.size(); i++) {
            cout << "Nome: " << database[i]->getNome() << ", Profissao: " << database[i]->getProfissao() << endl;
        }

        cout << "\nRelacionamentos: " << endl;
        for(int j=0; j<relation.size(); j++) {
            cout << relation[j].second.first.getNome() << " e " << relation[j].second.second.getNome() << " sao " << relation[j].first << endl;
        }
    }
private:
    vector<Character*> database;
    vector<pair<string, pair<Character, Character>>> relation;

    int searchDatabase(string nome) {
        int index = -1;

        for(int i=0; i<database.size(); i++) {
            if(database[i]->getNome() == nome){
                index = i;
                break;
            }
        }

        return index;
    }
};

int main() {
    CharacterDatabase database;
    Character c1 = Character("Rachel Green", "Garçonete"); Character c2 = Character("Monica Geller", "Chef");
    Character c3 = Character("Phoebe Buffay", "Massagista"); Character c4 = Character("Chandler Bing", "Desconhecido");
    Character c5 = Character("Ross Geller", "Professor"); Character c6 = Character("Joey Tribbiani", "Ator");

    database.addCharacter(c1); database.addCharacter(c2); database.addCharacter(c3);
    database.addCharacter(c4); database.addCharacter(c5); database.addCharacter(c6);

    database.editCharacter("Rachel Green", "Design de Moda");
    cout << database.searchCharacter("Gunther") << endl; 
    cout << database.searchCharacter("Rachel Green") << endl;

    database.relate(c2, c5, "irmãos"); database.relate(c2, c4, "casados");
    database.relate(c1, c2, "roommates"); database.relate(c4, c6, "roommates");

    database.deleteCharacter("Phoebe Buffay"); 
    database.imprimir();
}