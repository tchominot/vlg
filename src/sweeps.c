#include <stdio.h>
#include <stdlib.h>
#include "sweep-core.h"
#include "sweeps.h"

void double_sweep_simple(const igraph_t *g, struct graph_data *gd,
                         igraph_integer_t start)
{
  sweep(g, gd, start, &start, NULL, NULL);
  sweep(g, gd, start, NULL, NULL, NULL);
}

void double_sweep_random(const igraph_t *g, struct graph_data *gd,
                         igraph_integer_t start)
{
  igraph_vector_t ecc_vids;
  igraph_vector_init(&ecc_vids, 0);
  sweep(g, gd, start, NULL, &ecc_vids, NULL);
  start = VECTOR(ecc_vids)[rand() % igraph_vector_size(&ecc_vids)];
  sweep(g, gd, start, NULL, NULL, NULL);
  igraph_vector_destroy(&ecc_vids);
}

igraph_integer_t center_sweep(const igraph_t *g, struct graph_data *gd,
                              igraph_integer_t start)
{
  igraph_vector_t parent;
  igraph_vector_init(&parent, 0);
  igraph_integer_t center;
  igraph_integer_t ecc = sweep(g, gd, start, &center, NULL, &parent);
  if (ecc < gd->max_ecc) {
    fprintf(stderr, "WARNING: center_sweep: start vertex %d is not diametral (ecc=%d, max=%d)\n",
            start, ecc, gd->max_ecc);
  }
  for (igraph_integer_t i = ecc / 2; i-- > 0; )
    center = VECTOR(parent)[center];
  igraph_vector_destroy(&parent);
  return center;
}

igraph_integer_t double_sweep_radius(const igraph_t *g, struct graph_data *gd,
                                     igraph_integer_t start)
{
  igraph_vector_t ecc_vids;
  igraph_vector_init(&ecc_vids, 0);
  sweep(g, gd, start, NULL, &ecc_vids, NULL);
  start = VECTOR(ecc_vids)[rand() % igraph_vector_size(&ecc_vids)];
  igraph_vector_destroy(&ecc_vids);
  return center_sweep(g, gd, start);
}

void multiple_sweeps(const igraph_t *g, struct graph_data *gd,
                     igraph_integer_t start, unsigned nb_sweeps)
{
  while (nb_sweeps-- > 0) {
    sweep(g, gd, start, &start, NULL, NULL);
  }
}
