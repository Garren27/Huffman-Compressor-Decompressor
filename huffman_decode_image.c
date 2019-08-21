#include "huffman_decode_image.h"

// Type definition of the nodes to be used in the array tree
struct treeNode{
	int value;
	int index;

	int leftChild;
	int rightChild;
};

struct PGM_Image *huffman_decode_image( int image_width, int image_height, int max_gray_value, int number_of_nodes,
	struct node *huffman_node, long int length_of_encoded_image_array, unsigned char *encoded_image){

	if (number_of_nodes == 0) number_of_nodes = 1;

	struct PGM_Image *imagePtr = malloc(sizeof(struct PGM_Image));
	create_PGM_Image(imagePtr, image_width, image_height, max_gray_value);


	// Create the Huffman tree with an array 
	int numberOfNodesInTree = (number_of_nodes + 1) + (number_of_nodes);
	struct treeNode *treeList = malloc(numberOfNodesInTree * sizeof(struct treeNode));
	int arrayPosition = 0;
	int nextOpenSpot = 1;

	// Initialize all of the nodes in the tree
	for (int i = 0; i < numberOfNodesInTree; i++){
		treeList[i].value = -1;
		treeList[i].index = i;
		treeList[i].leftChild = -1;
		treeList[i].rightChild = -1;
	}
	
	// Initialize Huffman tree with the first two nodes
	int firstSymbol = huffman_node[number_of_nodes-1].first_value;
	int secondSymbol = huffman_node[number_of_nodes-1].second_value;

	treeList[0].leftChild = nextOpenSpot;
	treeList[0].rightChild = nextOpenSpot+1;

	treeList[nextOpenSpot].value = firstSymbol;
	treeList[nextOpenSpot+1].value = secondSymbol;
	nextOpenSpot = nextOpenSpot + 2;

	// Build the rest of the tree nodes and pointers
	for (int i = number_of_nodes-2; i >= 0; i--){
		firstSymbol = huffman_node[i].first_value;
		secondSymbol = huffman_node[i].second_value;

		for (int i = 0; i < numberOfNodesInTree; i++){
			if (treeList[i].value == firstSymbol){
				arrayPosition = i;
				break;
			}
		}

		// Update the node children and the node value
		treeList[arrayPosition].leftChild = nextOpenSpot;
		treeList[arrayPosition].rightChild = nextOpenSpot+1;
		treeList[arrayPosition].value = -1;

		// Update the tree and nextOpenSpot counter so we know where to put the next pair of nodes
		treeList[nextOpenSpot].value = firstSymbol;
		treeList[nextOpenSpot+1].value = secondSymbol;
		nextOpenSpot = nextOpenSpot + 2;
	}

	unsigned char character = 0x00;
	unsigned char result = 0x00;
	int found = 0;
	int buffer = 0; 
	arrayPosition = 0;
	int pixelValue = -1;
	int treePosition = 0;

	// Decode the image using the Huffman Tree
	for (int i = 0; i < image_height; i++){
		for (int j = 0; j < image_width; j++){

			while (found == 0){
				// If the buffer is full, reset it and get update the array position pointer
				if (buffer == 8){
					arrayPosition++;
					buffer = 0;
				}
				
				// Get the next character from the array and get the first bit
				character = encoded_image[arrayPosition];
				result = (character << buffer) & 0x80;
				buffer++;

				// Traverse the tree, going left if bit was 0 and right if 1
				if (result == 0){
					treePosition = treeList[treePosition].leftChild;
				}
				else{
					treePosition = treeList[treePosition].rightChild;
				}

				// If the tree value is not -1, we should be at the right value
				if (treeList[treePosition].value != -1){
					found = 1;
					pixelValue = treeList[treePosition].value;
				}

			}

			// Write the image value into the image and reset found flag and tree position to root
			imagePtr->image[i][j] = pixelValue;
			found = 0;
			treePosition = 0;
		}
	}

	free(treeList);
	return imagePtr;
}