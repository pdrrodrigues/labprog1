#include<bits/stdc++.h>

using namespace std;

class Student{
    private:
        string cpf;
        string name;
        string numberCode;
        vector<string> disciplines;
    
    public:
        Student(string cpf, string name, string numberCode, vector<string> disciplines){
            this->cpf = cpf;
            this->name = name;
            this->numberCode = numberCode;
            this->disciplines = disciplines;
        }

        string getCPF(){
            return cpf;
        }

        string getName(){
            return name;
        }

        string getNumberCode(){
            return numberCode;
        }

        vector<string>& getDisciplines(){
            return disciplines;
        }
};

class Disciplines{
    private:
        string nameDiscipline;
        string name;
        string numberCode;
        string credits;
    
    public:
        Disciplines(string nameDiscipline, string name, string numberCode, string credits){
            this->nameDiscipline = nameDiscipline;
            this->name = name;
            this->numberCode = numberCode;
            this->credits = credits;
        }

        string getNameDiscipline(){
            return nameDiscipline;
        }

        string getName(){
            return name;
        }

        string getNumberCode(){
            return numberCode;
        }

        string getCredits(){
            return credits;
        }
};

void printLine(){
    cout << string(50, '-') << endl;
}

void insertStudent(vector<Student>& s, vector<Disciplines>& d){
    string cpf;
    string name;
    string numberCode;
    vector<string> disciplines;

    cout << "Insira o codigo do aluno: ";
    cin >> numberCode;
    cout << "Insira o nome do aluno(ate 20 caracteres): ";
    cin >> name;
    cout << "Insira o cpf do aluno: ";
    cin >> cpf;

    int count = 0;
    while(count < 5){
        string temps;
        cout << "Insira ate cinco disciplinas ou digite s para sair: ";
        cin >> temps;
        if (temps == "s") {
            break;
        }
        bool has = false;
        for(int i=0; i<d.size(); i++){
            if(d[i].getNumberCode() == temps){
                disciplines.push_back(temps);
                has = true;
                count++;
            }
        }
        if(!has){
            cout << "Disciplina inexistente\n";
        }
    }

    Student temp = Student(cpf, name, numberCode, disciplines);
    s.push_back(temp);
}

void insertDiscipline(vector<Disciplines>& d){
    string nameDiscipline;
    string name;
    string numberCode;
    string credits;

    cout << "Insira o codigo da disciplina: ";
    cin >> numberCode;
    cout << "Insira o nome da disciplina(ate 30 caracteres): ";
    cin >> nameDiscipline;
    cout << "Insira o nome do professor(ate 20 caracteres): ";
    cin >> name;
    cout << "Insira a quantidade de creditos(ate 2 digitos): ";
    cin >> credits;
    
    Disciplines temp = Disciplines(nameDiscipline, name, numberCode, credits);
    d.push_back(temp);
}

void insertData2(vector<Student>& s, vector<Disciplines>& d){
    int choice2;
    do{
        printLine();
        cout << "ESCOLHA A OPCAO\n";
        printLine();
        cout << "1.ALUNO\n";
        cout << "2.DISCIPLINA\n";
        printLine();
        cout << "Digite a sua escolha: ";
        cin >> choice2;

        switch(choice2){
                case 1: insertStudent(s, d); break;
                case 2: insertDiscipline(d); break;
                default: break;
        }
    }while(choice2 != 1 && choice2 != 2);
}

void insertData(vector<Student>& s1, vector<Student>& s2, vector<Disciplines>& d1, vector<Disciplines>& d2){
    int choice1;
    do{
        printLine();
        cout << "ESCOLHA O PERIODO\n";
        printLine();
        cout << "1.PRIMEIRO PERIODO\n";
        cout << "2.SEGUNDO PERIODO\n";
        printLine();
        cout << "Digite a sua escolha: ";
        cin >> choice1;

        switch(choice1){
                case 1: insertData2(s1, d1); break;
                case 2: insertData2(s2, d2); break;
                default: break;
        }
    }while(choice1 != 1 && choice1 != 2);
}

void consultStudent(vector<Student>& s){
    string numberCode;
    cout << "Insira o codigo do aluno que deseja procurar: ";
    cin >> numberCode;
    for(int i=0; i<s.size(); i++){
        if(s[i].getNumberCode() == numberCode){
            cout << "Nome do Aluno: ";
            cout << s[i].getName();
            cout << "\nCodigo do Aluno: ";
            cout << s[i].getNumberCode();
            cout << "\nCPF do Aluno: ";
            cout << s[i].getCPF();
            cout << "\nDisciplinas do Aluno: \n";
            for(string str: s[i].getDisciplines()){
                cout << str << endl;
            }
            return;
        }
    }
    cout << "Aluno nao encontrado";
}

