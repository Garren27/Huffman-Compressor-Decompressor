#include "generate_huffman_nodes.h"

struct node *generate_huffman_nodes(long int *pixel_frequency, int max_gray_value, int number_of_non_zero_values_in_the_frequency_array){

	// Initialize the array of nodes, with the number of nodes being number_of_non_zero_values_in_the_frequency_array - 1
	struct node *nodeArray;
	if (number_of_non_zero_values_in_the_frequency_array > 1){
		nodeArray = malloc( (number_of_non_zero_values_in_the_frequency_array - 1) * sizeof(struct node) );
	}

	// Special case where the number of pixel values is 1
	else{
		nodeArray = malloc(sizeof(struct node));
		int i = 0;
		while (pixel_frequency[i] == 0){
			i++;
		}
		nodeArray[0].first_value = i;
		nodeArray[0].second_value = i;
		return nodeArray;
	}

	if (nodeArray == NULL){
		printf("Memory allocation for array failed\n");
		return 0;
	}

	// Declare the node trackers and smallest counters
	long int firstSmallest;
	int firstNode;
	long int secondSmallest;
	int secondNode;

	long int newSum = 0;
	long int maxValue = 0;

	for (int i = 0; i <= max_gray_value; i++){
		if (pixel_frequency[i] != 0 ){
			maxValue += pixel_frequency[i];
		}		
	}
	// Loop over the pixel_frequency array enough times so every node in nodeArray is filled
	for (int i = 0; i < number_of_non_zero_values_in_the_frequency_array - 1; i++){

		// Initialize our smallest counters and node trackers to maxValue + 1 because we know that is larger than any frequency
		firstSmallest = maxValue + 1;
		firstNode = maxValue + 1;

		// Calculate the smallest two numbers in the frequency array and their node locations
		for (int j = 0; j <= max_gray_value; j++){

			//Check if pixel_frequency[j] is the smallest
			if (pixel_frequency[j] < firstSmallest && pixel_frequency[j] != 0){
				secondSmallest = firstSmallest;
				secondNode = firstNode;
				firstSmallest = pixel_frequency[j];
				firstNode = j;
			}

			// If j wasn't the smallest, check if it was the second smallest
			else {
				if(pixel_frequency[j] < secondSmallest && pixel_frequency[j] != 0 ){
					secondSmallest = pixel_frequency[j];
					secondNode = j;
				}
			}
		}
		
		// Update the smallest frequency position with the sum of the frequencies of the two smallest nodes
		newSum = firstSmallest + secondSmallest;
		pixel_frequency[firstNode] = newSum;

		// Set the second smallest frequency position to be larger than all the rest
		pixel_frequency[secondNode] = maxValue + 1;

		// Update the node array at i with the position of the first and second nodes
		nodeArray[i].first_value = firstNode;
		nodeArray[i].second_value = secondNode;
	}

	return nodeArray;
}