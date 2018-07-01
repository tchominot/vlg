#include <igraph.h>
#include <stdio.h>
#include <stdlib.h>

#include "graph_data.h"
#include "graph_loader.h"
#include "preprocess.h"
#include "sweeps.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("USAGE: ./vlg GRAPH_FILE");
    return 1;
  }

  igraph_t *g = load_graph(argv[1]);
  if (!g) {
    return 2;
  }

  igraph_vector_t vids = biggest_cluster_vids(g);
  igraph_integer_t start_vid = VECTOR(vids)[rand() % igraph_vector_size(&vids)];

  struct graph_data gd;
  init_graph_data(g, &gd);


  double_sweep_simple(g, &gd, start_vid);
  printf("%d\n", gd.max_ecc);
/*igraph_integer_t cent_v = approximate_radius(g, &gd, diam_v);
  approximate_diameter(g, &gd, cent_v, 2);
  fill_center_vertices(g, &gd, cent_v);*/

  destroy_graph_data(&gd);
  igraph_vector_destroy(&vids);
  unload_graph(g);
  return 0;
}
