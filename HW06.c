//
// Name: Bren Garcia Marti
// Compiler: Xcode
// Course: CS 2060_001
// Assignment: HW06 Mad Libs
// Date: 4/3/2022
// Problem Statement: Write a program that uses random-number generation and user input to create sentences. The user will enter the noun but the other words will be generated randomly from words in a file.
//
#include <stdio.h>
#include <stdlib.h> // include rand() input and output char and string see slide 6 of Lect
#include <string.h> // include strcmp()
#include <stdbool.h> // include boolean variables
#include <ctype.h> // include toupper
#include <time.h> // to see the function randomly

//Madlib Values
#define STRING_LENGTH 100
#define NUMBER_SENTENCES 5
#define NUMBER_WORDS 5
#define WORD_LENGTH 20
#define NOUN "noun"
#define ADJECTIVE "adjective"
#define PATH_SIZE 80 // see L19 CH11 , slide 26

//file names and path
const char * MADLIB_FILE = "madlib.txt";
const char* PREPOSITION_FILE = "prepositions.txt";
const char* ARTICLE_FILE = "articles.txt";
const char* VERB_FILE = "verbs.txt";
const char * DIRECTORY_PATH = "/Users/bdenny/Documents/";

// ~~~ // USER FUNCTION PROTOTYPES // ~~~ //

    // Create a function as defined below to get the file path for each file.Use strcpy and string strcat functions.
    void getFilePath(char* finalPath, const char* directoryPath, const char* fileName);

    // Create a function as defined below that will open the file to read the words as a string then get each word and put it into the word type array (article, verb, preposition). The function will return whether the file was opened successfully. Use strcpy and strtok.
    bool getWordsFromFile(const char* path, char words[][WORD_LENGTH], int numberWords);

    // The user should enter 5 nouns and 5 adjectives. Create one function to be called for each type of word. Be careful of what characters are put into the array for each word entered by the user.
    void getUserWords(char word[][WORD_LENGTH], const char* wordType, int numberWords);

    // Create a function to make a sentence and write it to a file. Each word will be selected at random from each array in the following order: article, adjective, noun, verb, preposition, article, adjective and noun. Use sprintf to create the sentence. The final sentence should start with a capital letter and end with a period and each sentence should be written to a file.
    bool writeSentenceToFile(const char* path, const char article[][WORD_LENGTH],
        const char verb[][WORD_LENGTH],
        const char preposition[][WORD_LENGTH],
        const char noun[][WORD_LENGTH],
        const char adjective[][WORD_LENGTH],
        int numberWords,  int numberSentences);

// ~~~ // MAIN // ~~~ //

int main(void)
{
    bool retrievedWords = false;
    bool madLibCreation = false;
    char noun[NUMBER_WORDS][WORD_LENGTH];
    char adjective[NUMBER_WORDS][WORD_LENGTH];
    char preposition[NUMBER_WORDS][WORD_LENGTH];
    char articles[NUMBER_WORDS][WORD_LENGTH];
    char verbs[NUMBER_WORDS][WORD_LENGTH];
    
    // lengthArray replacement arrays to store the "finalPath" in getFilePath function
    char verb_filePath[PATH_SIZE] = { '\0' };
    char madLib_filePath[PATH_SIZE] = { '\0' };
    char articles_filePath[PATH_SIZE]= { '\0' };
    char preposition_filePath[PATH_SIZE]= { '\0' };
    
    
    getFilePath(verb_filePath, DIRECTORY_PATH, VERB_FILE);
    getFilePath(madLib_filePath, DIRECTORY_PATH, MADLIB_FILE);
    getFilePath(articles_filePath, DIRECTORY_PATH, ARTICLE_FILE);
    getFilePath(preposition_filePath, DIRECTORY_PATH, PREPOSITION_FILE);
           
    // we need the articles, prepositions, and verbs from files
   retrievedWords = getWordsFromFile(preposition_filePath, preposition, NUMBER_WORDS);
        if (retrievedWords == false)
        {
            printf("%s", "File could not be opened.\n");
        }
    retrievedWords = getWordsFromFile(articles_filePath, articles, NUMBER_WORDS);
    if (retrievedWords == false)
        {
            printf("%s", "File could not be opened.\n");
        }
    retrievedWords = getWordsFromFile(verb_filePath, verbs, NUMBER_WORDS);
    if (retrievedWords == false)
        {
            printf("%s", "File could not be opened.\n");
        }
    
    
    // we need the nouns and the adjectives from the user
    getUserWords(noun, NOUN, NUMBER_WORDS);
    getUserWords(adjective, ADJECTIVE, NUMBER_WORDS);
    
    madLibCreation = writeSentenceToFile(madLib_filePath, articles, verbs, preposition, noun, adjective, NUMBER_WORDS,  NUMBER_SENTENCES);
    if (madLibCreation == false)
        {
            printf("%s", "The madlib was not created to mad scientists standards.\n");
        }
    
    return 0;
} // end main


