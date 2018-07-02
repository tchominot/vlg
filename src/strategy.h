#ifndef STRATEGY_H
# define STRATEGY_H

# include <igraph.h>
# include "graph-data.h"

enum strategy {
  STRAT_NONE,
  STRAT_CLASSIC,
  STRAT_CENTER_CHAIN,
  STRAT_BALANCED
};

void strat_classic(igraph_t *g, struct graph_data *gd, igraph_integer_t start);
void strat_center_chain(igraph_t *g, struct graph_data *gd, igraph_integer_t start);
void strat_balanced(igraph_t *g, struct graph_data *gd, igraph_integer_t start);

enum strategy parse_strat(const char *str);

#endif // STRATEGY_H
