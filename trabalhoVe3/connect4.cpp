#include <iostream>
#include <random>
#include <array>
#include <vector>
#include <climits>

using namespace std;

enum Resultado_atual { Continua, Vitoria_Jogador_1, Vitoria_Jogador_2, Empate };

class Lig4 {
public:
    Lig4(int n, int m): m(m), n(n) {
        tabuleiro = new char*[this->n];
        for(int i=0; i<this->n; i++) {
            tabuleiro[i] = new char[this->m];
        }

        for(int i=0; i<this->n; i++) {
            for(int j=0; j<this->m; j++) {
                tabuleiro[i][j] = '.';
            }
        }
    }

    // Lig4(const Lig4 &cp) {
    //     m = cp.m;
    //     n = cp.n;
    //     vez = cp.vez;
    //     tabuleiro = new char*[n];
    //     for(int i = 0; i < n; ++i) {
    //         for(int j = 0; j < m; ++j) {
    //             tabuleiro[i] = new char[m];
    //         }
    //     }

    //     for(int i = 0; i < n; ++i) {
    //         for(int j = 0; j < m; ++j) {
    //             tabuleiro[i][j] = cp.tabuleiro[i][j];
    //         }
    //     }
    // }

    void exibe() {
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                cout << " " << tabuleiro[i][j];
            }
            cout << "\n";
        }

        for(int k=0; k<m; k++) {
            cout << " " << k+1;
        }

        cout << "\n";

        return;
    }

    char getJogador() const {
        return vez;
    }

    char** getTabuleiro() const {
        return tabuleiro;
    }

    void alternarJogador() {
        vez = (vez == 'O') ? 'X' : 'O';
        return;
    }

    bool jogadaValida(int mi) {
        return tabuleiro[0][mi] == '.';
    }

    void jogada(int mi) {
        for(int i=n-1; i>=0; --i) {
            if(tabuleiro[i][mi] == '.') {
                tabuleiro[i][mi] = vez;
                break;
            }
        }

        alternarJogador();
        return;
    }

    void desfazerJogada(int mi) {
        for (int i = 0; i < n; ++i) {
            if (tabuleiro[i][mi] != '.') {
                tabuleiro[i][mi] = '.';
                alternarJogador();
                break;
            }
        }
        
        return;
    }

    void resetar() {
        vez = 'X';
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                tabuleiro[i][j] = '.';
            }
        }

        return;
    }

    int jogadaVencedora(char jogador) const {
        int pontos = 0;       
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m - 3; j++) {
                if(tabuleiro[i][j] == jogador && tabuleiro[i][j+1] == jogador && tabuleiro[i][j+2] == jogador && tabuleiro[i][j+3] == jogador) {
                    ++pontos;
                }
            }
        }
        
        for(int j = 0; j < m; j++) {
            for(int i = 0; i < n - 3; i++) {
                if(tabuleiro[i][j] == jogador && tabuleiro[i+1][j] == jogador && tabuleiro[i+2][j] == jogador && tabuleiro[i+3][j] == jogador) {
                    ++pontos;
                }
            }
        }
        
        for(int i = 0; i < n - 3; i++) {
            for(int j = 0; j < m - 3; j++) {
                if(tabuleiro[i][j] == jogador && tabuleiro[i+1][j+1] == jogador && tabuleiro[i+2][j+2] == jogador && tabuleiro[i+3][j+3] == jogador) {
                    ++pontos;
                }
            }
        }
        
        for(int i = 3; i < n; i++) {
            for(int j = 0; j < m - 3; j++) {
                if(tabuleiro[i][j] == jogador && tabuleiro[i-1][j+1] == jogador && tabuleiro[i-2][j+2] == jogador && tabuleiro[i-3][j+3] == jogador) {
                    ++pontos;
                }
            }
        }

        return pontos;
    }

    bool cheio() {
        bool cheio = true;
        for(int j = 0; j < m; ++j) {
            if(tabuleiro[0][j] == '.'){
                cheio = false;
                break;
            }
        }

        return cheio;
    }

    Resultado_atual resultadoFinal() {
        int jogador1Pontos = this->jogadaVencedora('X');
        int jogador2Pontos = this->jogadaVencedora('O');
        if(jogador1Pontos > jogador2Pontos) {
            return Vitoria_Jogador_1;
        } else if (jogador1Pontos < jogador2Pontos) {
            return Vitoria_Jogador_2;
        } else if(!cheio()) {
            return Continua;
        } else {
            return Empate;
        }
    }

    ~Lig4() {
        for(int i=0; i<n; i++) {
            delete[] tabuleiro[i];
        }

        delete[] tabuleiro;
    }

private:
    int m;
    int n;
    char vez = 'X';
    char **tabuleiro;
};

class Lig4Tradicional: public Lig4 {
public:
    Lig4Tradicional(int dificuldade): Lig4(NUM_LIN, NUM_COL), dificuldade(dificuldade) {
        for(int i = 0; i<NUM_COL; ++i) {
            this->ordemColunas.push_back(NUM_COL/2 + (1-2*(i%2))*(i+1)/2);
        }
    }

    // Lig4Tradicional(Lig4Tradicional &cp): Lig4(cp), dificuldade(cp.dificuldade) {}

