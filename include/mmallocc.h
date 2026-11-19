#pragma once
#include <unistd.h>

struct BlockHeader;
struct FreeBlock;

void *mmallocc(size_t req_size);
void *free(void *ptr);
