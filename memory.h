#pragma once

void CreateBuffers(size_t inputSize, size_t outputSize);
void DestroyBuffers(void);
void CoppyToInputBuffer (void *data, size_t size);
void CoppyFromOutputBuffer (void *data, size_t size);