#include <iostream>
#include <random>
#include <array>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Lig4 {
public:
    Lig4(int n, int m): m(m), n(n), vez('X') {
        tabuleiro = new char*[this->n];
        for(int i = 0; i < this->n; i++) {
            tabuleiro[i] = new char[this->m];
        }

        for(int i = 0; i < this->n; i++) {
            for(int j = 0; j < this->m; j++) {
                tabuleiro[i][j] = '.';
            }
        }
    }

    Lig4(const Lig4 &cp) : m(cp.m), n(cp.n), vez(cp.vez) {
        tabuleiro = new char*[n];
        for(int i = 0; i < n; ++i) {
            tabuleiro[i] = new char[m];
            for(int j = 0; j < m; ++j) {
                tabuleiro[i][j] = cp.tabuleiro[i][j];
            }
        }
    }

    ~Lig4() {
        for(int i = 0; i < n; i++) {
            delete[] tabuleiro[i];
        }
        delete[] tabuleiro;
    }

    void exibe() const {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                cout << " " << tabuleiro[i][j];
            }
            cout << "\n";
        }

        for(int k = 0; k < m; k++) {
            cout << " " << k + 1;
        }
        cout << "\n";
    }

    char getJogador() const {
        return vez;
    }

    char** getTabuleiro() const {
        return tabuleiro;
    }

    void alternarJogador() {
        vez = (vez == 'O') ? 'X' : 'O';
    }

    bool jogadaValida(int mi) const {
        return tabuleiro[0][mi] == '.';
    }

    void jogada(int mi) {
        for(int i = n - 1; i >= 0; i--) {
            if(tabuleiro[i][mi] == '.') {
                tabuleiro[i][mi] = vez;
                break;
            }
        }
        alternarJogador();
    }

    void desfazerJogada(int mi) {
        for(int i = 0; i < n; i++) {
            if(tabuleiro[i][mi] != '.') {
                tabuleiro[i][mi] = '.';
                alternarJogador();
                break;
            }
        }
    }

    bool jogadaVencedora(char jogador) const {
        int sequenciaVencedora = 0;
        
        // Horizontal check
        for(int r = 0; r < n; r++) {
            for(int c = 0; c < m - 3; c++) {
                if(tabuleiro[r][c] == jogador && tabuleiro[r][c+1] == jogador && tabuleiro[r][c+2] == jogador && tabuleiro[r][c+3] == jogador) {
                    return true;
                }
            }
        }
        
        // Vertical check
        for(int c = 0; c < m; c++) {
            for(int r = 0; r < n - 3; r++) {
                if(tabuleiro[r][c] == jogador && tabuleiro[r+1][c] == jogador && tabuleiro[r+2][c] == jogador && tabuleiro[r+3][c] == jogador) {
                    return true;
                }
            }
        }
        
        // Diagonal check (\ direction)
        for(int r = 0; r < n - 3; r++) {
            for(int c = 0; c < m - 3; c++) {
                if(tabuleiro[r][c] == jogador && tabuleiro[r+1][c+1] == jogador && tabuleiro[r+2][c+2] == jogador && tabuleiro[r+3][c+3] == jogador) {
                    return true;
                }
            }
        }
        
        // Diagonal check (/ direction)
        for(int r = 3; r < n; r++) {
            for(int c = 0; c < m - 3; c++) {
                if(tabuleiro[r][c] == jogador && tabuleiro[r-1][c+1] == jogador && tabuleiro[r-2][c+2] == jogador && tabuleiro[r-3][c+3] == jogador) {
                    return true;
                }
            }
        }

        return false;
    }

private:
    int m;
    int n;
    char vez;
    char **tabuleiro;
};

class Lig4Tradicional: public Lig4 {
public:
    Lig4Tradicional(int dificuldade, default_random_engine engine) 
        : Lig4(NUM_LIN, NUM_COL), dificuldade(dificuldade), engine(engine) {}

    Lig4Tradicional(const Lig4Tradicional &cp) 
        : Lig4(cp), dificuldade(cp.dificuldade), engine(cp.engine) {}

    int jogadorAleatorio() {
        uniform_int_distribution<int> chance(0, NUM_COL - 1);
        return chance(engine);
    }

    int jogadorIA(int turnos) {
        return miniMax(dificuldade, INT_MIN, INT_MAX, turnos)[1];
    }

