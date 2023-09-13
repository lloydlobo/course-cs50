// Modifies the volume of an audio file
// https://cs50.harvard.edu/x/2023/labs/4/volume/

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

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

  size_t HEADER_PCM_WAV_SIZE = 48;
  uint8_t header[HEADER_PCM_WAV_SIZE];

  size_t ret = fread(header, sizeof(uint8_t), ARRAY_SIZE(header), input);
  if (ret != HEADER_PCM_WAV_SIZE) {
    perror("Failed to read the entire file");
    fclose(input);
    fclose(output);
    return 1;
  }

  fwrite(&header, sizeof(uint8_t), ARRAY_SIZE(header), output);

  // DONE: Read samples from input file and write updated data to output file

  int16_t buffer;
  while (fread(&buffer, sizeof(int16_t), 1, input) == 1) {
    buffer = (int16_t)(buffer * scaling_factor);
    fwrite(&buffer, sizeof(int16_t), 1, output);
  }

  // Close files
  fclose(input);
  fclose(output);
}

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
