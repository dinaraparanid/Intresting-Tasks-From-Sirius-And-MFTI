#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#define SWAP(A, B) A += B; B = A - B; A -= B

typedef struct deque
{
	int* container;
	size_t size;
} deque;

inline size_t size(const deque* x){
	return x->size;
}

inline int empty(const deque* x){
	return x->size == 0;
}

inline int front(const deque* x){
	return *x->container;
}

inline int back(const deque* x){
	return x->container[x->size - 1];
}

inline int get(const deque* x, const int index)
{
	assert(index < x->size);
	return x->container[index];
}

void push_back(deque *x, const int value)
{
	x->container = (int*)realloc(x->container, ++x->size * sizeof(int));
	assert(x->container != NULL);
	x->container[x->size - 1] = value;
}

int pop_back(deque *x)
{
	assert(x->size > 0);
	const int res = x->container[x->size - 1];
	
	x->container = (int*)realloc(x->container, --x->size * sizeof(int));
	assert(x->container != NULL);
	return res;
}

void push_front(deque *x, const int value)
{
	x->container = (int*)realloc(x->container, ++x->size * sizeof(int));
	assert(x->container != NULL);
	x->container[x->size - 1] = value;
	
	for (size_t i = x->size - 1; i > 0; i--){
		SWAP(x->container[i], x->container[i - 1]);
	}
	
}

int pop_front(deque *x)
{
	assert(x->size > 0);
	const int res = *(x->container);
	
	for (size_t i = 0; i < x->size - 1; i++){
		SWAP(x->container[i], x->container[i + 1]);
	}
	
	x->container = (int*)realloc(x->container, --x->size * sizeof(int));
	assert(x->container != NULL);
	return res;
}

void clear(deque *x)
{
	x->size = 0;
	x->container = (int*)realloc(x->container, 0);
	assert(x->container != NULL);
}

void insert(deque *x, const size_t index, const int value)
{
	x->container = (int*)realloc(x->container, ++x->size * sizeof(int));
	assert(x->container != NULL);
	x->container[x->size - 1] = value;
	
	for (size_t i = x->size - 1; i > index; i--){
		SWAP(x->container[i], x->container[i - 1]);
	}
}

int erase(deque* x, const size_t index)
{
	assert(x->size > index);
	const int res = x->container[index];
	
	for (int i = index; i < x->size; i++){
		SWAP(x->container[i], x->container[i + 1]);
	}
	
	x->container = (int*)realloc(x->container, --x->size * sizeof(int));
	assert(x->container != NULL);
	return res;
}

void resize(deque* x, const size_t new_size, const int value)
{
	if (new_size == x->size) return;
	x->container = (int*)realloc(x->container, new_size * sizeof(int));
	assert(x->container != NULL);
	
	if (new_size > x->size)
		for (size_t i = x->size; i < new_size; i++)
			x->container[i] = value;
	
	x->size = new_size;
}
