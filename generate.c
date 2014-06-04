#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void generateLine() {
  time_t now;
  time(&now);
  fprintf(stdout, "%d\t%d\t%d\t%lu.%d\n", rand(), rand(), rand(), (unsigned long)now, rand() % 1000);
}

int main(int argc, char **argv) {
  unsigned long number;
  char *invalid = NULL;

  if (argc < 2) {
    fprintf(stderr, "Usage: %s <number-of-records>", argv[0]);
    return 1;
  }

  number = strtoul(argv[1], &invalid, 10);

  if (strlen(invalid) != 0) {
    fprintf(stderr, "Invalid number: %s", argv[1]);
    return 1;
  }

  for (int i = 0; i < number; i++) {
    generateLine();
  }

  return 0;
}
