/**
 * Document: MaxCompiler Tutorial (maxcompiler-tutorial.pdf))>
 * Chapter: 9      Example: 3      Name: Complex Counter
 * MaxFile name: ComplexCounter
 * Summary:
 *       Shows how to creates advanced counters which specify a
 *   maximum value, increment, wrap mode and enable stream.
 */

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "DFE.h"
#include <MaxSLiCInterface.h>

void generateInputData(int size, uint32_t *input)
{
	for (int i = 0; i < size; i++)
		input[i] = i;
}

void ComplexCounterCPU(
	int size,
	uint32_t *input,
	uint32_t *countOneOut,
	uint32_t *countTwoOut,
	uint32_t *expected)
{

	int countOneState = 0;
	int countTwoState = 0;

	for (int i = 0; i < size; i++) {

		int countOneWrap = 0;
		if (countOneState >= DFE_countOneMax) {
			countOneState = 0;
			countOneWrap = 1;
		}

		if (countTwoState < DFE_countTwoMax && countOneWrap == 1)
			countTwoState++;

		expected[i] = input[i] + countTwoState;
		countOneState += DFE_countOneInc;
		countOneOut[i] = countOneState;
		countTwoOut[i] = countTwoState;
	}

}

int check(int size, uint32_t *result, uint32_t *expected)
{
	int status = 0;
	for (int i = 0; i < size; i++) {
		if (result[i] != expected[i]) {
			fprintf(stderr, "[%d] Verification error, out: %d != expected: %d\n",
				i, result[i], expected[i]);
			status = 1;
		}
	}
	return status;
}

int main()
{
	const int size = 1024;
	int sizeBytes = size * sizeof(uint32_t);
	uint32_t *input = malloc(sizeBytes);
	uint32_t *result = malloc(sizeBytes);
	uint32_t *countOneOut = malloc(sizeBytes);
	uint32_t *countTwoOut = malloc(sizeBytes);
	uint32_t *countOneExpected= malloc(sizeBytes);
	uint32_t *countTwoExpected = malloc(sizeBytes);
	uint32_t *expected = malloc(sizeBytes);

	generateInputData(size, input);

	// Run the streams
	printf("Running DFE.\n");
	DFE(size, input, countOneOut, countTwoOut, result);

	ComplexCounterCPU(size, input, countOneExpected, countTwoExpected, expected);

	int status = check(size, result, expected);
	if (status)
		printf("Test failed.\n");
	else
		printf("Test passed OK!\n");

	return status;
}
