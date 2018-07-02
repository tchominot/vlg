#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strategy.h"
#include "sweeps.h"
#include "pick-point.h"

#ifndef NDEBUG
# define PDONE (fprintf(stderr, "OK\n"))
# define PSWEEP(swp, vid) (fprintf(stderr, "  %s from %d: ", swp, vid));
#else
# define PDONE ((void)0)
# define PSWEEP(swp, vid) ((void)0)
#endif

void strat_classic(igraph_t *g, struct graph_data *gd, igraph_integer_t start) {
  PSWEEP("multiple sweeps (3)", start);
  multiple_sweeps(g, gd, start, 3);
  PDONE;

  for (unsigned i = 0; i < 2; i++) {
    start = pick_random_diametral_vid(gd);
    PSWEEP(  "center_radius sweep", start);
    center_radius_sweep(g, gd, start);
    PDONE;
  }
}

void strat_center_chain(igraph_t *g, struct graph_data *gd, igraph_integer_t start) {
  PSWEEP("initial double sweep (random)", start);
  double_sweep_random(g, gd, start);
  PDONE;

  start = pick_random_diametral_vid(gd);
  PSWEEP("center sweep", start);
  start = center_sweep(g, gd, start);
  PDONE;

  for (unsigned i = 0; i < 2; i++) {
    PSWEEP("radius_center (double) sweep", start);
    start = radius_center_sweep(g, gd, start);
    PDONE;
  }

  PSWEEP("last (single) sweep for the radius", start);
  single_sweep(g, gd, start);
  PDONE;
}

void strat_balanced(igraph_t *g, struct graph_data *gd, igraph_integer_t start) {
  PSWEEP("double sweep (simple)", start);
  double_sweep_simple(g, gd, start);
  PDONE;

  for (unsigned i = 0; i < 4; i++) {
    start = pick_random_diametral_vid(gd);
    PSWEEP(  "center_radius sweep", start);
    start = center_radius_sweep(g, gd, start);
    PDONE;
  }
}

enum strategy parse_strat(const char *str) {
  if (!strcmp(str, "classic"))
    return STRAT_CLASSIC;
  if (!strcmp(str, "center_chain"))
    return STRAT_CENTER_CHAIN;
  if (!strcmp(str, "balanced"))
    return STRAT_BALANCED;
  return STRAT_NONE;
}
