#include<stdio.h>
#include<stdint.h>
#include<assert.h>
#include<string.h>
#include "sunehaks01.h"

#define HEAP_MAX_SIZE 32

static void _swap_(Node *a, Node *b){
	Node t = {a->pn,a->ts,a->torl};

	a->pn = b->pn;
	a->ts = b->ts;
	a->torl = b->torl;

	b->pn = t.pn;
	b->ts = t.ts;
	b->torl = t.torl;	
}

static void _heapify_(Node data[], uint32_t len, uint32_t par){
	assert(len>0 && len<=HEAP_MAX_SIZE && par>0);

	uint32_t child = 2 * par ; 
	while(child<= len && par>0){
		if(child+1<=len)
			if(data[child].ts<=data[child+1].ts)
				++child;
		if(data[par].ts<=data[child].ts)
			
			_swap_(&data[par],&data[child]);
			par = child;
			child = 2 * par;
		
	}
}

static void test_heap(Node data[], uint32_t size){
	for (int i = size; i/2 >=1; --i){
		//printf("%d %d\n", data[i],data[i/2]);
		assert(data[i].ts<=data[i/2].ts);
	}
}

Node heap_node_new(uint32_t plane_no, uint32_t timestamp, uint32_t torl){
	Node node = {plane_no,timestamp,torl};
	return node;
}

Heap heap_new(Node data[], uint32_t len){
	assert(len>0 && len<HEAP_MAX_SIZE);
	Heap heap;
	for(uint32_t par = len/2; par>=1; --par)
		_heapify_(data,len,par);
	heap.size = len;
	memcpy(heap.data,data,(len+1)*sizeof(Node));
	test_heap(heap.data,heap.size);
	return heap;
}


void heap_sort(Heap *heap){
	assert(heap->size>0 && heap->size < HEAP_MAX_SIZE);
	for (int i = heap->size; i >=2; --i)
	{
		_swap_(&heap->data[1],&heap->data[i]);
		_heapify_(heap->data,i-1,1);	
		//printf("%d\n", heap->data[i]);
	}
}

void heap_add(Heap *heap, Node ele){
	assert(heap->size+1 <= HEAP_MAX_SIZE);

	++heap->size;

	//printf("%d %d %d\n", heap->data[heap->size].pn, heap->data[heap->size].ts, heap->data[heap->size].torl);
	heap->data[heap->size].pn = ele.pn;
	heap->data[heap->size].ts = ele.ts;
	heap->data[heap->size].torl = ele.torl;

	//printf("%d %d %d\n", heap->data[heap->size].pn, heap->data[heap->size].ts, heap->data[heap->size].torl);


	
	_heapify_(heap->data,heap->size,1);

	/*for(int i=1;i<=heap.size;i++)
		//assert(data[i].ts == l[5-i].ts);
		printf("%d\n",heap->data[i].ts);
	*/
}

void test_hs(){
	Node data[5] = {{0},{16,1005,0},{11,1410,1},{317,1217,1},{215,1327,0}};

	Heap heap = heap_new(data,4);
	heap_sort(&heap);
	int32_t i;
	Node l[5] = {{0},{16,1005,0},{317,1217,1},{215,1327,0},{11,1410,1}};

	for(i=1;i<5;i++)
		if(heap.data[i].ts>1150){
			printf("%d\t\t%d\t\t",heap.data[i].pn, heap.data[i].ts);
			if(heap.data[i].torl == 0)
				printf("take-off\n");
			else				
				printf("landing\n");
		}

}

void test_add(){
	Node data[5] = {{0},{16,1005,0},{11,1410,1},{317,1217,1},{215,1327,0}};

	Heap heap = heap_new(data,4);

	//Node l[5] = {{0},{16,1005,0},{317,1217,1},{215,1327,0},{11,1410,1}};
	Node ele = {11,1400,0};
	heap_add(&heap,ele);
	test_heap(data, heap.size);

	//printf("%d\n", heap.size);
	printf("heap after insertion of {11,1400,0}:\n");
	for(int i=1;i<=heap.size;i++)
		//assert(data[i].ts == l[5-i].ts);
		printf("%d\n",heap.data[i].ts);
	/*int32_t l[] = {0,80,50,16,9,30};
	for(int i=1;i<=heap.size;i++)
		assert(heap.data[i] == l[i]);
	*/

}

void test_hp(){
	Node data[5] = {{0},{16,1005,0},{11,1410,1},{317,1217,1},{215,1327,0}};

	Heap heap = heap_new(data,4);
	for(int i=1;i<=heap.size;i++)
		//assert(data[i].ts == l[5-i].ts);
		printf("%d\n",heap.data[i].ts);
}

void main(){
	printf("Heap before insertion:\n");
	test_hp();

	test_add();
	printf("Schedule after deleting planes before 11:50\n");
	printf("plane_no    timestamp          action\n");
	test_hs();
}
