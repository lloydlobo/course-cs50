// Modifies the volume of an audio file
// https://cs50.harvard.edu/x/2023/labs/4/volume/

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WAV_HEADER_SIZE 44 // for standard PCM WAV file headers

#define USAGE_MESSAGE "Usage: ./volume input.wav output.wav factor\n"

int main(int argc, char *argv[]) {
  if (argc != 4) {
    fprintf(stderr, USAGE_MESSAGE);
    return 1;
  }

  FILE *input = fopen(argv[1], "r");
  if (input == NULL) {
    perror("Could not open input file.\n");
    return 1;
  }

  FILE *output = fopen(argv[2], "w");
  if (output == NULL) {
    perror("Could not open output file.\n");
    return 1;
  }

  float scaling_factor = atof(argv[3]);

  // Read and write the header
  uint8_t header[WAV_HEADER_SIZE];
  if (fread(header, sizeof(uint8_t), WAV_HEADER_SIZE, input) !=
      WAV_HEADER_SIZE) {
    perror("Failed to read header of WAV file");
    fclose(input);
    fclose(output);
    return 1;
  }
  fwrite(&header, sizeof(uint8_t), WAV_HEADER_SIZE, output);

  // Process each audio sample in the WAV file as an int16_t value
  int16_t buffer;
  while (fread(&buffer, sizeof(int16_t), 1, input) == 1) {
    buffer = (int16_t)(buffer * scaling_factor);
    fwrite(&buffer, sizeof(int16_t), 1, output);
  }

  // Close files
  fclose(input);
  fclose(output);

  return 0;
}

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
04:15pm zsh $ valgrind ./volume input.wav output.wav 3.0
==96862== Memcheck, a memory error detector
==96862== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==96862== Using Valgrind-3.21.0 and LibVEX; rerun with -h for copyright info
==96862== Command: ./volume input.wav output.wav 3.0
==96862==
==96862==
==96862== HEAP SUMMARY:
==96862==     in use at exit: 0 bytes in 0 blocks
==96862==   total heap usage: 4 allocs, 4 frees, 9,136 bytes allocated
==96862==
==96862== All heap blocks were freed -- no leaks are possible
==96862==
==96862== For lists of detected and suppressed errors, rerun with: -s
==96862== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
*/

// #define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
// fseek(input, 0, SEEK_END);
// long input_size = ftell(input); // 352844 (353k)
// rewind(input);
