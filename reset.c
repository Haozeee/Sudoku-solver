#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *name = "input.txt";
	FILE *file = fopen(name, "w");
	if (file == NULL){
		printf("Unable to create file\n");
		return 1;
	}
	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++){
			if (j != 8){
				fputs("0 ", file);
			}
			else if (j == 8 && i == 8){
				fputs("0", file);
			}
			else{
				fputs("0\n", file);
			}
		}
	}
	printf("Board reset\n");
}