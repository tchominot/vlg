#ifndef VECUTILS_H
# define VECUTILS_H

# include <igraph.h>

igraph_integer_t vecutils_pick_random(const igraph_vector_t *v);
void vecutils_remove_all_occurences(igraph_vector_t *v, igraph_integer_t val);

#endif // VECUTILS_H
