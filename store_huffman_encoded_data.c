#include "store_huffman_encoded_data.h"

void store_huffman_encoded_data(char *compressed_file_name_ptr, int image_width, int image_height, int max_gray_value, 
	int number_of_nodes, struct node *huffman_node, long int length_of_encoded_image_array, unsigned char *encoded_image){

	FILE *filePtr;
	filePtr = fopen(compressed_file_name_ptr,"w");

	// Write the header with the simple integers first
	fprintf(filePtr, "%d %d %d %d %ld ", image_width, image_height, max_gray_value, number_of_nodes, length_of_encoded_image_array);

	// Set the number of nodes to be 1 if in the special case where the image is one colour
	if (number_of_nodes == 0) number_of_nodes = 1;

	// Write to the header all the node pairs
	for (int i = 0; i < number_of_nodes; i++){
		fprintf(filePtr, "%d %d ", huffman_node[i].first_value, huffman_node[i].second_value);
	}
	fprintf(filePtr, "\n");

	// Write the encoded picture to the file
	for (int i = 0; i < length_of_encoded_image_array; i++){
		fputc(encoded_image[i], filePtr);
	}

	fclose(filePtr);
} 