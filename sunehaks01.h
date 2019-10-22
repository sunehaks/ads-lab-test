#ifndef _INCLUDED_HEAP_
#define _INCLUDED_HEAP_

#include<stdint.h>
#include<assert.h>

#define HEAP_MAX_SIZE 32

typedef struct _heap_ Heap;
typedef struct _node_ Node;

struct _node_{
	uint32_t pn; // pn = plane_no
	uint32_t ts; // ts = timestamp
	uint32_t torl; // takeoff = 0, landing = 1
};

struct _heap_
{
	uint32_t size;
	Node data[HEAP_MAX_SIZE];
};


Heap heap_new(Node data[], uint32_t len);
Node heap_node_new(uint32_t plane_no, uint32_t timestamp, uint32_t torl);
void heap_add(Heap *heap, Node ele);
void heap_sort(Heap *heap);

#endif