#pragma once

#include <stddef.h>

void CreateBuffers(size_t inputSize, size_t outputSize, uint32_t inputSizeUin1, uint32_t inputSizeUin2);
void DestroyBuffers(void);
void CopyToInputBuffer (void *data, size_t size);
void CopyFromOutputBuffer (void *data, size_t size);

void CopyToInputBufferUni1(void *data, size_t size);
void CopyToInputBufferUni2(void *data, size_t size);