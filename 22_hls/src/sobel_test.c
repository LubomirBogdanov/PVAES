#include "sobel_test.h"

int main(void){
	uint8_t img_in[240][320];
	uint8_t img_out[240][320];
	FILE *fin, *fout;
	long int file_size;

	fin = fopen("/home/user/workspaces/hls_workspace/sobel/logo_en.B","rb");

	if(fin == NULL){
		printf("Error reading file!");
		return 1;
	}

	fseek(fin, 0L, SEEK_END);
	file_size = ftell(fin);
	rewind(fin);

	printf("\n\n\nFile size is: %ld bytes\n\n\n", file_size);

	fread(&img_in, 1, file_size, fin);

	fclose(fin);

	fout =	fopen("/home/user/workspaces/hls_workspace/sobel/logo_en_converted.B","wb");
	if(fout == NULL){
		printf("Error creating a file for writing!\n");
		return 1;
	}

	sobel(img_in, img_out);

	fwrite(&img_out, 1, file_size, fout);

	fclose(fout);

	return 0;
}
