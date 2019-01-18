#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

int indexx = 0;
char *all_questions[245];
char *all_answers[245];
char *answer;
char *question;
char *potential_answer;


int main()
{
    char *password;
    printf("_________ _________                                                     .___\n");
    printf("\\_   ___ \\\\_   ___ \\_______  ____  ______ ________  _  _____________  __| _/\n");
    printf("/    \\  \\//    \\  \\/\\_  __ \\/  _ \\/  ___//  ___/\\ \\/ \\/ /  _ \\_  __ \\/ __ | \n");
    printf("\\     \\___\\     \\____|  | \\(  <_> )___ \\ \\___ \\  \\     (  <_> )  | \\/ /_/ | \n");
    printf(" \\________/\\________/|__|   \\____/______>______>  \\/\\_/ \\____/|__|  \\_____| \n\n");

    printf("Witaj w generatorze krzyzowek w jezyku C\n");
    printf("Hasla i pytania sa w jezyku angielskim\n");
    printf("Autor: Mikolaj Dakowicz\n");

    printf("podaj haslo skladajace sie z samych wielkich liter i bez polskich znakow: \n");
    char a[2];
    gets(a);
    password = a;
    printf("czy chcesz wyswietlic tez odpowiedzi pod pytaniami?(tak/nie)");
    char do_answers[10];
    gets(do_answers);
    int password_len = strlen(password);
    char *crossword[strlen(password)];
    char *questions[strlen(password)];
    srand(time(0));
    //otwarcie pliku z has³ami i pytaniami
    FILE *myfile = fopen("D:\\CCrossword\\sample.txt", "r");
    if (myfile == NULL){
        printf("Blad przy otwieraniu pliku!\n");
        exit(1);
    }

    // stworzenie dwóch tablic: pytania i odpowiedzi
    char line[256];
    while (fgets(line, sizeof(line), myfile)){
        answer = strtok(line, "|");
        question = strtok(NULL, "");
        all_questions[indexx] = strdup(question);
        all_answers[indexx] = strdup(answer);
        //printf("%s\n", all_questions[indexx]);
        indexx++;
    };

    //pêtla która przechodzi po ka¿dej literze g³ównego has³a
    int size_of_all_answears = sizeof(all_answers)/sizeof(all_answers[0]);
    for(int character=0; character<(strlen(password)+1); character++){

        //pêtla szukania has³a a¿ znajdzie takie które zawiera literê z g³ównego has³a
        while(true)
        {
            int r = rand()%(size_of_all_answears-1);

            potential_answer = all_answers[r];
            char *tmp_potential_answer = potential_answer;
            char password_character = password[character];
            char *position = strchr(tmp_potential_answer, password_character);
            if ( (position != NULL) && (potential_answer[0] != password_character))
            {
                crossword[character] = tmp_potential_answer;
                questions[character] = all_questions[r];
                break;
            }
        }
    }
    //tworzenie krzyzowki graficznej
    int width = 0;
    for(int character=0; character<(strlen(password)); character++){
        int current_answer_lenght = strlen(crossword[character]);
        if (current_answer_lenght > width){
            width = current_answer_lenght;
        }
    }
    int max_width = width*2;
    printf("..............................................................................................\n");
    for(int character=0; character<(strlen(password)); character++){
        char *password_character = password[character];
        char *tmp_answer = strdup(crossword[character]);
        char *tmp_answer_left = strtok(tmp_answer, &password_character);
        char *tmp_answer_right = strtok(NULL, "");
        if(tmp_answer_right == NULL){
            tmp_answer_right = "";
        }
        printf("%d", character+1);
        for(int i=0; i<(width-strlen(tmp_answer_left)-2); i++){
            printf("   ");
        }

        for(int i=0; i<strlen(tmp_answer_left); i++){
            printf("[_]");
        }
        //print miejsca litery glownego hasla
        printf("[x]");
        for(int i=0; i<strlen(tmp_answer_right); i++){
            printf("[_]");
        }
        for(int i=0; i<(width-strlen(tmp_answer_right)-1); i++){
            printf("   ");
        }
        printf("\n");
    }

    printf("..............................................................................................\n");
    printf("pytania:\n");
    for(int a = 0; a < password_len; a++){
        printf("%d: %s", a+1, questions[a]);
    }

    if(strcmp(do_answers, "tak") == 0){
        printf("odpowiedzi:\n");
        for(int a = 0; a < password_len; a++){
            printf("%d: %s\n", a+1, crossword[a]);
        }
    }
    system("pause");
    return 0;
}