// 111 // USER FUNCTION: getUserWords // 111 //
// The user should enter 5 nouns and 5 adjectives. Create one function to be called for each type of word. Be careful of what characters are put into the array for each word entered by the user.
void getUserWords(char word[][WORD_LENGTH], const char* wordType, int numberWords)
{
    
    for (size_t i = 0; i < numberWords ; i++)
    {
    printf("Enter %lu %s, enter between each %s: ", (numberWords - i), wordType, wordType); //message to user
        fgets(word[i], WORD_LENGTH, stdin);
        // strip off the \n characters
        word[i][strcspn(word[i], "\n")] = '\0'; //sets the first newline in the string to a null character, removing it
            
        //clear the buffer for fgets
            if (strchr(word[i], '\n') == NULL)
            {
                while ((getchar()) != '\n');
            }
    }
    
    //TESTING double check the array
    //for (size_t i = 0; i < numberWords ; i++)
    //{
    //printf("The words are: %s\n", word[i]);
    //}
    
    return; // end of getUserWords
}

// 222 // USER FUNCTION: getWordsFromFile // 222 //
// Create a function as defined below that will open the file to read the words as a string then get each word and put it into the word type array (article, verb, preposition). The function will return whether the file was opened successfully. Use strcpy and strtok.
bool getWordsFromFile(const char* path, char words[][WORD_LENGTH], int numberWords)
{
    bool functioningFile = false;
    char lineFile[STRING_LENGTH]; // temporarily array to hold the whole line from the file
    const char s[2] = " "; //the token is a space
    char *token; //pointer to token
    int counter = 0;
    // size_t i = 0; //for TESTING the words array AFTER fgets
    
    FILE *inPtr; //datastream to open
    inPtr = fopen( path, "r"); //r for read
    if (inPtr == NULL)
    {
        // printf("%s", "File could not be opened.\n");
        functioningFile = false;
    }
    else
    {
        while (!feof(inPtr)) //while not the end of a file
        {
            fgets(lineFile, STRING_LENGTH, inPtr); //read the file line
            token = strtok(lineFile, s); //get the first token
            
              while( token != NULL && counter < numberWords)
              {
                  functioningFile = true;
                  // printf( " %s\n", token ); //TEST THE TOKEN
                  strcpy(words[counter], token); //copy the token to an array the main array can use
                  counter++; //increment the word array
                  token = strtok(NULL, s); //get the next token
              }
         }
    }
    //TESTING double check the array
    //for (i = 0; i < numberWords ; i++)
    //{
    //   printf("The words now in the array are: %s\n",  words[i]);
    //}
    fclose(inPtr); //close the file
    return functioningFile;
}

// 333 // USER FUNCTION: writeSentenceToFile // 333 //
// Create a function to make a sentence and write it to a file. Each word will be selected at random from each array in the following order: article, adjective, noun, verb, preposition, article, adjective and noun. Use sprintf to create the sentence. The final sentence should start with a capital letter and end with a period and each sentence should be written to a file.
bool writeSentenceToFile(const char* path, const char article[][WORD_LENGTH], const char verb[][WORD_LENGTH], const char preposition[][WORD_LENGTH], const char noun[][WORD_LENGTH], const char adjective[][WORD_LENGTH], int numberWords,  int numberSentences)
{
    srand(time(NULL)); //seed with time so the random is different each time
    
    bool functioningFile = false;
    char fileLine[STRING_LENGTH] = { '\0' }; // temporarily array to hold the whole line for the file
    // array of Ptrs to the word arrays
    const char (*sentenceGrammer[]) [WORD_LENGTH] = { article, adjective, noun, verb, preposition, article, adjective, noun  }; // 8 elements in this sentence

    FILE *outPtr; //datastream to open
    outPtr = fopen( path, "w"); // "w" If a file with the same name already exists, its content is erased and the file is considered as a new empty file. // "w+ Creates an empty file for both reading and writing.
    if (outPtr == NULL)
        {
            printf("%s", "That outPtr didn't work.\n");
            functioningFile = false;
        }
    else
        {
            functioningFile = true;
        for (size_t i = 0; i < numberSentences; i ++)
        {
                sprintf(fileLine, "%s %s %s %s %s %s %s %s", sentenceGrammer[0][(rand() % numberWords)], sentenceGrammer[1][(rand() % numberWords)], sentenceGrammer[2][(rand() % numberWords)],  sentenceGrammer[3][(rand() % numberWords)],  sentenceGrammer[4][(rand() % numberWords)], sentenceGrammer[5][(rand() % numberWords)], sentenceGrammer[6][(rand() % numberWords)], sentenceGrammer[7][(rand() % numberWords)]         ); // sentenceGrammer[index of pointer to array][the index of the final array]

                    // printf("%s", fileLine); //TESTING
            fileLine[0] = toupper(fileLine[0]);
                    // printf("\n%s", fileLine); //TESTING CAPITALIZATION
            strcat(fileLine, ".");
                    // printf("\n%s", fileLine); // TESTING THE PERIOD
                    
        fprintf(outPtr, "%s\n", fileLine); //print the fileLine to the file
        } // end of  for (i=0, i < numberSentences; i ++)
            fclose(outPtr); // close the file
        } // end of else
    
    
    return functioningFile;
} // end of write Wentence to File

// 444 // USER FUNCTION: getFilePath // 444 //
// Create a function as defined below to get the file path for each file. Use strcpy and string strcat functions.
void getFilePath(char * finalPath, const char* directoryPath, const char* fileName)
{

    strcpy(finalPath, directoryPath); // copy directory path symbolic constant into final path
    strcat(finalPath, fileName); //catenate the file name to the end of the file path
    // printf("The path is %s", finalPath); //TESTING
    return;
}

