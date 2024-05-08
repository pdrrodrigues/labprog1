#include <stdlib.h>
#include <stdio.h>

#define MAX_DISCIPLINES 5
#define STUDENT_CODE_LEN 5
#define DISCIPLINE_CODE_LEN 4

// Struct que representa os alunos com os seus dados e as diciplinas inscritas
typedef struct Student{
    char numberCode[STUDENT_CODE_LEN];
    char name[20];
    char cpf[11];
    char disciplines[MAX_DISCIPLINES * (DISCIPLINE_CODE_LEN + 1)];
    struct Student *next;
} Student;

// Struct que representa
typedef struct Discipline{
    char numberCode[DISCIPLINE_CODE_LEN];
    char name[30];
    char professor[20];
    char credits[2];
    struct Discipline *next;
} Discipline;

void printLine(){
    for(int i = 0; i < 50; i++){
        printf("-");
    }
    printf("\n");
}

void insertStudent(Student *h){
    char numCd[STUDENT_CODE_LEN];
    char nm[20];
    char cpf[11];
    char disciplines[MAX_DISCIPLINES * (DISCIPLINE_CODE_LEN + 1)] = {'\n'};

    printf("Insira o codigo do aluno: ");
    scanf("%s", numCd);
    printf("Insira o nome do aluno(ate 20 caracteres): ");
    scanf("%s", nm);
    printf("Insira o cpf do aluno: ");
    scanf("%s", cpf);

    int count = 0;
    while(count < 5){
        printf("Insira ate cinco disciplinas ou digite s para sair: ");
        char tempDis[DISCIPLINE_CODE_LEN + 1];
        scanf("%4s", tempDis);
        if (strcmp(tempDis, "s") == 0) {
            break;
        }
        strcat(disciplines, tempDis);
        strcat(disciplines, ";");
        count++;
    }

    Student *temp = (Student*) malloc(sizeof(Student));
    strcpy(temp->numberCode, numCd);
    strcpy(temp->name, nm);
    strcpy(temp->cpf, cpf);
    strcpy(temp->disciplines, disciplines);
    temp->next = h;
    h = temp;
}

void insertDiscipline(Discipline *h){
    char numberCode[DISCIPLINE_CODE_LEN];
    char name[30];
    char professor[20];
    char credits[2];

    printf("Insira o codigo da disciplina: ");
    scanf("%s", numberCode);
    printf("Insira o nome da disciplina(ate 30 caracteres): ");
    scanf("%s", name);
    printf("Insira o nome do professor(ate 20 caracteres): ");
    scanf("%s", professor);
    printf("Insira a quantidade de creditos(ate 2 digitos): ");
    scanf("%s", credits);
    
    Discipline *temp = (Discipline*) malloc(sizeof(Discipline));
    strcpy(temp->numberCode, numberCode);
    strcpy(temp->name, name);
    strcpy(temp->professor, professor);
    strcpy(temp->credits, credits);
    temp->next = h;
    h = temp; 
}

void insertData2(Student *h, Discipline *d){
    int choice2;
    do{
        printLine();
        printf("ESCOLHA A OPCAO\n");
        printLine();
        printf("1.ALUNO\n");
        printf("2.DISCIPLINA\n");
        printLine();
        printf("Digite a sua escolha: ");
        scanf("%d", &choice2);

        switch(choice2){
                case 1: insertStudent(h); break;
                case 2: insertDiscipline(d); break;
                default: break;
        }
    }while(choice2 != 1 && choice2 != 2);
}

void insertData(Student *h1, Student *h2, Discipline *d1, Discipline *d2){
    int choice1;
    do{
        printLine();
        printf("ESCOLHA O PERIODO\n");
        printLine();
        printf("1.PRIMEIRO PERIODO\n");
        printf("2.SEGUNDO PERIODO\n");
        printLine();
        printf("Digite a sua escolha: ");
        scanf("%d", &choice1);

        switch(choice1){
                case 1: insertData2(h1, d1); break;
                case 2: insertData2(h2, d2); break;
                default: break;
        }
    }while(choice1 != 1 && choice1 != 2);
}

Student* searchStudent(Student *h, char *s){
    printf("hi");
    while(h != NULL){
        if(!strcmp(h->numberCode, s)){
            printf("bye"); 
            return h;
        }
        h = h->next;
    }

    return NULL;
}

Discipline* searchDiscipline(Discipline *d, char *s){
    while(d != NULL){
        if(strcmp(d->numberCode, s)){ 
            return d;
        }
        d = d->next;
    }

    return NULL;
}

void consultStudent(Student *h){
    char nc[STUDENT_CODE_LEN];
    printf("Insira o codigo do aluno que deseja procurar: \n");
    scanf("%s", nc);
    Student *find = searchStudent(h, nc);
    if(find == NULL){
        printf("Aluno nao encontrado");
    }else{
        printf("Nome do Aluno: ");
        printf("%s\n", find->name);
        printf("Codigo do Aluno: ");
        printf("%s\n", find->numberCode);
        printf("CPF do Aluno: ");
        printf("%s\n", find->cpf); 
        printf("Disciplinas do Aluno: \n");
        char *token = strtok(find->disciplines, ";");
        while(token != NULL){
            printf("%s\n", token);
            token = strtok(NULL, ";");
        }
    }
}

void consult2(Student *h, Discipline *d){
    int choice2;
    do{
        printLine();
        printf("ESCOLHA UMA OPCAO\n");
        printLine();
        printf("1.ALUNO\n");
        printf("2.DISCIPLINA\n");
        printLine();
        printf("Digite a sua escolha: ");
        scanf("%d", &choice2);

        switch(choice2){
                case 1: consultStudent(h); break;
                case 2: ; break;
                default: break;
        }
    }while(choice2 != 1 && choice2 != 2);
}

void consult(Student *h1, Student *h2, Discipline *d1, Discipline *d2){
    int choice1;
    do{
        printLine();
        printf("ESCOLHA O PERIODO\n");
        printLine();
        printf("1.PRIMEIRO PERIODO\n");
        printf("2.SEGUNDO PERIODO\n");
        printLine();
        printf("Digite a sua escolha: ");
        scanf("%d", &choice1);

        switch(choice1){
                case 1: consult2(h1, d1); break;
                case 2: consult2(h2, d2); break;
                default: break;
        }
    }while(choice1 != 1 && choice1 != 2);
}

void readStudent(Student *h){
    FILE *fp = fopen("student.txt", "r");

    fclose(fp);
};

void readDiscipline(Discipline *h){

};

int main(){
    Student *h1 = NULL, *h2 = NULL;
    Discipline *d1 = NULL, *d2 = NULL;
    int choice, choiceCopy;
    do{
        system("cls");
        printLine();
        printf("SISTEMA ACADEMICO\n");
        printLine();
        printf("1.INSERIR DADOS\n");
        printf("2.REMOVER DADOS\n");
        printf("3.CONSULTAR DADOS\n");
        printf("0.SAIR DO SISTEMA\n");
        printLine();
        printf("Digite a sua escolha: ");
        scanf("%d", &choice);
        choiceCopy = choice;

        switch(choice){
            case 1: insertData(h1, h2, d1, d2); break;
            case 2: break;
            case 3: consult(h1, h2, d1, d2); break;
            case 0: printf("Ate a proxima vez\n"); break;
            default: printf("Opcao invalida, tente novamente\n"); break;
        }

        while((choice = getchar()) != '\n' && choice != EOF);
        printf("\n\n");
        printf("Pressione ENTER para continuar...\n");
        getchar();
    }while(choiceCopy != 0);

    return 0;
}