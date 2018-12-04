#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    
    //Checks if user passed two arguments
    if (argc != 3){
        printf("\nProgram must contain two arguments \n");
        printf("First is the text file to be encrypted \n");
        printf("Second is the shift amount \n\n");
        exit(EXIT_FAILURE);
    }

    int i, c;
    int shiftValue = atoi(argv[2]);
    int textParameterLength = strlen(argv[1]);
    char outputFile[textParameterLength + 5], charToWrite;

    //Saves the paramater text file into outputFile, adds .enc at the end of it
    strcpy(outputFile, argv[1]);
    outputFile[strlen(argv[1])] = '\0';
    strcat(outputFile, ".enc");


    // Checks if shift value is an integer between 1 and 25, inclusive
    if (shiftValue < 1 || shiftValue > 25){
        printf("\nThe shift value must be an integer between 1 and 25, inclusive \n\n");
        exit(EXIT_FAILURE);
    }
    
    // Checks if the second argument contains nondigits
    for (i = 0; i < strlen(argv[2]); i++){
        if (!isdigit(argv[2][i])){
            printf("\nSecond parameter cannot contain nondigits \n\n");
            exit(EXIT_FAILURE);
        }
    }

    // Traverses through the text file, builds the encryped message, writes to the output file character by character
    // Encryped file is created by adding the shift value to each character in input file using ASCII values
    // Opens the input and output files, prints an error message if the file does not exist in the current directory

    FILE *input, *output;
    input = fopen(argv[1], "r");
    output = fopen(outputFile, "w");

    if (input == 0){
        printf("\nSpecified text file does not exist in the current directory \n\n");
        exit(EXIT_FAILURE);

    }else{
        //traverses through all characters of the input file, assigns the character to variable c
        while ((c = getc(input)) != EOF){

            // if analyzed character is not a letter, it is maintained in the encryped file
            if (isalpha(c) == 0){
                charToWrite = c;
            // if analyzed character is an upper case and there is an overflow, wraparound
            }else if ((c <= 90) && (c + shiftValue > 90)){
                 charToWrite = c + shiftValue - 26;
            // if analyzed character is a lower case and there is an overflow, wraparound
            }else if ((97 <= c && c + shiftValue > 122)){
                 charToWrite = c + shiftValue - 26;
            // if character is a letter and no wraparound needed, add shift value to ASCII value of character
            }else{
                 charToWrite = c + shiftValue;
            }

            // writes the encrypted character into the output file
            fputc(charToWrite, output);

        }

        // closes the file streams
        fclose(input);
        fclose(output);
        
        //prints the completion message
        printf("\nFile has been encrypted and saved in %s\n", outputFile);
        printf("\n");

    }

    return 0;
}