#include "search_util.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

int score_letter(char letter, char **vocabulary, size_t num_words) {
  int counter = 0;
  for (size_t i = 0; i < num_words; i++){
	  if (vocabulary[i] == NULL){
		  continue;
	  }
	  if (strchr(vocabulary[i], letter) != NULL){
		  counter++;
	  }
  }
  return counter;
}

int score_word(char *word, int *letter_scores) {
  int score = 0;
  bool letters_seen[26] = {false};
  for (int i = 0; word[i] != '\0'; i++){
	  char letter = word[i];
	  if (letter >= 'a' && letter <= 'z'){
		  int index = letter - 'a';
		  if (!letters_seen[index]){
			  score += letter_scores[index];
			  letters_seen[index] = true;
		  }
	  }
  }
  return score;
}

char *get_guess(char **vocabulary, size_t num_words) {
  int letter_scores[26];

  for (int i = 0; i < 26; i++) {
    letter_scores[i] = score_letter('a' + i, vocabulary, num_words);
  }

  char *best_guess = NULL;
  int best_score = 0;
  int score = 0;
  for (size_t i = 0; i < num_words; i++) {
    if (vocabulary[i] == NULL) {
      continue;
    }
    score = score_word(vocabulary[i], letter_scores);
    if (score > best_score) {
      best_guess = vocabulary[i];
      best_score = score;
    }
  }
  return best_guess ? strdup(best_guess) : NULL;
}

size_t filter_vocabulary_gray(char letter, char **vocabulary,
                              size_t num_words) {

  size_t count = 0;
  for (size_t i = 0; i < num_words; i++){
	  if (vocabulary[i] == NULL){
		  continue;
	  }
	  if (strchr(vocabulary[i], letter) != NULL){
		  free(vocabulary[i]);
		  vocabulary[i] = NULL;
		  count++;
	  }
  }
  return count;
}

size_t filter_vocabulary_yellow(char letter, int position, char **vocabulary,
                                size_t num_words) {
	size_t count = 0;
	for (size_t i = 0; i < num_words; i++){
		if (vocabulary[i] == NULL) {
			continue;
		}
		char *word = vocabulary[i];
		if (strchr(word, letter) == NULL || word[position] == letter){
			free(vocabulary[i]);
			vocabulary[i] = NULL;
			count++;
		}
	}
	return count;
}

size_t filter_vocabulary_green(char letter, int position, char **vocabulary,
                               size_t num_words) {
  size_t count = 0;
  for (size_t i = 0; i < num_words; i++){
	  if (vocabulary[i] == NULL){
		  continue;
	  }
	  if (vocabulary[i][position] != letter){
		  free(vocabulary[i]);
		  vocabulary[i] = NULL;
		  count++;
	  }
  }
  return count;
}

void free_vocabulary(char **vocabulary, size_t num_words) {
  for (size_t i = 0; i < num_words; i++) {
    free(vocabulary[i]);
  }
  free(vocabulary);
}
