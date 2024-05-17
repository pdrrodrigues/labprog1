#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <algorithm>

using namespace std;

class Soldado {
public:
    Soldado(string nome, float saude, float poderDeAtaque) {
        this->nome = nome;
        this->saude = saude;
        this->poderDeAtaque = poderDeAtaque;
    }

    float getAtaque() {
        return this->poderDeAtaque;
    }

    float getSaude() {
        return this->saude;
    }
 
    string getNome() {
        return this->nome;
    }

    void defender(float ataque) {
        this->saude = (this->saude - ataque) < 0 ? 0 : this->saude - ataque;
        return;
    }

    virtual void atacar(Soldado &sd) {
        sd.defender(this->poderDeAtaque);
        return;
    }

private:
    string nome;
    float saude;
    float poderDeAtaque;
};

class Elfo: public Soldado {
public:
    Elfo(string nome, float saude, float poderDeAtaque): Soldado(nome, saude, poderDeAtaque) {}

    void atacar(Soldado &sd) override {
        sd.defender(Soldado::getAtaque()+1);
        return;
    }
};

class Anao: public Soldado {
public:
    Anao(string nome, float saude, float poderDeAtaque): Soldado(nome, saude, poderDeAtaque) {}

    void atacar(Soldado &sd) override {
        float ataque{0};
        random_device rd{};
        default_random_engine engine{rd()};
        uniform_int_distribution chance{0, 9};

        if(chance(engine) < 4) {
            ataque = Soldado::getAtaque() + 20;
        } else {
            ataque = Soldado::getAtaque();
        }

        sd.defender(ataque);
        return;
    }
};

class Humano: public Soldado {
public:
    Humano(string nome, float saude, float poderDeAtaque): Soldado(nome, saude, poderDeAtaque) {}

    void atacar(Soldado &sd) override {
        float ataque{0};
        random_device rd{};
        default_random_engine engine{rd()};
        uniform_int_distribution chance{0, 9};

        if(chance(engine) < 1) {
            ataque = 2*Soldado::getAtaque();
        } else {
            ataque = Soldado::getAtaque();
        }

        sd.defender(ataque);
        return;
    }
};

class Sauron: public Soldado {
public:
    Sauron(float saude, float poderDeAtaque): Soldado("Sauron", 10*saude, poderDeAtaque) {}

    void atacar(Soldado &sd) override {
        float ataque{0};
        random_device rd{};
        default_random_engine engine{rd()};
        uniform_int_distribution chance{0, 9};

        if(chance(engine) < 3) {
            ataque = 2*Soldado::getAtaque();
        } else {
            ataque = Soldado::getAtaque();
        }

        sd.defender(ataque);
        return;
    }
};

class Orc: public Soldado {
public:
    Orc(string nome, float saude, float poderDeAtaque): Soldado(nome, saude, poderDeAtaque) {}

        void atacar(Soldado &sd) override {
            float ataque{0};
            random_device rd{};
            default_random_engine engine{rd()};
            uniform_int_distribution chance{0, 9};

            if(chance(engine) < 2) {
                ataque = 2.2*Soldado::getAtaque();
            } else {
                ataque = Soldado::getAtaque();
            }

            sd.defender(ataque);
            return;
        }
};

class Mago: public Soldado {
public:
    Mago(string nome, float saude, float poderDeAtaque): Soldado(nome, 3*saude, poderDeAtaque) {}

        void atacar(Soldado &sd) override {
            float ataque{0};
            random_device rd{};
            default_random_engine engine{rd()};
            uniform_int_distribution chance{0, 9};

            if(chance(engine) < 5) {
                ataque = 1.5*Soldado::getAtaque();
            } else {
                ataque = Soldado::getAtaque();
            }

            sd.defender(ataque);
            return;
        }
};

int main(){
    vector<Soldado*> exercito;

    exercito.push_back(new Sauron(50, 10));
    exercito.push_back(new Mago("Gandolf", 100, 15));
    exercito.push_back(new Orc("Orc1", 50, 10));
    exercito.push_back(new Orc("Orc2", 50, 10));
    exercito.push_back(new Orc("Orc3", 50, 10));
    exercito.push_back(new Orc("Orc4", 50, 10));
    exercito.push_back(new Orc("Orc5", 50, 10));
    exercito.push_back(new Orc("Orc6", 50, 10));
    exercito.push_back(new Orc("Orc7", 50, 10));
    exercito.push_back(new Orc("Orc8", 50, 10));
    exercito.push_back(new Orc("Orc9", 50, 10));
    exercito.push_back(new Orc("Orc10", 50, 10));
    exercito.push_back(new Humano("Barbosa1", 50, 10));
    exercito.push_back(new Humano("Barbosa2", 50, 10));
    exercito.push_back(new Humano("Barbosa3", 50, 10));
    exercito.push_back(new Humano("Barbosa4", 50, 10));
    exercito.push_back(new Humano("BarbosaPrime", 550, 10));
    exercito.push_back(new Anao("Camatari1", 50, 10));
    exercito.push_back(new Anao("Camatari2", 50, 10));
    exercito.push_back(new Anao("Camatari3", 50, 10));
    exercito.push_back(new Anao("Camatari4", 50, 10));
    exercito.push_back(new Anao("Camatari5", 50, 10));
    exercito.push_back(new Elfo("Caimi1", 50, 10));
    exercito.push_back(new Elfo("Caimi2", 50, 10));
    exercito.push_back(new Elfo("Caimi3", 50, 10));
    exercito.push_back(new Elfo("Caimi4", 50, 10));
    exercito.push_back(new Elfo("Caimi5", 50, 10));

    random_device rd{};
    default_random_engine engine{rd()};

    while(exercito.size() > 1) {
        shuffle(exercito.begin(), exercito.end(), engine);
        vector<Soldado*> temp{};

        while(exercito.size() > 1) {
            Soldado *c1 = exercito.back();
            exercito.pop_back();
            Soldado *c2 = exercito.back();
            exercito.pop_back();

            while(c1->getSaude() != 0 && c2->getSaude() != 0) {
                c1->atacar(*c2);
                Soldado *tempSd = c1;
                c1 = c2;
                c2 = tempSd;
            }

            if(c1->getSaude() == 0) {
                temp.push_back(c2);
            } else {
                temp.push_back(c1);
            }
        }

        exercito.insert(exercito.end(), temp.begin(), temp.end());
    }

    Soldado *ganhador = exercito.back();
    exercito.pop_back();
    cout << "O ganhador da batalha foi " << ganhador->getNome() << endl;

    return 0;
};