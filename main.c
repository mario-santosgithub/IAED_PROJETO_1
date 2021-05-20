/* Projeto IAED */
/* Mario Santos - 99275 */
 
 
/* Biblioteca */
#include <stdio.h>
#include <string.h>
 
 
/* Constantes */
#define ACT 10 /* Capacidade maxima de atividades */
#define MAXT 10000 /* Capacidade maxima de tarefas */
#define DEF 6 /* As 6 caracteristicas da tarefa, ID, utilizador...*/
#define DESCMAX 50 /* Tamanho maximo da descricao */
#define MAXUSERS 50 /* Numero maximo de utilizadores */
#define MAXUSER 20 /* Numero maximo de caracteres de um utilizador */
#define MAXACT 20 /* Numero maximo de caracteres de uma atividade */
#define MAXVETOR 1000 /* Numero maximo de caracteres do input */
 
#define INVDUR_STR "invalid duration"
#define TASK_STR "task"
#define TODO_STR "TO DO"
#define INPROGRESS_STR "IN PROGRESS"
#define DONE_STR "DONE"
#define INVTIME_STR "invalid time"
#define DUPDESC_STR "duplicate description"
#define TOOMANY_STR "too many tasks"
#define USERAE_STR "user already exists"
#define TOOMANYU_STR "too many users"
#define NOSTASK_STR "no such task"
#define NOSUSER_STR "no such user"
#define TASKAS_STR "task already started"
#define NSACT_STR "no such activity"
#define DUPACT_STR "duplicate activity"
#define INVDESC_STR "invalid description"
#define TOOMANYA_STR "too many activities"
 
/* Estruturas de Dados */
 
typedef struct {    
    int id;
    char desc[DESCMAX];
    char user[MAXUSER];
    char act[MAXACT];
    int temp;
    int start;
} tarefa;
 
tarefa global[MAXT]; /* vetor que armazena todas as tarefas */
char atividades[ACT][MAXACT]; /* vetor que armazena as atividades */
char utilizadores[MAXUSERS][MAXUSER]; /* vetor que armazena os utilizadores */
int tarefas; /* numero total de tarefas */
int acts; /* numero total de atividades */
int users; /* numero total de utilizadores */
 
 
/* Prototipos */
 
void inicia_act();
void add_tarefa(int duracao, char desc[DESCMAX]);
void lista_todas_tarefas();
void lista_arg_tarefas();
void add_user();
void lista_users();
void lista_tarefas();
void act();
void total_tarefas();
char obter_user(char newuser[MAXUSER]);
int tempo(int temp);
void move_tarefa();
void altera_atividade(char act[MAXACT], int task, int temp);
void lista_act();
void add_act();
 
/* Codigo */
 
int main() {
 
    char opcao, desc[DESCMAX], input[MAXVETOR];
    int duracao, temp = 0;
 
    inicia_act();

    do {
        opcao = getchar();

        if (opcao == 't') {
            scanf("%d %[^\n]s", &duracao, desc);
            add_tarefa(duracao, desc);
        }
        if (opcao == 'l') {
            input[1] = getchar();
            if (input[1] == ' ') {
                lista_arg_tarefas();
            }
            else {
            lista_todas_tarefas();
            }
        }
        if (opcao == 'n') {
            temp = tempo(temp);
        }
        if (opcao == 'u') {
            input[1] = getchar();
            if (input[1] == ' ') {
                add_user();
            }
            else {
                lista_users();
            } 
        }
        if (opcao == 'm') {
            move_tarefa(temp);
        }
        if (opcao == 'd') {
            lista_tarefas();
        }
        if (opcao == 'a') {
            input[1] = getchar();
            if (input[1] == ' ') {
                add_act();
            }
            else {
                lista_act();;
            }
        }

    } while (opcao != 'q'); 
    
    return 0;
}
 
void inicia_act() {
    /* acts = 0 */
    strcpy(atividades[0], TODO_STR);
    acts++;
    strcpy(atividades[1], INPROGRESS_STR);
    acts++;
    strcpy(atividades[2], DONE_STR);
    acts++;
}
 
int tempo(int temp) {
 
    int duracao;
 
    scanf("%d", &duracao);
 
    if (duracao >= 0) {
 
        temp += duracao;
        printf("%d\n", temp);
        
    }
    else {
        printf("%s\n", INVTIME_STR);
    }
 
    return temp;
}
  
void add_tarefa(int duracao, char desc[DESCMAX]) {
 
    int i, teste = 1; /* Se testar = 0, a funcao para */

    if (tarefas < MAXT) {
        for(i = 0; i < tarefas; i++) {
                    
            if (strcmp(global[i].desc, desc) == 0) {
        
                teste = 0;
                printf("%s\n", DUPDESC_STR);
            }
        }
        if (teste == 1) {
            if (duracao > 0) {
                global[tarefas].temp = duracao;
                strcpy(global[tarefas].desc, desc);
                global[tarefas].id = tarefas+1;
                strcpy(global[tarefas].act, TODO_STR);
                printf("%s %d\n", TASK_STR, global[tarefas].id);
                tarefas++;
                }
            else {
                printf("%s\n", INVDUR_STR);
            }
        }
    }
    else {
        printf("%s\n", TOOMANY_STR);
    }
}

void lista_todas_tarefas() {

    int i;

    for (i = 0; i < tarefas; i++) {
        printf("%d %s #%d %s\n", global[i].id, global[i].act,
        global[i].temp, global[i].desc);
    }
}

