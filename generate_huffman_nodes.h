#ifndef NODES_H
#define NODES_H

#include <stdio.h>
#include <stdlib.h>
#include "libpnm.h"

struct node{
	int first_value;
	int second_value;
};

#endif

struct node *generate_huffman_nodes(long int *pixel_frequency, int max_gray_value, int number_of_non_zero_values_in_the_frequency_array);