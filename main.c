#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int checkFirstChar = 0;
int usedOption = 0;
int choosenOption = 0;
int lowerCaseCounter = 0;
int upperCaseCounter = 0;
int numberOfWordMatchesInFile = 0;
int programmResult = 0;

char *wordToFind;
char characterInFile;
char temp[512];

void printUsage(){
    printf("\nUsage: ./main.c {-h for help|-b|-s|-c word} filename\n");
}

int validateUserInput(int firstInputChar, int secondInputChar){
    if (firstInputChar == 45 && secondInputChar == 104){
        return secondInputChar;
    } else if (firstInputChar == 45 && secondInputChar == 98){
        return secondInputChar;
    } else if (firstInputChar == 45 && secondInputChar == 115){
        return secondInputChar;
    } else if (firstInputChar == 45 && secondInputChar == 99){
        return secondInputChar;
    } else {
        printUsage();
        exit(1);
    }
}
void printHelp(){
    printf("\n====================\t HELPPAGE \t==================\n");
    printUsage();
    printf("\nOPTIONS:\n");
    printf("\t-h\t\tdisplay this page.\n");
    printf("\t-b\t\tcount all upper cases in the choosen file.\n");
    printf("\t-s\t\tcount all lowercases in the choosen file. \n");
    printf("\t-c <word>\tcheck if word is in the file.\n");
    printf("\n====================\t HELPPAGE \t==================\n");
    exit(1);
}

int countUpperCases(FILE *file){
    int lowestUpperCase = 65;
    int biggestUpperCase = 90;
    while((characterInFile = getc(file)) != EOF ) {
        if (characterInFile >= lowestUpperCase && characterInFile <= biggestUpperCase){
            upperCaseCounter++;
        }
    }
    return upperCaseCounter;
}

int countLowerCases(FILE *file){
    int lowestLoewrCase = 97;
    int biggestLowerCase = 122;
    while((characterInFile = getc(file)) != EOF ) {
        if (characterInFile >= lowestLoewrCase && characterInFile <= biggestLowerCase){
            lowerCaseCounter++;
        }
    }
    return lowerCaseCounter;
}

int wordIsInFile(FILE *file, char *wordWhichIsToFind){
    while(fgets(temp, 512, file) != NULL) {
        if((strstr(temp, wordWhichIsToFind)) != NULL) {
            numberOfWordMatchesInFile++;
        }
    }
    return numberOfWordMatchesInFile;
}

int main(int argc, char *argv[]) {

    //check how many parametes are given and print help if to many
    if (argc > 1 && argc < 5){
        checkFirstChar = argv[1][0];
        usedOption = argv[1][1];
    }else{
        printUsage();
        exit(1);
    }

    //validate user input
    choosenOption = validateUserInput(checkFirstChar, usedOption);
    if (choosenOption == 104){
        printHelp();
    }



    char filename[512];
    strcpy(filename, argv[argc-1]);

    FILE *readFile = fopen(filename, "r");
    if (readFile == NULL){
        printf("Readable file not found!\n Correct path to file?? \n");
        exit(1);
    }

    FILE *writeFile = fopen("results.txt", "w");
    if (writeFile == NULL){
        printf("Writeable file not found!\n Correct path to file?? \n");
        exit(1);
    }

    //run chooses function
     if (choosenOption == 98){
        programmResult = countUpperCases(readFile);
        char result[] = "Es befinden sich folgende Anzahl an Grossbuchstaben in der Datei: ";
        fputs(result, writeFile);
        fprintf(writeFile, "%d", programmResult);
        printf("### write result to result.txt ###\n");
    } else if (choosenOption == 115){
        programmResult = countLowerCases(readFile);
        char result[] = "Es befinden sich folgende Anzahl an Kleinbuchstaben in der Datei: ";
        fputs(result, writeFile);
        fprintf(writeFile, "%d", programmResult);
        printf("### write result to result.txt ###\n");
    } else if (choosenOption == 99){
        if (argc > 2){
            wordToFind = argv[2];
        } else {
            printUsage();
            exit(1);
        }
        programmResult = wordIsInFile(readFile, wordToFind);
        if (programmResult > 0){
            char result[] = "Das Wort befindet sich folgende Anzahl in der Datei: ";
            fputs(result, writeFile);
            fprintf(writeFile, "%d", programmResult);
        } else{
            char result[] = "Das Wort befindet sich nicht in der Datei! ";
            fputs(result, writeFile);
        }
        printf("### write result to result.txt ###\n");
    }

    fclose(readFile);
    fclose(writeFile);
    return 0;
}