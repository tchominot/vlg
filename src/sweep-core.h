#ifndef SWEEP_CORE_H
# define SWEEP_CORE_H

# include <igraph.h>
# include "graph-data.h"

/*
** TODO: details
*/
igraph_integer_t sweep(const igraph_t *g, struct graph_data *gd,
                       igraph_integer_t start, igraph_integer_t *out_end,
                       igraph_vector_t *ecc_vids, igraph_vector_t *parent);

#endif // SWEEP_CORE_H
