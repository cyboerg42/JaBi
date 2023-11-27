// Just another brainfuck interpreter - 16_10_2019 - Peter Kowalsky (acheloos)
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <stdint.h>
#include <stdlib.h>
using namespace std;

#define DATA_MAX_SIZE 32000 // in byte
#define RAM_SIZE 32000 // in byte
#define FIFO_SITE 256 // in byte

char* jmp_to(int pos, char* d, char data[DATA_MAX_SIZE]){
	d = &data[pos];
	return d;
}

int main (int argc, char *argv[]) {

  char *d;
  char data[DATA_MAX_SIZE];
  d = data;

  ifstream file(argv[1]);
	
  if (file.is_open())
  {
    char buffer;
    while (file.get(buffer))
    {
      *d = buffer;
      d++;
    }
    *d = EOF;
    file.close();
  }
  else {
    cout << "Unable to open file\n";
    return 0;
  }

  uint8_t ram[RAM_SIZE];
  uint8_t *r;
  r = ram;

  register uint8_t reg = 0;

  char* fifo[FIFO_SIZE];
  char **fi;
  fi = fifo;

  d = jmp_to(0, d, data);

  do {
    switch (*d) {
      case '+':
        (*r)++;
        break;
      case '-':
        (*r)--;
        break;
      case '>':
        r++;
        break;
      case '<':
        r--;
        break;
      case '[':
        if ((*r) == 0) {
          while(true) {
            d++;
            if ((*d) == '[') reg++;
            if ((*d) == ']') {
              if (reg == 0) break;
              else reg--;
            }
          }
        }
	else {
          fi++;
	  *fi = d;
	}
        break;
      case ']':
        if ((*r) != 0) {
	  d = *fi;
        }
        else {
          fi--;
        }
        break;
      case '.':
        cout << char(*r);
        std::cout << std::flush;
        break;
      case ',':
        (*r) = getchar();
        break;
      }
      d++;
  } while ((*d) != EOF);
  return 0;
}
