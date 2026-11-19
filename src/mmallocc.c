#include "mmallocc.h"
#include <errno.h>
#include <signal.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

struct BlockHeader {
  size_t block_size;
};
// Linked list for our free list
// Intrusive free list
struct FreeBlock {
  size_t block_size;
  struct FreeBlock *next_block;
  struct FreeBlock *prev_block;
};

static size_t MINIMUM_BLOCK_SIZE =
    sizeof(size_t) + 2 * sizeof(struct FreeBlock *);

static inline size_t get_usable_block_size(const struct FreeBlock *fb) {
  return fb->block_size - sizeof(fb->block_size);
}

struct FreeBlock *free_head = NULL;

void *mem_init() {
  sbrk(0);
  return NULL;
}

void *malloc(size_t req_size) {
  // Request from the OS size bytes
  // Return a pointer to those bytes
  // Keep track of fragments that are free

  struct FreeBlock *traverse = free_head;
  while (traverse) {
    size_t usable_block_size = get_usable_block_size(traverse);
    if (usable_block_size < req_size)
      continue;

    traverse->block_size = req_size;
    uint8_t *ptr = (uint8_t *)traverse->next_block;
    return ptr;
  }

  // Allocate new memory
  size_t new_block_size = req_size + sizeof(size_t) < MINIMUM_BLOCK_SIZE
                              ? MINIMUM_BLOCK_SIZE
                              : req_size + sizeof(size_t);
  void *new_mem = sbrk(new_block_size);

  return new_mem;
}

void free(void *ptr) {
  // Mark heap data as free
  // What happens if you get a ptr in the middle of the data?
  // If you free starting from the ptr
  // You have a block header thats stale and not correct and probably just
  // completely blank forever
  if (!ptr)
    return;
}
