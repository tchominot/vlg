#include <stdio.h>
#include "sweep-core.h"
#include "sweeps.h"
#include "vecutils.h"

void single_sweep(const igraph_t *g, struct graph_data *gd,
                  igraph_integer_t start)
{
  sweep(g, gd, start, NULL, NULL, NULL);
}

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
  start = vecutils_pick_random(&ecc_vids);
  sweep(g, gd, start, NULL, NULL, NULL);
  igraph_vector_destroy(&ecc_vids);
}

igraph_integer_t center_sweep(const igraph_t *g, struct graph_data *gd,
                              igraph_integer_t start)
{
  igraph_vector_t parent;
  igraph_vector_init(&parent, igraph_vcount(g));
  igraph_integer_t center;
  igraph_integer_t ecc = sweep(g, gd, start, &center, NULL, &parent);
  for (igraph_integer_t i = ecc / 2; i-- > 0; )
    center = VECTOR(parent)[center];
  igraph_vector_destroy(&parent);
  return center;
}

igraph_integer_t radius_center_sweep(const igraph_t *g, struct graph_data *gd,
                                     igraph_integer_t start)
{
  igraph_vector_t ecc_vids;
  igraph_vector_init(&ecc_vids, 0);
  sweep(g, gd, start, NULL, &ecc_vids, NULL);
  start = vecutils_pick_random(&ecc_vids);
  igraph_vector_destroy(&ecc_vids);
  return center_sweep(g, gd, start);
}

igraph_integer_t center_radius_sweep(const igraph_t *g, struct graph_data *gd,
                                     igraph_integer_t start)
{
  start = center_sweep(g, gd, start);
  sweep(g, gd, start, &start, NULL, NULL);
  return start;
}

void multiple_sweeps(const igraph_t *g, struct graph_data *gd,
                     igraph_integer_t start, unsigned nb_sweeps)
{
  while (nb_sweeps-- > 0) {
    sweep(g, gd, start, &start, NULL, NULL);
  }
}
