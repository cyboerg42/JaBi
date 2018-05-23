// Just another brainfuck interpreter - 30_01_2016 - Peter Kowalsky (acheloos)
#include <iostream>
#include <fstream>
#include <string>
#include <stdint.h>
#include <stdlib.h>
using namespace std;

#define DATA_MAX_SIZE 32000 // in byte
#define RAM_SIZE 32000 // in byte

int main (int argc, char *argv[]) {
  char data[DATA_MAX_SIZE];
  char *d;
  d = data;

  char buffer;
  ifstream file(argv[1]);
  if (file.is_open())
  {
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
  
  d = data;
  uint8_t ram[RAM_SIZE];
  uint8_t *r;
  r = ram;

  register uint8_t reg = 0;
  
  do {
    switch (*d) {
      case '+':
        reg++;
        break;
      case '-':
        reg--;
        break;
      case '>':
        (*r) = reg;
        r++;
        reg = (*r);
        break;
      case '<':
        (*r) = reg;
        r--;
        reg = (*r);
        break;
      case '[':
        if ((reg) == 0) {
          while(true) {
            d++;
            if ((*d) == '[') reg++;
            if ((*d) == ']') {
              if (reg == 0) break;
              else reg--;
            }
          }
        }
        break;
      case ']':
        if (reg != 0) {
          (*r) = reg; reg = 0;
	  while(true) {
            d--;
            if ((*d) == ']') reg++;
            if ((*d) == '[') {
              if (reg == 0) {
		reg = (*r);		
		break;
	      }
              else reg--;
            }
          }
        }
        break;
      case '.':
        cout << char(reg);
        break;
      case ',':
        reg = getchar();
        break;
      }
      d++;
  } while ((*d) != EOF);
  return 0;
}
