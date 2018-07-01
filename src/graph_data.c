#include "graph_data.h"

void init_graph_data(igraph_t *g, struct graph_data *gd) {
  gd->min_ecc = igraph_vcount(g);
  gd->max_ecc = 0;
  igraph_vector_init(&gd->diametral_vertices, 0);
  igraph_vector_init(&gd->diametral_candidates, 0);
  igraph_vector_init(&gd->center_vertices, 0);
}

void destroy_graph_data(struct graph_data *gd) {
  igraph_vector_destroy(&gd->diametral_vertices);
  igraph_vector_destroy(&gd->diametral_candidates);
  igraph_vector_destroy(&gd->center_vertices);
}
