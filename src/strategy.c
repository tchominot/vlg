#include <stdio.h>
#include <stdlib.h>

#include "strategy.h"
#include "sweeps.h"
#include "vecutils.h"

#ifndef NDEBUG
# define PDONE (fprintf(stderr, "OK\n"))
# define PSWEEP(swp, vid) (fprintf(stderr, "  %s from %d: ", swp, vid));
#else
# define PDONE ((void)0)
# define PSWEEP(swp, vid) ((void)0)
#endif

void strat_classic(igraph_t *g, struct graph_data *gd, igraph_integer_t start) {
  PSWEEP("triple sweep", start);
  multiple_sweeps(g, gd, start, 3);
  PDONE;

  for (unsigned i = 0; i < 2; i++) {
    start = vecutils_pick_random(&gd->diametral_candidates);

    PSWEEP(  "center_radius sweep", start);
    center_radius_sweep(g, gd, start);
    PDONE;
  }
}
