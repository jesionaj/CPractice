// 2016 Adam Jesionowski

#ifndef INC_HEAP_H_
#define INC_HEAP_H_

#include <stdbool.h>
#include <stdint.h>

#ifndef u32
	typedef uint32_t u32;
#endif

typedef struct {
	u32  Size;
	u32* Array;
	u32  EndIndex;
} Heap_t;

Heap_t* MakeHeap(u32 size);
bool HeapPeek(Heap_t* heap, u32* value);
bool HeapPush(Heap_t* heap, u32 value);
bool HeapPop(Heap_t* heap, u32* value);

#endif /* INC_HEAP_H_ */
