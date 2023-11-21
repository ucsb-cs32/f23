#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void init() {
  setvbuf(stdin,  NULL, 2, 0);
  setvbuf(stdout, NULL, 2, 0);
}

void debug() {
  printf("Welcome to debug mode!\n");
  system("/bin/sh");
}

void prompt(const char* text) {
  printf("%s", text);
  fflush(stdout);
}

void clear_stdin() {
  char c;
  while((c = getchar()) != '\n' && c != EOF);
}

int main() {
  // init();

  size_t size;
  char   buffer[140];

  while(1) {
    prompt("Input size: ");
    scanf("%lu", &size);

    prompt("Input data: ");
    read(0, buffer, size);

    if(strncmp(buffer, "exit", 4) == 0) {
      break;
    }
    // if(strncmp(buffer, "debug", 5) == 0) {
    //   debug();
    // }
    else {
      printf("You said: ");
      fwrite(buffer, size, 1, stdout);
      // fflush(stdout);
    }
  }

  // clear_stdin();
  return 0;
}
