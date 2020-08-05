// Реализация дека на C

#include <stdio.h>
#include <string.h>
#include <malloc.h>

struct deque
{
	int* d;
	size_t size;
};

void push_back(struct deque *x, int value)
{
	(*x).size++;
	(*x).d = (int*)realloc((*x).d, (*x).size * sizeof(int));
	(*x).d[(*x).size - 1] = value;
}

void pop_back(struct deque *x)
{
	if((*x).size == 0)
	{
		puts("error");
		return;
	}
	printf("%d\n",(*x).d[(*x).size - 1]);
	(*x).size--;
	(*x).d = (int*)realloc((*x).d, (*x).size * sizeof(int));
}

void push_front(struct deque *x, int value)
{
	(*x).size++;
	(*x).d = (int*)realloc((*x).d, (*x).size * sizeof(int));
	(*x).d[(*x).size - 1] = value;
	for(unsigned int i = (*x).size - 1; i > 0; i--)
	{
		(*x).d[i] += (*x).d[i - 1];
		(*x).d[i - 1] = (*x).d[i] - (*x).d[i - 1];
		(*x).d[i] -= (*x).d[i - 1];
	}
}

void pop_front(struct deque *x)
{
	if((*x).size == 0)
	{
		puts("error");
		return;
	}
	printf("%d\n",*((*x).d));
	for(int i = 0; i < (*x).size - 1; i++)
	{
		(*x).d[i] += (*x).d[i + 1];
		(*x).d[i + 1] = (*x).d[i] - (*x).d[i + 1];
		(*x).d[i] -= (*x).d[i + 1];
	}
	(*x).size--;
	(*x).d = (int*)realloc((*x).d, (*x).size * sizeof(int));
}

void clear(struct deque *x)
{
	(*x).size = 0;
	(*x).d = (int*)realloc((*x).d, 0);
}

int main()
{
	struct deque s;
	s.size = 0;
	s.d = (int*)malloc(0);
	char command[100];
	do
	{
		scanf("%s", command);
		if(strcmp(command, "exit") == 0) puts("bye");
		else if(strcmp(command, "clear") == 0) clear(&s), puts("ok");
		else if(strcmp(command, "size") == 0) printf("%u\n", s.size);
		else if(strcmp(command, "front") == 0)
			(s).size == 0 ? puts ( "error" ) : printf ( "%d\n", *(s.d) );
		else if(strcmp(command, "back") == 0)
			(s).size == 0 ? puts ( "error" ) : printf("%d\n", s.d[s.size - 1]);
		else if(strcmp(command, "push_back") == 0)
		{
			int n = 0;
			scanf("%d", &n);
			push_back(&s, n);
			puts("ok");
		}
		else if(strcmp(command, "push_front") == 0)
		{
			int n = 0;
			scanf("%d", &n);
			push_front(&s, n);
			puts("ok");
		}
		else if(strcmp(command, "pop_back") == 0) pop_back(&s);
		else pop_front(&s);
	}
	while(strcmp(command, "exit") != 0);
	free(s.d);
	return 0;
}