#include <igraph.h>
#include <stdio.h>
#include <stdlib.h>

#include "graph_data.h"
#include "graph_loader.h"
#include "preprocess.h"
#include "sweeps.h"

#define PTASK(task) (printf("%s: ", task));
#define PDONE (printf("Done\n"));

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

  igraph_integer_t start_vid = VECTOR(vids)[rand() % igraph_vector_size(&vids)];

  struct graph_data gd;
  init_graph_data(g, &gd);

  PTASK("Performing initial double sweep");
  double_sweep_simple(g, &gd, start_vid);
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
  printf("\nResults:\n");
  printf("  Diameter: %d ~ %d\n", gd->max_ecc, 2 * gd->min_ecc);
  printf("  Radius <= %d\n", gd->min_ecc);
  // TODO: print center
}
