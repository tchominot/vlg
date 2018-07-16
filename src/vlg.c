#include <igraph.h>
#include <stdio.h>
#include <stdlib.h>

#include "graph-data.h"
#include "graph-loader.h"
#include "preprocess.h"
#include "strategy.h"
#include "vecutils.h"

#ifndef NDEBUG
# define PSEP        (fprintf(stderr, "\n"))
# define PDONE       (fprintf(stderr, "OK\n"))
# define PSWEEPS     (fprintf(stderr, "Sweeps:\n"))
# define PTASK(task) (fprintf(stderr, "%s: ", task))
#else
# define PSEP        ((void)0)
# define PDONE       ((void)0)
# define PSWEEPS     ((void)0)
# define PTASK(task) ((void)0)
#endif

static void print_results(struct graph_data *gd);
static void print_vector(const igraph_vector_t *v);
static void print_usage();

int main(int argc, char *argv[]) {
  if (argc != 3) {
    print_usage();
    return 1;
  }

  enum strategy strat = parse_strat(argv[1]);
  if (strat == STRAT_NONE) {
    fprintf(stderr, "%s is not a valid strategy.\n", argv[1]);
    print_usage();
    return 1;
  }

  PSEP;
  PTASK("Loading graph");
  igraph_t *g = load_graph(argv[2]);
  if (!g) {
    return 2;
  }
  PDONE;

  PTASK("Finding the main cluster");
  igraph_vector_t vids = main_cluster_vids(g);
  PDONE;

  struct graph_data gd;
  init_graph_data(g, &gd);

  igraph_integer_t start_vid = vecutils_pick_random(&vids);

  PSWEEPS;
  switch (strat) {
    case STRAT_CLASSIC:
      strat_classic(g, &gd, start_vid);
      break;
    case STRAT_CENTER_CHAIN:
      strat_center_chain(g, &gd, start_vid);
      break;
    case STRAT_BALANCED:
      strat_balanced(g, &gd, start_vid);
      break;
    default:
      return 3;
  }
  PDONE;

  vecutils_sort_unique(&gd.diametral_candidates);
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

  printf("Center  : ");
  print_vector(&gd->center_vertices);

  printf("\nDiametral vertices:\n");
  printf("  Known maximum eccentricity vertices    : ");
  print_vector(&gd->max_ecc_vids);
  printf("  Number of diametral vertices candidates: %ld\n",
      igraph_vector_size(&gd->diametral_candidates));
}

static void print_vector(const igraph_vector_t *v) {
  long int size = igraph_vector_size(v);
  if (size <= 0) {
    printf("(empty)\n");
    return;
  }
  printf("%ld", (long int) igraph_vector_e(v, 0));
  for (long int i = 1; i < size; i++)
    printf(", %ld", (long int) igraph_vector_e(v, i));
  printf("\n");
}

static void print_usage() {
  fprintf(stderr, "USAGE: ./vlg STRATEGY GRAPH_FILE\n");
  fprintf(stderr, "   - STRATEGY: classic | center_chain | balanced\n");
}
