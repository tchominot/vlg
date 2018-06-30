#include <alloca.h>
#include <assert.h>
#include <stdio.h>

#include "diameter.h"

struct bfs_diam_data {
  unsigned i;
  unsigned n_iter;
  igraph_integer_t root;
  struct graph_data *gd;
};

static igraph_bool_t handler(const igraph_t *g,
                             igraph_integer_t vid,
                             igraph_integer_t pred,
                             igraph_integer_t succ,
                             igraph_integer_t rank,
                             igraph_integer_t dist,
                             void *bdd);

igraph_integer_t approximate_diameter(const igraph_t *g, struct graph_data *gd,
                                      igraph_integer_t root, unsigned n_iter) {
  assert(g != NULL);
  assert(gd != NULL);
  struct bfs_diam_data bdd = { .i = 0, .n_iter = n_iter, .root = root, .gd = gd };
  for (; bdd.i < n_iter; bdd.i++) {
    igraph_bfs(g, bdd.root, NULL, IGRAPH_OUT, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, handler, &bdd);
  }
  return bdd.root; // the last visited node
}

static igraph_bool_t
handler(const igraph_t *g, igraph_integer_t vid, igraph_integer_t pred,
        igraph_integer_t succ, igraph_integer_t rank, igraph_integer_t dist,
        void *bdd) {
  (void) g, (void) pred, (void) rank;
  struct bfs_diam_data *data = bdd;
  if (succ != -1)
    return 0;

  // This is the last node in the traversal, meaning that dist == ecc(root)
  data->root = vid; // start from here for the next traversal
  if (dist < data->gd->min_ecc) {
    data->gd->min_ecc = dist;
  }
  if (dist > data->gd->max_ecc) {
    data->gd->max_ecc = dist;
  }
  return 0;
}
