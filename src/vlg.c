#include <igraph.h>
#include <stdio.h>
#include <stdlib.h>

#include "graph_data.h"
#include "graph_loader.h"
#include "preprocess.h"
#include "strategy.h"
#include "vecutils.h"

#ifndef NDEBUG
# define PSEP (fprintf(stderr, "\n"))
# define PDONE (fprintf(stderr, "OK\n"))
# define PSTRAT(st) (fprintf(stderr, "Starting strategy: %s:\n", st))
# define PTASK(task) (fprintf(stderr, "%s: ", task))
#else
# define PSEP ((void)0)
# define PDONE ((void)0)
# define PSTRAT(st) ((void)0)
# define PTASK(task) ((void)0)
#endif

static void print_results(struct graph_data *gd);

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("USAGE: ./vlg GRAPH_FILE");
    return 1;
  }

  PTASK("Loading graph");
  igraph_t *g = load_graph(argv[1]);
  if (!g) {
    return 2;
  }
  PDONE;

  PTASK("Finding the main cluster");
  igraph_vector_t vids = main_cluster_vids(g);
  PDONE;

  igraph_integer_t start_vid = vecutils_pick_random(&vids);

  struct graph_data gd;
  init_graph_data(g, &gd);

  PSTRAT("classic");
  strat_classic(g, &gd, start_vid);
  PDONE;

/*igraph_integer_t cent_v = approximate_radius(g, &gd, diam_v);
  approximate_diameter(g, &gd, cent_v, 2);
  fill_center_vertices(g, &gd, cent_v);*/

  print_results(&gd);

  destroy_graph_data(&gd);
  igraph_vector_destroy(&vids);

  unload_graph(g);
  return 0;
}

static void print_results(struct graph_data *gd) {
  PSEP;
  printf("Diameter: %d ~ %d\n", gd->max_ecc, 2 * gd->min_ecc);
  printf("Radius  : <= %d\n", gd->min_ecc);

  printf("Center  :");
  long int size = igraph_vector_size(&gd->center_vertices);
  for (long int i = 0; i < size; i++)
    printf(" %d", (int) VECTOR(gd->center_vertices)[i]);
  printf("\n");
}
