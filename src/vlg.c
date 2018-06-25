#include <igraph.h>
#include <stdio.h>
#include <stdlib.h>

#include "graph_loader.h"
#include "preprocess.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("USAGE: ./vlg FILE");
  }
  igraph_t *g = load_graph(argv[1]);
  preprocess_graph(g);
  // compute diameter
  // compute center and radius using data from diameter computation
  unload_graph(g);
  return 0;
}
