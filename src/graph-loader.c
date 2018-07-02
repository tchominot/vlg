#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph-loader.h"

#define READER_BUFSIZE 1024

static int read_graph(FILE *in, igraph_t *out);

igraph_t* load_graph(char *path) {
  // allocate space for graph structure
  igraph_t *graph = malloc(sizeof(igraph_t));
  if (!graph) { // malloc failed
    perror("load_graph: malloc");
    return NULL;
  }

  // open graph file for reading
  FILE *in = fopen(path, "r");
  if (!in) { // open failed
    fprintf(stderr, "load_graph: cannot fopen %s: %s\n", path, strerror(errno));
    free(graph);
    return NULL;
  }

  // read file's content into graph
  int read_ret = read_graph(in, graph);
  fclose(in);
  if (read_ret != IGRAPH_SUCCESS) { // read_graph failed
    const char *err = igraph_strerror(read_ret);
    fprintf(stderr, "load_graph: error reading graph from %s: %s\n", path, err);
    free(graph);
    return NULL;
  }
  return graph;
}

void unload_graph(igraph_t *g) {
  igraph_destroy(g);
  free(g);
}

static int read_graph(FILE *in, igraph_t *out) {
  // read number of nodes
  unsigned long nodes;
  if (fscanf(in, "%lu\n", &nodes) != 1)
    return IGRAPH_PARSEERROR;

  // skip node degrees lines
  char buf[READER_BUFSIZE];
  unsigned long i = 0;
  size_t nr = 0; // nb of characters put in the buffer by the last fread call
  size_t k = 0;  // offset in the buffer
  while (i < nodes) {
    nr = fread(buf, 1, READER_BUFSIZE, in);
    if (!nr) {
      fprintf(stderr, "read_graph: unexpected EOF\n");
      return IGRAPH_PARSEERROR;
    }
    for (k = 0; k < nr && i < nodes; k++) {
      if (buf[k] == '\n')
        i += 1;
    }
  }
  fseek(in, - (nr - k), SEEK_CUR);

  // read edges
  return igraph_read_graph_edgelist(out, in, nodes, 0); // 0 for undirected
}