    array<int, 2> miniMax(int profundidade, int alfa, int beta, int turnos) {
        if (profundidade == 0 || turnos >= (NUM_COL * NUM_LIN)) {
            return array<int, 2>{valorTabuleiro(this->getTabuleiro(), 'X'), -1};
        }

        if (this->getJogador() == 'X') {
            array<int, 2> valorAtual = {INT_MIN, -1};
            if (this->jogadaVencedora('O')) {
                return valorAtual;
            }
            for (int c = 0; c < NUM_COL; c++) {
                if (this->jogadaValida(c)) {
                    this->jogada(c);
                    int valor = this->miniMax(profundidade - 1, alfa, beta, turnos + 1)[0];
                    this->desfazerJogada(c);
                    if (valor > valorAtual[0]) {
                        valorAtual = {valor, c};
                    }
                    alfa = max(alfa, valorAtual[0]);
                    if (alfa >= beta) { break; }
                }
            }
            return valorAtual;
        } else {
            array<int, 2> valorAtual = {INT_MAX, -1};
            if (this->jogadaVencedora('X')) {
                return valorAtual;
            }
            for (int c = 0; c < NUM_COL; c++) {
                if (this->jogadaValida(c)) {
                    this->jogada(c);
                    int valor = this->miniMax(profundidade - 1, alfa, beta, turnos + 1)[0];
                    this->desfazerJogada(c);
                    if (valor < valorAtual[0]) {
                        valorAtual = {valor, c};
                    }
                    beta = min(beta, valorAtual[0]);
                    if (alfa >= beta) { break; }
                }
            }
            return valorAtual;
        }
    }

    static int valorTabuleiro(char** tabuleiro, char p) {
        int score = 0;
        vector<char> vl(NUM_COL);
        vector<char> vc(NUM_LIN);
        vector<char> conjunto(4);

        for (int r = 0; r < NUM_LIN; r++) {
            for (int c = 0; c < NUM_COL; c++) {
                vl[c] = tabuleiro[r][c];
            }
            for (int c = 0; c < NUM_COL - 3; c++) {
                for (int i = 0; i < 4; i++) {
                    conjunto[i] = vl[c + i];
                }
                score += valorConjunto(conjunto, p);
            }
        }

        for (int c = 0; c < NUM_COL; c++) {
            for (int r = 0; r < NUM_LIN; r++) {
                vc[r] = tabuleiro[r][c];
            }
            for (int r = 0; r < NUM_LIN - 3; r++) {
                for (int i = 0; i < 4; i++) {
                    conjunto[i] = vc[r + i];
                }
                score += valorConjunto(conjunto, p);
            }
        }

        for (int r = 0; r < NUM_LIN - 3; r++) {
            for (int c = 0; c < NUM_COL; c++) {
                vl[c] = tabuleiro[r][c];
            }
            for (int c = 0; c < NUM_COL - 3; c++) {
                for (int i = 0; i < 4; i++) {
                    conjunto[i] = tabuleiro[r + i][c + i];
                }
                score += valorConjunto(conjunto, p);
            }
        }

        for (int r = 0; r < NUM_LIN - 3; r++) {
            for (int c = 0; c < NUM_COL; c++) {
                vl[c] = tabuleiro[r][c];
            }
            for (int c = 0; c < NUM_COL - 3; c++) {
                for (int i = 0; i < 4; i++) {
                    conjunto[i] = tabuleiro[r + 3 - i][c + i];
                }
                score += valorConjunto(conjunto, p);
            }
        }
        return score;
    }

    static int valorConjunto(const vector<char>& v, char p) {
        int bom = 0;
        int ruim = 0;
        int vazio = 0;
        for (char ch : v) {
            if (ch == p) bom++;
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

    char jogar() {
        bool fim = false;
        int turnos = 0;
        while(!fim) {
            if(this->getJogador() == 'X') {
                this->jogada(jogadorIA(turnos));
            } else if (this->getJogador() == 'O') {
                bool valido;
                int jogada;
                do {
                    jogada = this->jogadorAleatorio();
                    valido = this->jogadaValida(jogada);
                } while(!valido);

                this->jogada(jogada);
            }

            if (turnos == NUM_COL * NUM_LIN) {
                fim = true;
            }
            fim = this->jogadaVencedora(this->getJogador() == 'X' ? 'O' : 'X');
            ++turnos;
        }
        return ((this->getJogador() == 'X') ? 'O' : 'X');
    }

    ~Lig4Tradicional() {}

private:
    int dificuldade;
    default_random_engine engine;
    static const int NUM_COL = 7;
    static const int NUM_LIN = 6;
};

int main() {
    const int total = 100;
    int count = 0;
    random_device rd{};
    default_random_engine engine{rd()};

    for(int i = 0; i < total; ++i){
        char ganhador;
        Lig4Tradicional l = Lig4Tradicional(5, engine);
        ganhador = l.jogar();

        if(ganhador == 'X') {
            ++count;
        }
    }

    cout << "WinRate: " << count << endl;
    return 0;
}