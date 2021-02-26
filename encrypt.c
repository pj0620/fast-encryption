#include <stdio.h>
#include <stdlib.h>

// Assuming: 
//	sizeof(unsigned long int) = 4
//	sizeof(char) = 1
int getNextBlock(char * inputBlock, unsigned long int * runningSum) {
	for (int i = 0; i < 4; i++) {
		
	}
} 

int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "not enough input arguments - usage: %s [PLAINTEXT] [KEY]\n", argv[0]);
		exit(1);
	}

	// open plaintext file
	FILE *plaintext;
	plaintext = fopen(argv[1],"r");
	//printf("openning %s\n", argv[1]);
	if (plaintext == NULL) {
		fprintf(stderr, "could not open %s\n", argv[1]);
                exit(1);
	}

	// create ciphertext file
	FILE *ciphertext;
	ciphertext = fopen("ciphertext.bin","w");
   	char inBlock[8];
	unsigned long int runningSum = 123456789;
	int blockStopped = -1;
	while (blockStopped == -1) {
		for (int i = 0; i < 8; ++i) {
			//printf("looping\n");
			inBlock[i] = fgetc(plaintext);
			if (EOF == inBlock[i]) {
				//printf("here\n");
				blockStopped = i;
				break;
			}
			else {
				printf("char = %02x\n", inBlock[i]);
			}
		}
	}
	// zero pad missing blocks
	if (blockStopped != 0) {
		for (; blockStopped < 8; ++blockStopped) {
			inBlock[blockStopped] = 0;
		}
	}

	unsigned long int a = * (unsigned long int *) & inBlock;
	printf("res = %016lx", a);

	// close files
	fclose(plaintext);
	fclose(ciphertext);


	return 0;
}
