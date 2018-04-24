#include <igraph.h>
#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

int read_graph(FILE *in, igraph_t *out);

int main(int argc, char *argv[]) {
  igraph_t g;
  FILE *in = fopen(argv[1], "r");
  if (!in)
    return 1;
  if (read_graph(in, &g) != IGRAPH_SUCCESS)
    return 2;
  fclose(in);
  igraph_destroy(&g);
  return 0;
}

int read_graph(FILE *in, igraph_t *out) {
  // read number of nodes
  unsigned long nodes;
  if (fscanf(in, "%lu\n", &nodes) != 1)
    return IGRAPH_PARSEERROR;

  // skip node degrees lines
  char buf[32];
  for (unsigned long i = 0; i < nodes; i++) {
    if (!fgets(buf, 32, in))
      return IGRAPH_PARSEERROR;
  }

  return igraph_read_graph_edgelist(out, in, nodes, 0);
}
