#include "read_huffman_encoded_data.h"


unsigned char *read_huffman_encoded_data(char *compressed_file_name_ptr, int *image_width, int *image_height, 
	int *max_gray_value, int *number_of_nodes, struct node **huffman_node, long int *length_of_encoded_image_array){
	
	FILE *filePtr;
	filePtr = fopen(compressed_file_name_ptr,"r");

	int width, height, maxGray, nodeNumber;
	long int arrayLength;

	// Read the integers and long int from the file
	fscanf(filePtr, "%d %d %d %d %ld ", &width, &height, &maxGray, &nodeNumber, &arrayLength);


	// Set up pointers so we can extract data
	*image_width = width;
	*image_height = height;
	*max_gray_value = maxGray;
	*number_of_nodes = nodeNumber;
	*length_of_encoded_image_array = arrayLength;

	// Special case if the number of nodes was 0
	if (nodeNumber == 0) 
		nodeNumber = 1;

	// Read the node pairs from the file
	struct node *nodeArray;
	nodeArray = malloc( (nodeNumber) * sizeof(struct node) );
	int firstVal, secondVal;

	for (int i = 0; i < nodeNumber; i++){
		fscanf(filePtr, "%d %d", &firstVal, &secondVal);
		nodeArray[i].first_value = firstVal;
		nodeArray[i].second_value = secondVal;
	}

	*huffman_node = nodeArray;

	fgetc(filePtr);
	fgetc(filePtr);

	// Read the encoded image from the file
	unsigned char *encodedData;
	encodedData = malloc(arrayLength);
	unsigned char data;

	for (int i = 0; i < arrayLength; i++){
		data = fgetc(filePtr);
		encodedData[i] = data;
	}
	
	fclose(filePtr);
	return encodedData;
}