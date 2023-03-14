/* *********************************************
 * Author: Danny Brokke (dannybrokke@live.com)
 * Desc: C program that reads a file in, applies
 * the ROT13 cipher to every character, then 
 * writes the enciphered text back to the file.
*/ *********************************************

// The rot13 function prototype
void rot13( const char *input, char *output);
// Included libraries
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define IN_SIZE     40          // 40 characters per data line

/* ==============================================
main_method

This is my main method for the assignment. 
It takes a FILE as an input and it creates a FILE object to output to.
It reads line by line from the input file, modifies the data in real time,
then prints the modified data to the output folder.
The modified data is just the text after it has been put through the rot13 cipher.
Space values are not encrypted, but they must stay in their same location.
Newlines are not encrypted, must stay in their same location.


================================================ */

int main( int ac, char *av[] )
{
    
	FILE *readPtr;
	FILE *writePtr;
	
	if ((readPtr = fopen("c://Users//danny//Desktop//input.txt", "r")) == NULL) {
		puts("File for reading could not be opened");	
		return(1);
	
	}

	if ((writePtr = fopen("c://Users//danny//Desktop//output.txt", "w")) == NULL) {
		puts("File for writing could not be opened");	
		return(1);
	
	}
	
    printf(" \n");
	while (!feof(readPtr)){

        // Creating two character arrays that will act as strings
        // to hold our current input/output values for that line.
	char input[IN_SIZE];
        char output[IN_SIZE];
        // Using fgets to load the array with its max amount of objects, 
        // based around where the readPtr is reading.
        fgets(input, IN_SIZE, readPtr);
        printf("%s\n", input);
        rot13(input, output);
        fputs(output, writePtr);
	}
    printf(" \n");
	fclose(readPtr);
	fclose(writePtr);
    return( 0 );
}

void rot13(const char *input, char *output)
{
	// Copying the array so as to make sure the input data stays constant.
        for (int i = 0; i < IN_SIZE; i++)
        {
            output[i] = input[i];
        }
        
	// Looping through each character in the array
	for (int i = 0; i < IN_SIZE; i++)
        {

            int compare = tolower(input[i]);

                // Making sure to only go in the for loop if the character is not a space or newline (10/32 are those in decimal, respectively).
                if (input[i] != '\0' && input[i] != '\n' && compare != 10 && compare != 32)
                {
                    // Creating the compare value by subtracting the current letter from z
                    int compare = 'z' - tolower(input[i]);
                    // If less than 13 that means the letter is close enough that we will end up having to reset it. 
                    // So let's reset it, and properly increment it.
                    if (compare < 13)
                    {
                        int counter = 13 - compare - 1;
                        output[i] = 'a';
                        while(counter != 0)
                        {
                            output[i]++;
                            counter--;
                        }
                    } 
                    // If its not a character that will run into issues with z, just increment it by 13.
                    else
                    {
                        output[i] = tolower(output[i]+=13);
                    }
                }
        } 
        // Printing the values just to check the output easier than having to reopen the file.
        printf("Post Rot13: %s\n", output);
        
}
