#include "preprocess.h"

static void keep_biggest_cluster(igraph_t *g);

void preprocess_graph(igraph_t *g) {
  keep_biggest_cluster(g);
}

static void keep_biggest_cluster(igraph_t *g) {
  igraph_vector_t membership, csize, to_remove;
  igraph_vector_init(&membership, igraph_vcount(g));
  igraph_vector_init(&csize, 0);
  igraph_vector_init(&to_remove, 0);

  igraph_clusters(g, &membership, &csize, NULL, IGRAPH_WEAK);
  int big_cluster_id = igraph_vector_which_max(&csize);
  for (long int i = 0; i < igraph_vector_size(&membership); i++) {
    if ((int) VECTOR(membership)[i] != big_cluster_id) {
      igraph_vector_push_back(&to_remove, i);
    }
  }
  igraph_delete_vertices(g, igraph_vss_vector(&to_remove));

  igraph_vector_destroy(&to_remove);
  igraph_vector_destroy(&csize);
  igraph_vector_destroy(&membership);
}

// Simplification du graphe a faire :
// regarder tous les sommets de degré 1 connectés a un seul meme noeud et
// en garder qu'un seul a chaque fois (redondant pour les calculs qu'on veut
// faire sinon)
// i.e
// pour chaque noeud n
// si n est de degré 1
// et qu'il existe un noeud de degré 1 à distance 2 de n
// alors supprimer n
