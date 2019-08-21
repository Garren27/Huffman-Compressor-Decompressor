#include "huffman_encode_image.h"

unsigned char *huffman_encode_image(struct PGM_Image *input_pgm_image, struct node *huffman_node, int number_of_nodes, 
	long int *length_of_encoded_image_array){

	char huffmanCodesArray[input_pgm_image->maxGrayValue][number_of_nodes];

	// Initialize the huffman codes array with empty space
	for (int i = 0; i < (input_pgm_image->maxGrayValue) + 1; i++){
		strcpy(huffmanCodesArray[i], "");
	}

	if (number_of_nodes == 0){
		strcat(huffmanCodesArray[huffman_node[0].first_value], "0");
	}

	//Generate the Huffman codes for each symbol
	for (int i = number_of_nodes - 1; i >= 0; i--){
		int firstSymbol = huffman_node[i].first_value;
		int secondSymbol = huffman_node[i].second_value;

		//Copy the value of the first symbol and add it the end of the second symbol
		strcat(huffmanCodesArray[secondSymbol], huffmanCodesArray[firstSymbol]);
		// Concatenate 0 to the end of the first symbol and 1 to the end of the second symbol
		strcat(huffmanCodesArray[firstSymbol], "0");
		strcat(huffmanCodesArray[secondSymbol], "1" );
	}

	int imageHeight = input_pgm_image->height;
	int imageWidth = input_pgm_image->width;

	int imageValue = 0;

	int number_of_non_zeroes = 0;
	int *zeroesPtr = &number_of_non_zeroes;

	long int *pixelFreqArray = generate_pixel_frequency(input_pgm_image, zeroesPtr);

	//Calculate the precise length of encoded image array
	*length_of_encoded_image_array = 0;
	for (int i = 0; i <= input_pgm_image->maxGrayValue; i++){
		if(pixelFreqArray[i] != 0){
			*length_of_encoded_image_array += (pixelFreqArray[i] * strlen(huffmanCodesArray[i]));
		}
	}
	free(pixelFreqArray);

	int encodedImagePosition = 0;
	int buffer = 0;
	unsigned char character = 0x00;

	*length_of_encoded_image_array = (*length_of_encoded_image_array / 8) + 1;
	unsigned char *huffmanEncodedImage;
	huffmanEncodedImage = malloc(*length_of_encoded_image_array * sizeof(unsigned char));


	// Read every pixel value from the file to the get the value to encode
	for (int i = 0; i < imageHeight; i++){
		for (int j = 0; j < imageWidth; j++){
			imageValue = input_pgm_image->image[i][j];

			for (int k = 0; k < strlen(huffmanCodesArray[imageValue]); k++){

				//Buffer is < 8
				if (buffer < 8){
					if (huffmanCodesArray[imageValue][k] == '0'){
						character = character << 1;
					}
					else{
						//should be 1
						character = character << 1;
						character |= 0x01;
					}
					buffer++;
				}
				//Buffer is 7, we need to write the character and push to the encoded image
				else{
					huffmanEncodedImage[encodedImagePosition] = character;
					buffer = 0;
					character = 0x00;
					encodedImagePosition++;
					if (huffmanCodesArray[imageValue][k] == '0'){
						character = character << 1;
					}
					else{
						character = character << 1;
						character |= 0x01;
					}
					buffer++;
				}
			}
		}
	}

	// Adjust the character so that the extra zeroes are at the end of the character when we reach the end
	for (int i = 0; i < 8 - buffer; i++){ 
		character = character << 1;
	}
	// Write the last character to the encoded image
	huffmanEncodedImage[encodedImagePosition] = character;


	return huffmanEncodedImage; 
}