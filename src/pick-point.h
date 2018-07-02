#ifndef PICK_POINT_H
# define PICK_POINT_H

# include <igraph.h>
# include "graph-data.h"

/*
** Returns a vertex id which is (hopefully) diametral based on the given data.
** The vertex is taken (randomly) from the candidates or from the max_ecc_vids
** if there are no candidates.
** The behaviour is undefined if both vectors are empty. This should never
** happen as long as at least one sweep has been made before calling this.
** Do not call this function before having done at least 1 sweep with gd.
*/
igraph_integer_t pick_random_diametral_vid(const struct graph_data *gd);

#endif // PICK_POINT_H
