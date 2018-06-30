#ifndef DIAMETER_H
# define DIAMETER_H

# include <igraph.h>
# include "graph_data.h"

igraph_integer_t approximate_diameter(const igraph_t *g, struct graph_data *gd,
                                      igraph_integer_t root, unsigned n_iter);

#endif // DIAMETER_H
