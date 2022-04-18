/*=============================================================================
| Assignment: HW 02 – Calculating the 8, 16, or 32 bit checksum for a
| given input file
|
| Author: Showad Huda
| Language: C
|
| To Compile: gcc checksum.c
|
| To Execute: ./checksum inputText1.txt 8
| where the files in the command line are in the current directory.
|
| The text file contains text is mixed case with spaces, punctuation,
| and is terminated by the hexadecimal ‘0A’, inclusive.
| (The 0x’0A’ is included in the checksum calculation.)
|
| The checksum_size contains digit(s) expressing the checksum size
| of either 8, 16, or 32 bits
|
| Class: CIS3360 - Security in Computing – Spring 2021
| Instructor: McAlpin
| Due Date: 4/18/2021
|
+===============cd /cd==============================================================*/


//Pre-processor directives
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Two void type checksum parameters
//name of the file used for	calculating	the	checksum. the size,	in bits, of	the	checksum
void checkSumInput(char *filename, int size);
void checkSumRun(int size, char *input, unsigned int long *check);
//unsigned for positivity
unsigned int long stringToBitMask(char *text, int size);

//Main function parameters with command line arguments
//Establishes the name of the file and checksum bit size for computing
int main(int argc, char *argv[]){
	//Storing file name with char *fileName
	char *fileName = malloc(sizeof(char) *50);
	//Storing checksum bit size with int checkSumBitStore
	int checkSumBitStore;
	//Two files will be opened, so if-else established in case of less than two
	//If-Else Statement for Checksum 
	if(argc < 2){
		printf("Error: Prerequisites Not Met, Please Try Again.\n");
	}
	else{
		//First file name stored
		strcpy(fileName, argv[1]);
		//Second file converted and stored
		checkSumBitStore = atoi(argv[2]);
		
		//If statement to see checksum bit size value
		if(checkSumBitStore != 8 && checkSumBitStore != 16 && checkSumBitStore != 32){
			printf("Valid checksum sizes are 8, 16, or 32\n");
			//fprintf with stderr- I used printf since that's what the instruction .pdf stated.
			//fprintf(stderr, "Valid checksum sizes are 8, 16, or 32\n");
		}
		//Checksum to File
		checkSumInput(fileName, checkSumBitStore);
	}

}

//checkSumInput() function
//Establishes input and computes it for output of size, value, and c
void checkSumInput(char *fileName, int checkSumSize){
	//File pointer checksum
	FILE *fileInput;
	//Variables
	int charValue = 0;
	int characterCount = 0;
	int textLength = checkSumSize / 8 + 1;
	//Memory allocation
	unsigned int long *checksum = calloc(1, sizeof(unsigned int long));
	char *charInput = malloc(sizeof(char) *textLength);
	//Loop Iterative Method Variables
	int i = 0;
	int j = 0;
	int k = 0;
	//Open and read file
	fileInput = fopen(fileName, "r");
	
	//If-While to compute
	//Error message if incorrect input is entered
	if(fileInput == NULL){
		printf("Error: Input Invalid, Please Try Again.\n");
		return;
	}
	//Compute til End Of File
	while(charValue != EOF){
		//Length is 1
		if(textLength - i == 1){
			charInput[i] = '\0';
			printf("%s", charInput);
			//checkSumRun function to compute checksum
			checkSumRun(checkSumSize, charInput, checksum);
			j++;
			i = 0;
			//Check to see if length is 80 characters
			if(j * (textLength - 1) == 80){
				printf("\n");
			}
		}
		
		else{
			charValue = fgetc(fileInput);
			if(charValue == EOF){
				if(checkSumSize == 16 || checkSumSize == 32) //Check checksum size is 16 or 32 bits
				{
					//Check length
					if(textLength - i != 1 && textLength - i != textLength){
						k = 0;
						//Loop til length is one or textLength
						while(textLength - i != 1 && textLength - i != textLength){
							charInput[i] = 'X';
							i++;
							k++;
						}
						//Termination length i
						charInput[i] = '\0';
						printf("%s", charInput);
						//checkSumRun function to compute checksum
						checkSumRun(checkSumSize, charInput, checksum);
						j++;
						characterCount += k - 1;
						i = 0;
						//Check to see if length is 80 characters
						if(j * (textLength - 1) == 80){
							printf("\n");
						}
					}
					else{
						break;
					}
				}
				else{
					break;
				}
			}
			else{
				charInput[i] = charValue;
				characterCount++;
				i++;
			}
		}
	}
	
	//Closing input file
	fclose(fileInput);
	//New line for neatness readability
	printf("\n");
	
	//Computed display results
	printf("%2d bit checksum is %8lx for all %4d chars\n",checkSumSize, *checksum, characterCount);
	
}

//checkSumRun function
//Establishes computing checksum with string
void checkSumRun(int checkSumSize, char *stringInput, unsigned int long *checksum){
	unsigned int long bitMask;
	bitMask = stringToBitMask(stringInput, checkSumSize);
	//Compute checksum to 64 bits
	*checksum = bitMask + *checksum;
	*checksum = *checksum << (64 - checkSumSize);
	*checksum = *checksum >> (64 - checkSumSize);
}

//stringToBitMask function
//Establishes the checksums	are _masked_
unsigned int long stringToBitMask(char *stringInput, int checkSumSize){
	int i = 0;
	unsigned int long bitMasked;
	bitMasked = stringInput[i];
	checkSumSize -= 8;
	//While loop til checkSumSize is 0
	while(checkSumSize != 0){
		bitMasked = (bitMasked << 8) + stringInput[i + 1];
		checkSumSize -= 8;
		i++;
	}
	return bitMasked;
}


/*=============================================================================
| I, Showad Huda ([sh461424]) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/