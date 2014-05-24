#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "heap.h"

void assert(bool success, const char *message);
int compare_nodes(const void *a, const void *b);
void test_create(void);
void test_push(void);
void test_pop(void);

void assert(bool success, const char *message) {
    if (!success) {
        fprintf(stderr, "\t[heap] failed: %s\n", message);
        exit(1);
    }
}

int compare_nodes(const void *a, const void *b) {
    return strcmp(a, b);
}

void test_create() {
    struct heap *heap = heap_create(compare_nodes);

    assert(heap->nodes != NULL, "has memory for nodes");
    assert(heap->capacity > 0, "has initial capacity for nodes");
    assert(heap->comparator == compare_nodes, "has a comparator function");
    assert(heap->size == 0, "heap is empty");

    heap_destroy(heap);
}

void test_push() {
    struct heap *heap = heap_create(compare_nodes);

    char *a = "test 1";
    char *b = "test 2";

    assert(heap_push(heap, a), "item pushed");
    assert(heap->size == 1, "incremented size");

    assert(heap_push(heap, b), "item pushed");
    assert(heap->size == 2, "incremented size");

    heap_destroy(heap);
}

void test_pop() {
    struct heap *heap = heap_create(compare_nodes);

    char *a = "test 1";
    char *b = "test 2";

    heap_push(heap, a);
    heap_push(heap, b);

    assert(heap_pop(heap) == b, "item popped");
    assert(heap->size == 1, "decremented size");

    assert(heap_pop(heap) == a, "item popped");
    assert(heap->size == 0, "decremented size");

    assert(heap_pop(heap) == NULL, "popped null when empty");
    assert(heap->size == 0, "size still zero when empty");

    heap_destroy(heap);
}

int main() {
    test_create();
    test_push();

    return 0;
}