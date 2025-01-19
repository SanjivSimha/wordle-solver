#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "search_util.h"

int main(void) {
  char words[10][6] = {"stalk", "scrap", "shear", "batch", "motif",
                       "tense", "ultra", "vital", "ether", "nadir"};
  char **vocabulary = calloc(10, sizeof(char *));
  for (int i = 0; i < 10; i++) {
    vocabulary[i] = strdup(words[i]);
  }
  size_t num_words = 10;
  filter_vocabulary_gray('a', vocabulary, num_words);
  for (size_t i = 0; i < num_words; i++){
	  if (vocabulary[i]) printf("%s\n", vocabulary[i]);
  }
  
  filter_vocabulary_yellow('e', 2, vocabulary, num_words);
  for (size_t i = 0; i < num_words; i++) {
	  if (vocabulary[i]) printf("%s\n", vocabulary[i]);
  }
  filter_vocabulary_green('t', 0, vocabulary, num_words);
  for (size_t i = 0; i < num_words; i++){
	  if (vocabulary[i]) printf("%s\n", vocabulary[i]);
  }

  free_vocabulary(vocabulary, num_words);

  return 0;
}
