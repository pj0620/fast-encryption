#include <stdio.h>
#include <stdlib.h>

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
	unsigned long int last = 0x616161111110101;
	unsigned long int X;
	unsigned long int Y;
	int blockStopped = -1;
	char* outBlock = (char *) & Y;
	while (blockStopped == -1) {
		// get input block 
		for (int i = 0; i < 8; ++i) {
			inBlock[i] = fgetc(plaintext);
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
		X = * (unsigned long int *) & inBlock;
		
		
		// write output block
		Y = X + last;
		last = X;
		for (int i = 0; i < 8; i++) {
			fputc(outBlock[i], ciphertext); 
		}
		
		//printf("res = %016lx\n", a); 
	}

	// close files
	fclose(plaintext);
	fclose(ciphertext);


	return 0;
}
