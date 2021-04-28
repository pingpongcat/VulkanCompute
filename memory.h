#pragma once

#include <stddef.h>

void CreateBuffers(size_t inputSize, size_t outputSize);
void DestroyBuffers(void);
void CopyToInputBuffer (void *data, size_t size);
void CopyFromOutputBuffer (void *data, size_t size);