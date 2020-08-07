#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#define SWAP(A, B) A += B; B = A - B; A -= B

typedef struct _deque
{
	int* container;
	size_t size;
} _deque;

size_t _size(const _deque* x){
	return x->size;
}

int _empty(const _deque* x){
	return x->size == 0;
}

int _front(const _deque* x){
	return *x->container;
}

int _back(const _deque* x){
	return x->container[x->size - 1];
}

void _free(_deque* x){
	free(x->container);
}

int _get(const _deque* x, const int index)
{
	assert(index < x->size);
	return x->container[index];
}

void _push_back(_deque *x, const int value)
{
	x->container = (int*)realloc(x->container, ++x->size * sizeof(int));
	assert(x->container != NULL);
	x->container[x->size - 1] = value;
}

int _pop_back(_deque *x)
{
	assert(x->size > 0);
	const int res = x->container[x->size - 1];
	
	x->container = (int*)realloc(x->container, --x->size * sizeof(int));
	assert(x->container != NULL);
	return res;
}

void _push_front(_deque *x, const int value)
{
	x->container = (int*)realloc(x->container, ++x->size * sizeof(int));
	assert(x->container != NULL);
	x->container[x->size - 1] = value;
	
	for (size_t i = x->size - 1; i > 0; i--){
		SWAP(x->container[i], x->container[i - 1]);
	}
	
}

int _pop_front(_deque *x)
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

void _clear(_deque *x)
{
	x->size = 0;
	x->container = (int*)realloc(x->container, 0);
	assert(x->container != NULL);
}

void _insert(_deque *x, const size_t index, const int value)
{
	x->container = (int*)realloc(x->container, ++x->size * sizeof(int));
	assert(x->container != NULL);
	x->container[x->size - 1] = value;
	
	for (size_t i = x->size - 1; i > index; i--){
		SWAP(x->container[i], x->container[i - 1]);
	}
}

int _erase(_deque* x, const size_t index)
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

void _resize(_deque* x, const size_t new_size, const int value)
{
	if (new_size == x->size) return;
	x->container = (int*)realloc(x->container, new_size * sizeof(int));
	assert(x->container != NULL);
	
	if (new_size > x->size)
		for (size_t i = x->size; i < new_size; i++)
			x->container[i] = value;
	
	x->size = new_size;
}