void lista_arg_tarefas() {

    int save, j, i = 0, teste; /* Se teste = 1, entao existe tarefa com o id */
    int input[MAXVETOR];
    char c;

    scanf("%d", &input[i]);
    i++;
    while ((c = getchar()) != '\n') {
        if (c == ' ') {
            scanf("%d", &input[i]);
            i++;
        }
    }
    i--;
    save = i;
    i = 0;
    while (i <= save) {
        teste = 0;
        for(j = 0; j < tarefas; j++) {
            if (global[j].id == input[i]) {
                teste = 1;
                printf("%d %s #%d %s\n", global[i].id, global[i].act,
                 global[i].temp, global[i].desc);
            }
        }
        if (teste == 0) {
            printf("%d: %s\n", input[i], NOSTASK_STR);
        }
        i++;
    }
}

void add_user() {
    
    int i, new = 1; /* se o utilizador for novo new = 1 */
    char newuser[MAXUSER];
 
    scanf("%s", newuser);
 
    if (users < MAXUSERS){
 
        for(i = 0; i < users; i++) {
 
            if (strcmp(utilizadores[i], newuser) == 0) {
                new = 0;
            }
        }
        if (new == 1) {
            strcpy(utilizadores[users], newuser);
            users++;
        }
        else {
            printf("%s\n", USERAE_STR);
        }
    }
    else {
        printf("%s\n", TOOMANYU_STR);
    }
}
 
void lista_users() {
    
    int i;
    
    for (i = 0; i < users; i++) {
        printf("%s\n", utilizadores[i]);
    } 
}

void move_tarefa(int temp) {
 
    int task=0, id, i, existe1 = 0; /* Se a tarefa existir, existe1 = 1*/
    int existe2 = 0;              /* Se o utilizador existir, existe2 =1*/
    char user[MAXUSER], act[MAXACT];          
 
    scanf("%d %s %[^\n]s", &id, user, act);
    for(i = 0; i < tarefas; i++) {
        if (global[i].id == id) {
            task = i;
            existe1 = 1;
        }
    }
    if (existe1 == 0) {
        printf("%s\n", NOSTASK_STR);
        return;
    }
    for(i = 0; i < users; ++i) {
        if (strcmp(utilizadores[i], user) == 0) {
            existe2 = 1;
        }
    }
    if (existe2 == 0) {
        printf("%s\n", NOSUSER_STR);
        return;
    }
    if ((existe1 == 1) && (existe2 == 1)) {
        if ((strcmp(global[task].act, TODO_STR) != 0)
         && (strcmp(act, TODO_STR) == 0)) {
                printf("%s\n", TASKAS_STR);
            }
        else {
            strcpy(global[task].user, user);
            altera_atividade(act, task, temp);   
        }    
    }
}
 
void altera_atividade(char act[MAXACT], int task, int temp) {

    int gasto, slack, existeA=0; /* Se a atividade existir, existeA = 1 */
    int i;
    for(i = 0; i < acts; i++) {
        if (strcmp(atividades[i], act) == 0) {
            existeA = 1;
        }
    }
    if (existeA == 1) {    
        if (strcmp(global[task].act, TODO_STR) == 0) {
            strcpy(global[task].act, act);
            global[task].start = temp;
        }
        else if ((strcmp(act, DONE_STR) == 0)) {
            strcpy(global[task].act, act);
            gasto = temp - global[task].start;
            slack = gasto - global[task].temp;
            printf("duration=%d slack=%d\n", gasto, slack);
        }
        else {
            strcpy(global[task].act, act);    
        }
    }
    else {
        printf("%s\n", NSACT_STR);
    }
}

void lista_tarefas() {

    int i, existe = 0;
    char act[MAXACT], atividade[MAXACT];

    scanf("%[^\n]s", atividade);
    for(i = 0; i < MAXACT; i++) {
        act[i] = atividade[i+1];
    }
    for (i = 0; i < acts; i++) {
        if (strcmp(atividades[i], act) == 0) {
            existe = 1;
        }
    }
    if (existe == 1) {
        for (i = 0; i < tarefas; i++) {
            if (strcmp(global[i].act, act) == 0) {
                printf("%d %d %s\n", global[i].id, global[i].start,
                 global[i].desc);
            }
        }
    }
    else {
        printf("%s\n", NSACT_STR);
    }
}

void lista_act() {

    int i;

    for (i = 0; i < acts; i++) {
            printf("%s\n", atividades[i]);
        }
}

void add_act() {

    int i, existe1 = 0; /* Se existe1 = 1, a atividade e nova */
    int existe2 = 1; /* Se existe2 = 1, a atividade so letras maiusculas */
    char newact[MAXACT];

    scanf("%[^\n]s", newact);
    for (i = 0; i < acts; i++) {
        if (strcmp(atividades[i], newact) != 0) {
            existe1 = 1;
        }
    }
    for (i = 0; i < MAXACT-2; i++) { /* confirma se nao ha minusculas */
        if ((newact[i] >= 'a') && (newact[i] <= 'z')) {
            existe2 = 0;
        }
    }   
    if (acts == ACT) {
        printf("%s\n", TOOMANYA_STR);
    }
    if (existe1 == 0) {
        printf("%s\n", DUPACT_STR);
    }
    if (existe2 == 0) {
        printf("%s\n", INVDESC_STR);
    }
    if ((existe1 == 1) && (existe2 == 1) && (acts < ACT)) {
        strcpy(atividades[acts], newact);
        acts++;
    }
}
