#include <stdlib.h>
#include <unistd.h>

void *mem_init() { sbrk(0); }
void *malloc(size_t size) {
  // Request from the OS size bytes
  // Return a pointer to those bytes
  // Keep track of fragments that are free
}

void free(void *ptr) {
  // Mark heap data as free
}
