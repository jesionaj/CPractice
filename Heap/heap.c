// 2016 Adam Jesionowski

#include <stdlib.h>
#include "heap.h"

#define PARENT(x)  ((x-1) >> 1)
#define L_CHILD(x) (2*x + 1)
#define R_CHILD(x) (2*x + 2)

static void MaxHeapifyDown(Heap_t* heap, u32 index);
static void MaxHeapifyUp(Heap_t* heap, u32 index);

static void ArraySwap(u32* array, u32 firstIdx, u32 secondIdx)
{
	u32 temp = array[firstIdx];
	array[firstIdx] = array[secondIdx];
	array[secondIdx] = temp;
}

Heap_t* MakeHeap(u32 size)
{
	Heap_t* heap = malloc(sizeof(Heap_t));

	heap->Size = size;
	heap->Array = calloc(size, sizeof(u32));
	heap->EndIndex = 0;

	return heap;
}

bool HeapPeek(Heap_t* heap, u32* value)
{
	if(heap->EndIndex == 0)
	{
		return false;
	}

	*value = heap->Array[0];

	return true;
}

bool HeapPush(Heap_t* heap, u32 value)
{
	if(value == 0 || heap->EndIndex == heap->Size)
	{
		return false;
	}

	// Add value to end of array
	heap->Array[heap->EndIndex] = value;

	// Heapify that value upwards
	MaxHeapifyUp(heap, heap->EndIndex);

	// Move end index up
	heap->EndIndex++;

	return true;
}

bool HeapPop(Heap_t* heap, u32* value)
{
	if(heap->EndIndex == 0)
	{
		return false;
	}

	// Set returned value to root node and zero it out
	*value = heap->Array[0];
	heap->Array[0] = 0;

	// Move index pointer back one, pointing at a value
	heap->EndIndex--;

	// Swap that value into the root
	ArraySwap(heap->Array, 0, heap->EndIndex);

	// Heapify and we're done
	MaxHeapifyDown(heap, 0);

	return true;
}

static void MaxHeapifyUp(Heap_t* heap, u32 index)
{
	if(index == 0)
	{
		return;
	}

	// If the parent value is smaller than this value, then we need to move it upwards
	if(heap->Array[PARENT(index)] < heap->Array[index])
	{
		ArraySwap(heap->Array, PARENT(index), index);
		MaxHeapifyUp(heap, PARENT(index));
	}
}

static void MaxHeapifyDown(Heap_t* heap, u32 index)
{
	u32 childIndex;

	// We can't move past the end of the heap
	if(L_CHILD(index) > heap->Size)
	{
		return;
	}

	// Check which child is the larger of the two
	if(heap->Array[L_CHILD(index)] > heap->Array[R_CHILD(index)])
	{
		childIndex = L_CHILD(index);
	}
	else
	{
		childIndex = R_CHILD(index);
	}

	// If the child is larger, swap with that child and heapify down
	if(heap->Array[childIndex] > heap->Array[index])
	{
		ArraySwap(heap->Array, childIndex, index);
		MaxHeapifyDown(heap, childIndex);
	}
}