void consultDiscipline(vector<Student>& s, vector<Disciplines>& d){
    string numberCode;
    cout << "Insira o codigo da disciplina que deseja procurar: ";
    cin >> numberCode;
    bool has = false;
    for(int i=0; i<d.size(); i++){
        if(d[i].getNumberCode() == numberCode){
            has = true;
            cout << "Nome da Disciplina: ";
            cout << d[i].getNameDiscipline();
            cout << "\nCodigo da Disciplina: ";
            cout << d[i].getNumberCode();
            cout << "\nNome do Professor: ";
            cout << d[i].getName();
            cout << "\nAlunos matriculados na disciplina: \n";
            for(int i=0; i<s.size(); i++){
                for(string str: s[i].getDisciplines()){
                    if(str == numberCode){
                        cout << s[i].getNumberCode() << endl;
                    }
                }
            }
        }
    }
    if(!has){
        cout << "Disciplina nao encontrada";
    }
}

void consult2(vector<Student>& s, vector<Disciplines>& d){
    int choice2;
    do{
        printLine();
        cout << "ESCOLHA A OPCAO\n";
        printLine();
        cout << "1.ALUNO\n";
        cout << "2.DISCIPLINA\n";
        printLine();
        cout << "Digite a sua escolha: ";
        cin >> choice2;

        switch(choice2){
                case 1: consultStudent(s); break;
                case 2: consultDiscipline(s, d); break;
                default: break;
        }
    }while(choice2 != 1 && choice2 != 2);
}

void consult(vector<Student>& s1, vector<Student>& s2, vector<Disciplines>& d1, vector<Disciplines>& d2){
    int choice1;
    do{
        printLine();
        cout << "ESCOLHA O PERIODO\n";
        printLine();
        cout << "1.PRIMEIRO PERIODO\n";
        cout << "2.SEGUNDO PERIODO\n";
        printLine();
        cout << "Digite a sua escolha: ";
        cin >> choice1;

        switch(choice1){
                case 1: consult2(s1, d1); break;
                case 2: consult2(s2, d2); break;
                default: break;
        }
    }while(choice1 != 1 && choice1 != 2);
}

void removeStudent(vector<Student>& s){
    string numberCode;
    cout << "Insira o codigo do aluno que deseja eliminar: ";
    cin >> numberCode;
    for(int i=0; i<s.size(); i++){
        if(s[i].getNumberCode() == numberCode){
            s.erase(s.begin() + i);
            return;
        }
    }
    cout << "Aluno nao encontrado";
}

void removeDiscipline(vector<Student>& s, vector<Disciplines>& d){
    string numberCode;
    cout << "Insira o codigo da disciplina que deseja remover: ";
    cin >> numberCode;
    bool has = false;
    for(int i=0; i<d.size(); i++){
        if(d[i].getNumberCode() == numberCode){
            has = true;
            d.erase(d.begin() + i);
            for(int i=0; i<s.size(); i++){
                vector<string> temp = s[i].getDisciplines();
                for(int j=0; j<temp.size(); j++){
                    if(temp[j] == numberCode){
                        s[i].getDisciplines().erase(s[i].getDisciplines().begin() + j);
                    }
                }
            }
        }
    }
    if(!has){
        cout << "Disciplina nao encontrada";
    }
}

void remove2(vector<Student>& s, vector<Disciplines>& d){
    int choice2;
    do{
        printLine();
        cout << "ESCOLHA A OPCAO\n";
        printLine();
        cout << "1.ALUNO\n";
        cout << "2.DISCIPLINA\n";
        printLine();
        cout << "Digite a sua escolha: ";
        cin >> choice2;

        switch(choice2){
                case 1: removeStudent(s); break;
                case 2: removeDiscipline(s, d); break;
                default: break;
        }
    }while(choice2 != 1 && choice2 != 2);
}

void remove(vector<Student>& s1, vector<Student>& s2, vector<Disciplines>& d1, vector<Disciplines>& d2){
    int choice1;
    do{
        printLine();
        cout << "ESCOLHA O PERIODO\n";
        printLine();
        cout << "1.PRIMEIRO PERIODO\n";
        cout << "2.SEGUNDO PERIODO\n";
        printLine();
        cout << "Digite a sua escolha: ";
        cin >> choice1;

        switch(choice1){
                case 1: remove2(s1, d1); break;
                case 2: remove2(s2, d2); break;
                default: break;
        }
    }while(choice1 != 1 && choice1 != 2);
}

vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void writeFileDisciplines(vector<Disciplines>& d, string fileName){
    ofstream outFile(fileName, ios::trunc);
    if (!outFile.is_open()) {
        cerr << "Error opening the file for writing." << endl;
        return;
    }

    for(int i=0; i<d.size(); i++){
        string output = d[i].getNameDiscipline();
        output += ";";
        output += d[i].getName();
        output += ";";
        output += d[i].getNumberCode();
        output += ";";
        output += d[i].getCredits();
        output += "\n";
        outFile << output;
    }

    outFile.close();
}

void readFileDisciplines(vector<Disciplines>& d, string fileName){
    ifstream file(fileName);

    if (!file.is_open()) {
        cerr << "Error opening the file." << endl;
        return;
    }

    string line;
    while(getline(file, line)){
        vector<string> parts = split(line, ';');

        if (parts.size() < 4) {
            cerr << "Invalid line: " << line << endl;
            continue;
        }

        Disciplines temp = Disciplines(parts[0], parts[1], parts[2], parts[3]);
        d.push_back(temp);
    }
}

void writeFileStudent(vector<Student>& s, string fileName){
    ofstream outFile(fileName, ios::trunc);
    if (!outFile.is_open()) {
        cerr << "Error opening the file for writing." << endl;
        return;
    }

    for(int i=0; i<s.size(); i++){
        string output = s[i].getCPF();
        output += ";";
        output += s[i].getName();
        output += ";";
        output += s[i].getNumberCode();
        output += ";";
        vector<string> temp = s[i].getDisciplines();
        for(int j=0; j<temp.size(); j++){
            output += temp[i];
            output += ";";
        }

        output += "\n";
        outFile << output;
    }

    outFile.close();
}

void readFileStudent(vector<Student>& s, vector<Disciplines>& d, string fileName){
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Error opening the file." << endl;
        return;
    }

    string line;
    while(getline(file, line)){
        vector<string> parts = split(line, ';');

        if (parts.size() < 4) {
            cerr << "Invalid line: " << line << endl;
            continue;
        }

        string cpf = parts[0];
        string name = parts[1];
        string numberCode = parts[2];

        vector<string> disciplines(parts.begin() + 3, parts.end());

        for(int j=0; j<disciplines.size(); j++){
            bool hasAny = false;
            for(int i=0; i<d.size(); i++){
                if(d[i].getNumberCode() == disciplines[j]){
                    hasAny = true;
                }
            }
            if(!hasAny){
                disciplines.erase(disciplines.begin() + j);
            }
        }

        Student temp = Student(cpf, name, numberCode, disciplines);
        s.push_back(temp);
    }
}

int main(){
    vector<Student> s1, s2;
    vector<Disciplines> d1, d2;

    readFileDisciplines(d1, "disciplinas1.txt");
    readFileStudent(s1, d1, "alunos1.txt");
    readFileDisciplines(d2, "disciplinas2.txt");
    readFileStudent(s2, d2, "alunos2.txt");

    int choice, choiceCopy;
    do{
        system("cls");
        printLine();
        cout << "SISTEMA ACADEMICO" << endl;
        printLine();
        cout << "1.INSERIR DADOS" << endl;
        cout << "2.REMOVER DADOS" << endl;
        cout << "3.CONSULTAR DADOS" << endl;
        cout << "0.SAIR DO SISTEMA" << endl;
        printLine();
        cout << "Digite a sua escolha: ";
        cin >> choice;
        choiceCopy = choice;

        switch(choice){
            case 1: insertData(s1, s2, d1, d2); break;
            case 2: remove(s1, s2, d1, d2); break;
            case 3: consult(s1, s2, d1, d2); break;
            case 0: cout << "Ate a proxima vez" << endl; break;
            default: cout << "Opcao invalida, tente novamente" << endl; break;
        }

        while((choice = getchar()) != '\n' && choice != EOF);
        cout << "\n\n";
        cout << "Pressione ENTER para continuar..." << endl;
        getchar();
    }while(choiceCopy != 0);

    writeFileDisciplines(d1, "disciplinas1.txt");
    writeFileStudent(s1, "alunos1.txt");
    writeFileDisciplines(d2, "disciplinas2.txt");
    writeFileStudent(s2, "alunos2.txt");

    return 0;
}