#ifndef SWEEP_CORE_H
# define SWEEP_CORE_H

# include <igraph.h>
# include "graph-data.h"

/*
** Core underlying function to perform a single sweep.
** It performs a bfs (igraph_bfs) and updates the data in gd accordingly.
** All the fields of graph_data are updated to improve the approximation:
**  - the maximum eccentricity is updated if it is found that start's eccentricity is higher
**  - the minimum eccentricity is updated if it is found that start's eccentricity is lower
**  - the lists of vertices (max_ecc_vids, diametral_candidates and central_vertices) are kept up-to-date as well
**
** out_end : if not NULL, the last vertex traversed by the bfs is stored here
** ecc_vids: if not NULL, the vertices in the last level of the bfs are stored in it
**           The function clears it before adding any vertex to it.
** parent  : if not NULL, fill it such that parent[i] contains the vid of the parent of i
** Returns the eccentricity of the start vertex.
*/
igraph_integer_t sweep(const igraph_t *g, struct graph_data *gd,
                       igraph_integer_t start, igraph_integer_t *out_end,
                       igraph_vector_t *ecc_vids, igraph_vector_t *parent);

#endif // SWEEP_CORE_H
