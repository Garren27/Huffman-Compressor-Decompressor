#include "generate_pixel_frequency.h" 

long int *generate_pixel_frequency(struct PGM_Image *input_pgm_image, int *number_of_non_zero_values_in_the_frequency_array){
	
	// Create array with length equal to maxGray so we can fit all pixels in it
	long int *arrayPointer;
	arrayPointer = calloc( (input_pgm_image->maxGrayValue) + 1, sizeof(long int));

	if (arrayPointer == NULL){
		printf("Memory allocation for array failed\n");
		return 0;
	}

	int imageHeight = input_pgm_image->height;
	int imageWidth = input_pgm_image->width;

	int imageValue = 0;

	// Count the number of occurances of each pixel
	for (int i = 0; i < imageHeight; i++){
		for (int j = 0; j < imageWidth; j++){
			imageValue = input_pgm_image->image[i][j];
			arrayPointer[imageValue]++;
		}
	}

	// Count the number of pixels that have at least one occurance
	int nonZeroCounter = 0;
	for (int i = 0; i <= input_pgm_image->maxGrayValue; i++){
		if (arrayPointer[i] != 0){
			nonZeroCounter++;
		}
	}

	*number_of_non_zero_values_in_the_frequency_array = nonZeroCounter;
	return arrayPointer;
}