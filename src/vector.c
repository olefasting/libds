#include <string.h>
#include "vector.h"

bool vector_resize(struct vector *this, size_t capacity);

/* Allocate memory for a new vector. The memory must be freed with a
 * subsequent call to `vector_destroy`.
 *
 * Returns the vector or null if memory allocation failed.
 */
struct vector *vector_create() {
    struct vector *this = calloc(1, sizeof(struct vector));
    if (!this) {
        return NULL;
    }

    this->items = NULL;
    this->length = 0;
    this->capacity = 0;

    if (vector_resize(this, 16) < 0) {
        vector_destroy(this);
        return NULL;
    }

    return this;
}

/* Deallocate the memory associated with this vector. This does not free the
 * memory for the items in the vector. The caller must free those separately.
 *
 * this - The vector to free.
 *
 * Returns nothing.
 */
void vector_destroy(struct vector *this) {
    this->length = 0;
    this->capacity = 0;
    free(this->items);
    free(this);
}

/* Remove all items from a vector. The items themselves are not freed. The
 * caller must free the data items. The vector does not resize after removing
 * the items. The memory is still allocated for future inserts.
 *
 * this - The vector to clear.
 *
 * Returns nothing.
 */
void vector_clear(struct vector *this) {
    memset(this->items, 0, this->capacity * sizeof(void *));
    this->length = 0;
}

/* Add an item to the end of the vector. Expands the vector's capacity to
 * store the additional data.
 *
 * this - The vector to store the new item.
 * item - The data to append to the list.
 *
 * Returns false if memory allocation failed.
 */
bool vector_push(struct vector *this, void *item) {
    if (this->length == this->capacity) {
        if (!vector_resize(this, this->capacity * 2)) {
            return false;
        }
    }

    this->items[this->length] = item;
    this->length++;

    return true;
}

/* Remove the last item from the list. When used with `push`, the vector can
 * be used as a stack.
 *
 * this - The vector to pop.
 *
 * Returns the last item or null if the list is empty.
 */
void *vector_pop(struct vector *this) {
    if (this->length == 0) {
        return NULL;
    }

    void *item = this->items[this->length - 1];
    this->items[this->length - 1] = NULL;
    this->length--;
    return item;
}

/* Private: Allocate memory to store list item pointers.
 *
 * this     - The list to resize.
 * capacity - The number of items to accomodate in the list.
 *
 * Returns false if memory allocation failed.
 */
bool vector_resize(struct vector *this, size_t capacity) {
    void **items = realloc(this->items, capacity * sizeof(void *));
    if (!items) {
        return false;
    }

    this->items = items;
    this->capacity = capacity;

    return true;
}
