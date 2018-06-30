#ifndef GRAPH_DATA_H
# define GRAPH_DATA_H

# include <igraph.h>

struct graph_data {
  igraph_integer_t min_ecc;
  igraph_integer_t max_ecc;
  igraph_vector_t diametral_points;
  igraph_vector_t center_points;
};

void init_graph_data(igraph_t *g, struct graph_data *gd);
void destroy_graph_data(struct graph_data *gd);

#endif // GRAPH_DATA_H
