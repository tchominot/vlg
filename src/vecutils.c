#include <assert.h>
#include <stdlib.h>

#include "vecutils.h"

igraph_integer_t vecutils_pick_random(const igraph_vector_t *v) {
  long int size = igraph_vector_size(v);
  assert(size > 0);
  long int idx = rand() % igraph_vector_size(v);
  return igraph_vector_e(v, idx);
}
void vecutils_remove_all_occurences(igraph_vector_t *v, igraph_integer_t val) {
  long int size = igraph_vector_size(v);
  long int new_size = 0;
  for (long int i = 0; i < size; i++) {
    igraph_integer_t cur = igraph_vector_e(v, i);
    if (cur != val)
      igraph_vector_set(v, new_size++, cur);
  }
  igraph_vector_resize(v, new_size);
}
