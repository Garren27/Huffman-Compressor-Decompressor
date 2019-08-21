#include "libpnm.h"
#include "generate_pixel_frequency.h"
#include "huffman_encode_image.h"
#include "store_huffman_encoded_data.h"
#include <stdio.h>

/*
main takes 2 arguments
input file name: a file that contains a pgm image
output file name: a file that will contain a pgm image
*/
int main(int argc, char *argv[]){

	// Validate the number of arguments, there should be 2 besides the program name
	if (argc != 3){
		printf("Error: Number of arguments must be 2\n");
		return 0;

	}

	// Create the image pointer we will work with
	struct PGM_Image pgmIm;
	struct PGM_Image *pgmPtr;
	pgmPtr = &pgmIm;

	// Get the image name from the command line
	load_PGM_Image(pgmPtr, argv[1]);

	int number_of_non_zeros = 0;
	int *number_of_non_zeros_ptr = &number_of_non_zeros;
	
	// Get a pixel frequency array
	long int *pixelFreqArray = generate_pixel_frequency(pgmPtr, number_of_non_zeros_ptr);

	// Get the huffman nodes
	struct node *huffmanNodes = generate_huffman_nodes(pixelFreqArray, pgmPtr->maxGrayValue, number_of_non_zeros);

	long int length_of_encoded_image_array = 0;
	long int *length_of_encoded_image_array_ptr = &length_of_encoded_image_array;
	
	// Get the encoded image
	unsigned char *huffmanImage = huffman_encode_image(pgmPtr, huffmanNodes, number_of_non_zeros - 1, length_of_encoded_image_array_ptr);
	
	// Store the encoded image
	store_huffman_encoded_data(argv[2], pgmPtr->width, pgmPtr->height, pgmPtr->maxGrayValue, number_of_non_zeros - 1, huffmanNodes, length_of_encoded_image_array, huffmanImage);

	// Memory clean up
	free_PGM_Image(pgmPtr);
	free(pixelFreqArray);
	free(huffmanNodes);
	free(huffmanImage);

	return 0;
}