#ifndef GRAPH_LOADER_H
# define GRAPH_LOADER_H

#include <igraph.h>

#define LOAD_ERROR_EXIT_VALUE 1

igraph_t* load_graph(char *path);
void unload_graph(igraph_t *g);

#endif // GRAPH_LOADER_H
