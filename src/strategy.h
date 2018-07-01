#ifndef STRATEGY_H
# define STRATEGY_H

# include <igraph.h>
# include "graph_data.h"

void strat_classic(igraph_t *g, struct graph_data *gd, igraph_integer_t start);

#endif // STRATEGY_H
