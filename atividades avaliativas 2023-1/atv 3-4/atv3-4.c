//Salu Conteratto Ramos, RA 2150352

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
// #include <windows.h>
#include <ctype.h>

#define queueMaxSize 15

typedef struct client{
    char name[61];
    char birthday[11]; //dd/mm/aaaa
    char condition[2]; //N, D ou H
}client;

typedef struct node{
    client data;
    struct node* next;
    struct node* previous;
}node;

typedef struct sortedDoublyLinkedList{
    node* head;
    node* tail;
}sortedDoublyLinkedList;

//cria uma lista
sortedDoublyLinkedList* createSortedDoublyLinkedList() {
    sortedDoublyLinkedList* list = malloc(sizeof(sortedDoublyLinkedList));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

//adiciona elemento a lista
void addElementToList(sortedDoublyLinkedList* list, client value){
    node* newNode = malloc(sizeof(node));
    newNode->data = value;
    newNode->next = NULL;
    newNode->previous = NULL;
    if(list->head == NULL){
        // printf("primeiro elemento!\n");
        newNode->next = NULL;
        newNode->previous = NULL;
        list->head = newNode;
        list->tail = newNode;
    }else{ //insertion sort
        node* current = list->head;
        bool added = false; //controla se a posição foi encontrada ou não, se terminar o loop abaixo e não encontrar significa que a posição deve ser o final da lista
        bool isHead = true; //controla se a posição é a cabeça ou não
        while(current->next != NULL){
            //se for igual ou menor adiciona e encerra
            if(strcmp(value.name, current->data.name) <= 0){
                newNode->next = current;
                if(isHead == true){
                    // printf("head\n");
                    list->head = newNode;
                }else{
                    // printf("meio\n");
                    newNode->previous = current->previous;
                    current->previous->next = newNode;
                }
                current->previous = newNode;
                added = true;
                break;
            }
            isHead = false;
            current = current->next; //pula de elemento
        }
        if(added == false){
            // printf("tail!\n");
            newNode->previous = list->tail;
            list->tail->next = newNode;
            list->tail = newNode;
        }
    }
}

client* searchList(sortedDoublyLinkedList* list, char* name){
    node* current = list->head;
    while(current->next != NULL){
        if(strcmp(name, current->data.name) == 0){
            return &current->data;
        }
        current = current->next;
    }
    return NULL;
}

//imprime uma lista
void printList(sortedDoublyLinkedList* list){
    node* current = list->head;
    printf("----------------------\n");
    while(current != NULL){
        // printf("%s, %s, %s (next: %s, previous: %s, head: %s, tail: %s)\n", current->data.name, current->data.birthday, current->data.condition, current->next->data.name, current->previous->data.name, list->head->data.name, list->tail->data.name);
        printf("%s, %s, %s\n", current->data.name, current->data.birthday, current->data.condition);
        current = current->next;
    }
    printf("----------------------\n");
}

//abstração para ler próxima linha de um arquivo
char* readFileLine(FILE *f, int lineMaxSize){
    char ch;
    char *line = (char *) malloc(sizeof(char)*lineMaxSize);
    for(int i = 0; i < lineMaxSize; i++){
        ch = fgetc(f);
        if(ch == '\n' || ch == EOF){
            line[i] = '\0';
            break;
        }else if(ch != '\n'){
            line[i] = ch;
        }
    }
    return line;
}

void stringToUpper(char* str) {
    while(*str){
        *str = toupper(*str);
        str++;
    }
}








client createClient(char* name, char* birthday, char* condition){
    client data;
    strcpy(data.name, name);
    strcpy(data.birthday, birthday);
    strcpy(data.condition, condition);
    return data;
}

void readRegister(sortedDoublyLinkedList* list){
    FILE *registersFile;
    registersFile = fopen("clientes.csv", "r");
    char name[61];
    char birthday[11];
    char condition[2];
    while(1){
        char *nextLine = readFileLine(registersFile, 72);
        if(strcmp(nextLine, "") == 0){//verifica se a linha é vazia
            break;
        }
        sscanf(nextLine, "%60[^,],%10[^,],%1[^,]", name, birthday, condition);
        addElementToList(list, createClient(name, birthday, condition));
        //printf("adicionando nome %s\n", name);
    }
    //printList(list);
}

void createRegister(){

}

void searchRegister(){

}

void updateRegister(){

}

void saveRegister(){

}


int main(){

    sortedDoublyLinkedList* registers = createSortedDoublyLinkedList();
    readRegister(registers);

    printf("(1) Realizar novo cadastro\n");
    printf("(2) Buscar cadastro\n");
    printf("(3) Alterar dados do cadastro\n");
    printf("(4) Montar fila de espera\n"); //realizar a leitura de DadosChegada.txt, verificar quais clientes ir˜ao para fila de espera, quais entrarão imediatamente no restaurante e quais não serão servidos
    printf("(5) Proximo a ir ao buffet\n"); //tirar uma pessoa da fila de espera e colocá-la na fila do buffet correspondente à sua condição de saúde (se houver espaço no restaurante)
    printf("(6) Sair do restaurante\n"); //quando um cliente deixa o restaurante, avisar qual cliente está saindo e atualizar a fila repectiva
    printf("(7) Imprimir fila D\n");
    printf("(8) Imprimir fila H\n");
    printf("(9) Imprimir fila N\n");
    printf("(10) Imprimir fila de espera\n");
    printf("(11) Imprimir todas as filas\n");
    printf("(12) Imprimir lista de cadastro\n");
    printf("(13) Sair\n\n");

    client* result;
    int selectedOption = 0;
    char name[61] = "";
    char birthday[11] = "";
    char condition[2] = "";
    int day = 0;
    int month = 0;
    int year = 0;
    while(1){
        printf("Digite uma opcao: ");
        scanf("%d", &selectedOption);
        getchar(); //consumir o caractere de nova linha pendente no buffer
        printf("\n");
        switch(selectedOption){
            case 1:
                printf("Digite o nome completo: ");
                fgets(name, 61, stdin);
                name[strcspn(name, "\n")] = '\0'; //Remove o \n da string
                stringToUpper(name);
                printf("Digite a data de nascimento: ");
                fgets(birthday, 11, stdin);
                birthday[strcspn(birthday, "\n")] = '\0'; //Remove o \n da string
                getchar(); //consumir o caractere de nova linha pendente no buffer
                printf("Digite a condicao de saude: ");
                fgets(condition, 2, stdin);
                condition[strcspn(condition, "\n")] = '\0'; //Remove o \n da string
                stringToUpper(condition);
                //etapa de verificação
                sscanf(birthday, "%d/%d/%d", &day, &month, &year);
                if(day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 2023){
                    printf("data de aniversario invalida!\n");
                }else if(strcmp(condition, "H") != 0 && strcmp(condition, "D") != 0 && strcmp(condition, "N") != 0){
                    printf("condicao de saude invalida!\n");
                }else{
                    addElementToList(registers, createClient(name, birthday, condition));
                    printf("cadastro realizado com sucesso!\n");
                }
                break;
            case 2:
                printf("Digite o nome completo: ");
                fgets(name, 61, stdin);
                name[strcspn(name, "\n")] = '\0'; //Remove o \n da string
                stringToUpper(name);
                printf("Estamos verificando nosso sistema...\n");
                result = searchList(registers, name);
                if(result == NULL){
                    printf("Cadastro nao encontrado!\n");
                }else{
                    printf("Cadastro encontrado!\n");
                    printf("--------------------------\n");
                    printf("Nome: %s\n", result->name);
                    printf("Data de nascimento: %s\n", result->birthday);
                    printf("Condicao de saude: %s\n", result->condition);
                }
                break;
            case 3:
                printf("Digite o nome completo: ");
                fgets(name, 61, stdin);
                name[strcspn(name, "\n")] = '\0'; //Remove o \n da string
                stringToUpper(name);
                printf("Estamos verificando nosso sistema...\n");
                result = searchList(registers, name);
                if(result == NULL){
                    printf("Cadastro nao encontrado!\n");
                }else{
                    printf("Cadastro encontrado!\n");
                    printf("--------------------------\n");
                    printf("(1) Nome\n");
                    printf("(2) Data de nascimento\n");
                    printf("(3) Condicao de saude\n");
                    printf("Oque deseja alterar? ");
                    scanf("%d", &selectedOption);
                    getchar(); //consumir o caractere de nova linha pendente no buffer
                    switch (selectedOption){
                        case 1:
                            printf("Digite novo nome: ");
                            fgets(name, 61, stdin);
                            name[strcspn(name, "\n")] = '\0'; //Remove o \n da string
                            stringToUpper(name);
                            strcpy(result->name, name);
                            printf("Cadastro atualizado com sucesso!\n");
                            break;
                        case 2:
                            printf("Digite nova data de nascimento: ");
                            fgets(birthday, 11, stdin);
                            birthday[strcspn(birthday, "\n")] = '\0'; //Remove o \n da string
                            sscanf(birthday, "%d/%d/%d", &day, &month, &year);
                            if(day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 2023){
                                printf("data de aniversario invalida!\n");
                            }else{
                                strcpy(result->birthday, birthday);
                                printf("Cadastro atualizado com sucesso!\n");
                            }
                            break;
                        case 3:
                            printf("Digite nova condicao de saude: ");
                            fgets(condition, 2, stdin);
                            condition[strcspn(condition, "\n")] = '\0'; //Remove o \n da string
                            stringToUpper(condition);
                            if(strcmp(condition, "H") != 0 && strcmp(condition, "D") != 0 && strcmp(condition, "N") != 0){
                                printf("condicao de saude invalida!\n");
                            }else{
                                strcpy(result->condition, condition);
                                printf("Cadastro atualizado com sucesso!\n");
                            }
                            break;
                        default:
                            printf("Opcao invalida!\n");
                            break;
                    }
                }
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                break;
            case 10:
                break;
            case 11:
                break;
            case 12:
                printList(registers);
                break;
            case 13:
                free(registers);
                return 0;
                break;
            default:
                printf("comando inválido\n");
                break;
        }
        printf("\n");
    }
}