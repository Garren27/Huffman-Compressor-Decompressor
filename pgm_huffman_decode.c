#include "libpnm.h"
#include <stdio.h>
#include "read_huffman_encoded_data.h"
#include "huffman_decode_image.h"

/*
main takes 2 arguments
input file name: a file that contains a compressed pgm image
output file name: a file that will contain a decompressed pgm image
*/
int main(int argc, char *argv[]){

	// Validate the number of arguments, there should be 2 besides the program name
	if (argc != 3){
		printf("Error: Number of arguments must be 2\n");
		return 0;
	}
	
	int width, height, maxGray, nodeNumber;
	long int encodedLength;

	// Set up pointers we will be passing around
	int *widthPtr = &width;
	int *heightPtr = &height;
	int *grayPtr = &maxGray;
	int *nodeNumPtr = &nodeNumber;
	long int *lengthPtr = &encodedLength;

	struct node *nodeList;
	struct node **nodeListPtr = &nodeList;

	// Get the encoded data from the file
	unsigned char *huffmanEncodedData = read_huffman_encoded_data(argv[1], widthPtr, heightPtr, grayPtr, nodeNumPtr, nodeListPtr, lengthPtr);

	// Get the decompressed image struct
	struct PGM_Image *img = huffman_decode_image(width, height, maxGray, nodeNumber, nodeList, encodedLength, huffmanEncodedData);

	// Write the uncompressed image to file
	save_PGM_Image(img, argv[2], 1);
	free_PGM_Image(img);

	return 0;
}