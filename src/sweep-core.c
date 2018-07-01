#include <assert.h>

#include "sweep-core.h"

struct bfs_sweep_data {
  igraph_integer_t  dist;
  igraph_integer_t  last;
  igraph_vector_t   *ecc_vids;
  struct graph_data *gd;
};

static igraph_bool_t handler(const igraph_t *g,
                             igraph_integer_t vid,
                             igraph_integer_t pred,
                             igraph_integer_t succ,
                             igraph_integer_t rank,
                             igraph_integer_t dist,
                             void *bsd);
static void remove_all_occurences(igraph_vector_t *v, igraph_integer_t val);

igraph_integer_t sweep(const igraph_t *g, struct graph_data *gd,
                       igraph_integer_t start, igraph_integer_t *out_end,
                       igraph_vector_t *parent, igraph_vector_t *ecc_vids)
{
  // Check inputs and build auxiliary data
  assert(g != NULL);
  assert(gd != NULL);
  struct bfs_sweep_data bsd = {
    .dist = 0,
    .last = start,
    .ecc_vids = ecc_vids,
    .gd = gd
  };
  igraph_integer_t old_max_ecc = gd->max_ecc;
  igraph_integer_t old_min_ecc = gd->min_ecc;

  // Actual sweeping, cf handler function defined below
  igraph_bfs(g, start, NULL, IGRAPH_OUT, 0, NULL, NULL,
             NULL, parent, NULL, NULL, NULL, handler, &bsd);

  // Update diametral_candidates and diametral_vertices as needed
  if (gd->max_ecc > old_max_ecc) {
    igraph_vector_clear(&gd->diametral_vertices);
  }
  if (gd->max_ecc >= old_max_ecc) {
    // Remove start from candidates and add it to known vertices with max ecc
    long int pos;
    remove_all_occurences(&gd->diametral_candidates, start);
    if (!igraph_vector_binsearch(&gd->diametral_vertices, start, &pos))
      igraph_vector_insert(&gd->diametral_vertices, pos, start);
  }

  // Update center vertices as needed
  if (gd->min_ecc < old_min_ecc) {
    igraph_vector_clear(&gd->center_vertices);
  }
  if (gd->min_ecc <= old_min_ecc) {
    long int pos;
    if (!igraph_vector_binsearch(&gd->center_vertices, start, &pos))
      igraph_vector_insert(&gd->center_vertices, pos, start);
  }

  // Outputs
  if (out_end)
    *out_end = bsd.last;
  return bsd.dist;
}

static igraph_bool_t
handler(const igraph_t *g, igraph_integer_t vid, igraph_integer_t pred,
        igraph_integer_t succ, igraph_integer_t rank, igraph_integer_t dist,
        void *bfs_sweep_data)
{
  // Prepare arguments
  (void) g, (void) pred, (void) rank;
  struct bfs_sweep_data *data = bfs_sweep_data;

  // Update current distance in bfs_sweep_data
  igraph_integer_t old_dist = data->dist;
  data->dist = dist; // dist only grows in a bfs, so it is also max_dist

  // Update the list of vids which are at distance ecc(root) from root
  if (data->ecc_vids) {
    if (dist > old_dist)
      igraph_vector_clear(data->ecc_vids);
    igraph_vector_push_back(data->ecc_vids, vid);
  }

  // Update max_ecc and the diametral candidates
  if (dist > data->gd->max_ecc) {
    data->gd->max_ecc = dist;
    igraph_vector_clear(&data->gd->diametral_candidates);
  }
  if (dist == data->gd->max_ecc) {
    igraph_vector_push_back(&data->gd->diametral_candidates, vid);
  }

  if (succ != -1)
    return 0;

  // This is the last node in the traversal, meaning that dist == ecc(root)
  data->last = vid;
  if (dist < data->gd->min_ecc) {
    data->gd->min_ecc = dist;
  }
  if (dist > data->gd->max_ecc) {
    data->gd->max_ecc = dist;
  }
  return 0;
}

static void remove_all_occurences(igraph_vector_t *v, igraph_integer_t val) {
  long int size = igraph_vector_size(v);
  long int new_size = 0;
  for (long int i = 0; i < size; i++) {
    igraph_integer_t cur = igraph_vector_e(v, i);
    if (cur != val)
      igraph_vector_set(v, new_size++, cur);
  }
  igraph_vector_resize(v, new_size);
}
