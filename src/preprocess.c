#include "preprocess.h"

igraph_vector_t main_cluster_vids(igraph_t *g) {
  igraph_vector_t cluster_vids, csize, membership;
  igraph_vector_init(&cluster_vids, 0);
  igraph_vector_init(&csize, 0);
  igraph_vector_init(&membership, igraph_vcount(g));

  igraph_clusters(g, &membership, &csize, NULL, IGRAPH_WEAK);
  int big_cluster_id = igraph_vector_which_max(&csize);
  for (long int i = 0; i < igraph_vector_size(&membership); i++) {
    if ((int) VECTOR(membership)[i] == big_cluster_id) {
      igraph_vector_push_back(&cluster_vids, i);
    }
  }

  igraph_vector_destroy(&csize);
  igraph_vector_destroy(&membership);
  return cluster_vids;
}
