// Modifies the volume of an audio file
// https://cs50.harvard.edu/x/2023/labs/4/volume/

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

const size_t HEADER_PCM_WAV_SIZE = 44;

int main(int argc, char *argv[]) {
  if (argc != 4) {
    printf("Usage: ./volume input.wav output.wav factor\n");
    return 1;
  }

  FILE *input = fopen(argv[1], "r");
  if (input == NULL) {
    perror("Could not open file.\n");
    return 1;
  }

  FILE *output = fopen(argv[2], "w");
  if (output == NULL) {
    perror("Could not open file.\n");
    return 1;
  }

  float scaling_factor = atof(argv[3]);

  // DONE: Copy header from input file to output file

  fseek(input, 0, SEEK_END);
  long input_size = ftell(input); // 352844 (353k)
  rewind(input);

  uint8_t header[HEADER_PCM_WAV_SIZE];

  size_t ret = fread(header, sizeof(uint8_t), ARRAY_SIZE(header), input);
  if (ret != HEADER_PCM_WAV_SIZE) {
    perror("Failed to read header af WAV file");
    fclose(input);
    fclose(output);
    return 1;
  }

  fwrite(&header, sizeof(uint8_t), ARRAY_SIZE(header), output);

  // DONE: Read samples from input file and write updated data to output file

  int16_t buffer;
  // treat each sample of audio in a WAV file as an int16_t value.
  while (fread(&buffer, sizeof(int16_t), 1, input) == 1) {
    buffer = (int16_t)(buffer * scaling_factor);
    fwrite(&buffer, sizeof(int16_t), 1, output);
  }

  // Close files
  fclose(input);
  fclose(output);
}

/*
 * PERF: Your program, if it uses malloc, must not leak any memory.
 *
 * int16_t buffer = (int16_t)malloc(input_size - ARRAY_SIZE(header));
 * size_t ret = fread(buffer, sizeof(int16_t), ARRAY_SIZE(buffer), input);
 * // ... handle error
 *
 * for (size_t i = 0; i < ARRAY_SIZE(buffer); i++) {
 *    int16_t sample = buffer[i];
 *    buffer[i] = (sample * scaling_factor);
 * }
 * fwrite(&buffer, sizeof(uint8_t), ARRAY_SIZE(buffer), output);
 *
 * free(buffer)
 *
 * // ... close files
 */

/*
 WAV Files

 WAV files are a common file format for representing audio. WAV files store
 audio as a sequence of “samples”: numbers that represent the value of some
 audio signal at a particular point in time. WAV files begin with a 44-byte
 “header” that contains information about the file itself, including the size of
 the file, the number of samples per second, and the size of each sample. After
 the header, the WAV file contains a sequence of samples, each a single 2-byte
 (16-bit) integer representing the audio signal at a particular point in time.

 Scaling each sample value by a given factor has the effect of changing the
 volume of the audio. Multiplying each sample value by 2.0, for example, will
 have the effect of doubling the volume of the origin audio. Multiplying each
 sample by 0.5, meanwhile, will have the effect of cutting the volume in half.
 */

/*
 * 11:47am zsh $ valgrind ./volume input.wav output.wav 3.00
 *
 * ==1706756== Memcheck, a memory error detector
 * ==1706756== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
 * ==1706756== Using Valgrind-3.21.0 and LibVEX; rerun with -h for copyright
 * info
 * ==1706756== Command: ./volume input.wav output.wav 3.00
 * ==1706756==
 *
 * ==1706756== HEAP SUMMARY:
 * ==1706756==     in use at exit: 0 bytes in 0 blocks
 * ==1706756==   total heap usage: 5 allocs, 5 frees, 10,160 bytes allocated
 * ==1706756==
 * ==1706756== All heap blocks were freed -- no leaks are possible
 * ==1706756==
 * ==1706756== For lists of detected and suppressed errors, rerun with: -s
 * ==1706756== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
 */
