// 2016 Adam Jesionowski

#include <stdlib.h>
#include <iostream>
#include "CppUTest/TestHarness.h"

extern "C" {
#include "heap.h"
}

#define HEAP_SIZE 32

TEST_GROUP(Heap)
{
	Heap_t* heap;

	void setup()
	{
	    heap = MakeHeap(HEAP_SIZE);
	}

	void teardown()
	{
	    free(heap);
	}

};


TEST(Heap, MakeHeap)
{
	LONGS_EQUAL(heap->Size, HEAP_SIZE);
	LONGS_EQUAL(heap->EndIndex, 0);
}

TEST(Heap, PeekEmpty)
{
	u32 value;
	CHECK_FALSE(HeapPeek(heap, &value));
}

TEST(Heap, PopEmpty)
{
	u32 value;
	CHECK_FALSE(HeapPop(heap, &value));
}

TEST(Heap, Push)
{
	CHECK_TRUE(HeapPush(heap, 0xFEED));

	LONGS_EQUAL(heap->EndIndex, 1);
	LONGS_EQUAL(0xFEED, heap->Array[0]);
}

TEST(Heap, PushPeek)
{
	u32 value;
	HeapPush(heap, 0xDEEF);
	HeapPeek(heap, &value);
	LONGS_EQUAL(0xDEEF, value);
	LONGS_EQUAL(1, heap->EndIndex);
}

TEST(Heap, PushPop)
{
	u32 value;
	HeapPush(heap, 0xFEDE);
	HeapPop(heap, &value);
	LONGS_EQUAL(0xFEDE, value);
	LONGS_EQUAL(0, heap->EndIndex);
}

TEST(Heap, PushZero)
{
	CHECK_FALSE(HeapPush(heap, 0));
}


TEST(Heap, PushMax)
{
	for(u32 i = 1; i <= HEAP_SIZE; i++)
	{
		CHECK_TRUE(HeapPush(heap, i));
	}
	CHECK_FALSE(HeapPush(heap, 33));
}

TEST(Heap, OperatesAsMaxHeap)
{
	u32 value;

	HeapPush(heap, 1);
	HeapPush(heap, 1000);
	HeapPush(heap, 50);
	HeapPush(heap, 500);
	HeapPush(heap, 1500);
	HeapPush(heap, 2500);
	HeapPush(heap, 100);

	HeapPop(heap, &value);
	LONGS_EQUAL(2500, value);
	HeapPop(heap, &value);
	LONGS_EQUAL(1500, value);
	HeapPop(heap, &value);
	LONGS_EQUAL(1000, value);
	HeapPop(heap, &value);
	LONGS_EQUAL(500, value);
	HeapPop(heap, &value);
	LONGS_EQUAL(100, value);
	HeapPop(heap, &value);
	LONGS_EQUAL(50, value);
	HeapPop(heap, &value);
	LONGS_EQUAL(1, value);
}