    int jogadorAleatorio() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dist(0, NUM_COL - 1);
        return dist(gen);
    }

    int jogadorIA(int turnos) {
        return miniMax(dificuldade, INT_MIN, INT_MAX, turnos)[1];
    }

    array<int, 2> miniMax(int profundidade, int alfa, int beta, int turnos) {
        if (profundidade == 0 || profundidade >= (NUM_COL * NUM_LIN) - turnos) {
            return array<int, 2>{this->valorTabuleiro('X'), -1};
        }
        if (this->getJogador() == 'X') {
            array<int, 2> valorAtual = {INT_MIN, -1};
            if (this->resultadoFinal() == Vitoria_Jogador_2) {
                return valorAtual;
            } 
            for (int j = 0; j < NUM_COL; j++) {
                if (this->jogadaValida(ordemColunas[j])) {
                    this->jogada(ordemColunas[j]);
                    int valor = this->miniMax(profundidade - 1, alfa, beta, turnos)[0];
                    this->desfazerJogada(ordemColunas[j]);
                    if (valor > valorAtual[0]) {
                        valorAtual = {valor, ordemColunas[j]};
                    }
                    alfa = max(alfa, valorAtual[0]);
                    if (alfa >= beta) { break; }
                }
            }
            return valorAtual;
        }
        else {
            array<int, 2> valorAtual = {INT_MAX, -1};
            if (this->resultadoFinal() == Vitoria_Jogador_1) {
                return valorAtual;
            }
            for (int j = 0; j < NUM_COL; j++) {
                if (this->jogadaValida(ordemColunas[j])) {
                    this->jogada(ordemColunas[j]);
                    int valor = this->miniMax(profundidade - 1, alfa, beta, turnos)[0];
                    this->desfazerJogada(ordemColunas[j]);
                    if (valor < valorAtual[0]) {  
                        valorAtual = {valor, ordemColunas[j]};
                    }
                    beta = min(beta, valorAtual[0]);
                    if (alfa >= beta) { break; }
                }
            }
            return valorAtual;
        } 
    }

    int valorTabuleiro(char jogador) {
        int valor = 0;
        vector<char> vl(NUM_COL);
        vector<char> vc(NUM_LIN);
        vector<char> conjunto(4);
        
        for (int lin = 0; lin < NUM_LIN; lin++) {
            for (int col = 0; col < NUM_COL; col++) {
                vl[col] = this->getTabuleiro()[lin][col];
            }
            for (int col = 0; col < NUM_COL - 3; col++) {
                for (int i = 0; i < 4; i++) {
                    conjunto[i] = vl[col + i];
                }
                valor += valorConjunto(conjunto, jogador);
            }
        }
        
        for (int col = 0; col < NUM_COL; col++) {
            for (int lin = 0; lin < NUM_LIN; lin++) {
                vc[lin] = this->getTabuleiro()[lin][col];
            }
            for (int lin = 0; lin < NUM_LIN - 3; lin++) {
                for (int i = 0; i < 4; i++) {
                    conjunto[i] = vc[lin + i];
                }
                valor += valorConjunto(conjunto, jogador);
            }
        }
        
        for (int lin = 0; lin < NUM_LIN - 3; lin++) {
            for (int col = 0; col < NUM_COL - 3; col++) {
                for (int i = 0; i < 4; i++) {
                    conjunto[i] = this->getTabuleiro()[lin + i][col + i];
                }
                valor += valorConjunto(conjunto, jogador);
            }
        }

        for (int lin = 0; lin < NUM_LIN - 3; lin++) {
            for (int col = 0; col < NUM_COL - 3; col++) {
                for (int i = 0; i < 4; i++) {
                    conjunto[i] = this->getTabuleiro()[lin + 3 - i][col + i];
                }
                valor += valorConjunto(conjunto, jogador);
            }
        }
        return valor;
    }

    static int valorConjunto(vector<char> v, char jogador) {
        int bom = 0;
        int ruim = 0;
        int vazio = 0;
        for (char ch : v) {
            if (ch == jogador) bom++;
            if (ch == 'O' || ch == 'X') ruim++;
            if (ch == '.') vazio++;
        }
        ruim -= bom;
        return heuristica(bom, ruim, vazio);
    }

    static int heuristica(int b, int r, int v) {
        int valor = 0;
        if (b == 4) { valor += 500001; }
        else if (b == 3 && v == 1) { valor += 5000; }
        else if (b == 2 && v == 2) { valor += 500; }
        else if (r == 2 && v == 2) { valor -= 501; }
        else if (r == 3 && v == 1) { valor -= 5001; }
        else if (r == 4) { valor -= 500000; }
        return valor;
    }

    Resultado_atual jogar() {
        Resultado_atual fim = Continua;
        int turnos = 0;
        while(fim == Continua) {
            if(this->getJogador() == 'X') {
                this->jogada(this->jogadorIA(turnos));
            } else if (this->getJogador() == 'O') {
                bool valido;
                int jogada;
                do{
                    jogada = this->jogadorAleatorio();
                    valido = this->jogadaValida(jogada);
                } while(!valido);

                this->jogada(jogada);
            }

            fim = this->resultadoFinal();
            ++turnos;
        }
        return fim;
    }

    ~Lig4Tradicional() {}
private:
    int dificuldade;
    static const int NUM_COL = 7;
    static const int NUM_LIN = 6;
    vector<int> ordemColunas;
};

int main() {
    // const int total = 100;
    int count = 0;
    Resultado_atual ganhador;
    Lig4Tradicional l = Lig4Tradicional(5);

    // for(int i = 0; i < total; ++i){
    //     ganhador = l.jogar();
    //     l.exibe();
    //     l.resetar();

    //     if(ganhador == Vitoria_Jogador_1) {
    //         ++count;
    //         cout << "Vitorias do jogador 1: " << count << endl;
    //     }
    // }

    do{
        ganhador = l.jogar();
        l.exibe();
        l.resetar();

        if(ganhador == Vitoria_Jogador_1) {
            ++count;
            cout << "Vitorias do jogador 1: " << count << endl;
        }
    } while(ganhador == Vitoria_Jogador_1);

    if(ganhador == Empate) {
        cout << "Empate" << endl;
    } else {
        cout << "Vitorias do jogador 2" << endl;
    }
    
    return 0;
}