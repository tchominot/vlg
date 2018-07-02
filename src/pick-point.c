#include "pick-point.h"
#include "vecutils.h"

igraph_integer_t pick_random_diametral_vid(const struct graph_data *gd) {
  if (igraph_vector_size(&gd->diametral_candidates) > 0)
    return vecutils_pick_random(&gd->diametral_candidates);
  return vecutils_pick_random(&gd->max_ecc_vids);
}
