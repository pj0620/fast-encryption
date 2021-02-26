#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "not enough input arguments - usage: %s [PLAINTEXT] [KEY]\n", argv[0]);
		exit(1);
	}

	// open plaintext file
	FILE *ciphertext;
	ciphertext = fopen(argv[1],"r");
	if (ciphertext == NULL) {
		fprintf(stderr, "could not open %s\n", argv[1]);
                exit(1);
	}

	// create plaintext file
	FILE *plaintext;
	plaintext = fopen("plaintext.txt","w");
   	char inBlock[8];
	unsigned long int last = 0x616161111110101;
	unsigned long int X;
	unsigned long int Y;
	int blockStopped = -1;
	char* outBlock = (char *) & X;
	while (blockStopped == -1) {
		// get input block 
		for (int i = 0; i < 8; ++i) {
			inBlock[i] = fgetc(ciphertext);
			if (EOF == inBlock[i]) {
				blockStopped = i;
				break;
			}
		}
		if (blockStopped != -1) {
			for (; blockStopped < 8; ++blockStopped) {
				inBlock[blockStopped] = 0;
			}
		}
		Y = * (unsigned long int *) & inBlock;
		
		
		// write output block
		X = Y - last;
		last = X;
		for (int i = 0; i < 8; i++) {
			fputc(outBlock[i], plaintext); 
		}
		
		//printf("res = %016lx\n", a); 
	}

	// close files
	fclose(plaintext);
	fclose(ciphertext);


	return 0;
}
