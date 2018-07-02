#ifndef SWEEPS_H
# define SWEEPS_H

# include <igraph.h>
# include "graph-data.h"

/*
** Performs a single sweep from the vertex "start" on the graph g.
** The sweep updates the data in gd, see sweep-core.h for more details.
*/
void single_sweep(const igraph_t *g, struct graph_data *gd,
                  igraph_integer_t start);

/*
** Performs a double sweep from the vertex "start" on the graph g.
** The second sweeps starts from the first's last visited vertex.
** Each sweep updates the data in gd, see sweep-core.h for more details.
*/
void double_sweep_simple(const igraph_t *g, struct graph_data *gd,
                         igraph_integer_t start);

/*
** Performs a double sweep from the vertex "start" on the graph g.
** The second sweep's starting vertex is chosen randomly among vertices in the
** eccentricity of "start", i.e vertices at the furthest distance from the
** start. Each sweep updates the data in gd, see sweep-core.h for more details.
*/
void double_sweep_random(const igraph_t *g, struct graph_data *gd,
                         igraph_integer_t start);

/*
** Performs a single sweep from the vertex "start" on the graph g and then
** finds the vertex in the middle of the spanning tree (specifically in the
** middle of the branch on which the last visited vertex is). If the starting
** vertex is a diametral one, then this finds a vertex of the center.
**
** Returns the vertex found in the middle of the spanning tree.
**
** This function's main purpose is to find a center vertex. To do so, it
** requires a diametral point (the chance of the returned vertex to be in
** the center is proportionnal to the confidence that the starting vertex
** is diametral). The sweep also updates the data in gd, see sweep-core.h
** for more details.
*/
igraph_integer_t center_sweep(const igraph_t *g, struct graph_data *gd,
                              igraph_integer_t start);

/*
** Performs a single sweep followed by a center_sweep.
**
** The first sweep is meant to lower min_ecc (if started from the center).
** The second sweep starts from a random vertex from the eccentricity of the
** starting one and picks up the center of its spanning tree to return.
** Each sweep updates the data in gd, see sweep-core.h for more details.
**
** Intended usage: start from a center vertex and chain the returned vertex
**                 (hopefully a center vertex) into another sweep.
*/
igraph_integer_t radius_center_sweep(const igraph_t *g, struct graph_data *gd,
                                     igraph_integer_t start);

/*
** Performs a center_sweep followed by a single sweep.
**
** This kind of double sweep is meant to be started from a diametral candidate.
** The first sweep improves the approximation for max_ecc and finds a potential
** center vertex while the second one (in)validates the center vertex and
** improves min_ecc.
** Each sweep updates the data in gd, see sweep-core.h for more details.
*/
igraph_integer_t center_radius_sweep(const igraph_t *g, struct graph_data *gd,
                                     igraph_integer_t start);


/*
** Like double_sweep_simple but with an arbitrary number of sweeps.
** Performs nb_sweeps sweeps in a row on the graph g.
** Each sweep starts from the last visited vertex of the previous one.
** Each sweep updates the data in gd, see sweep-core.h for more details.
*/
void multiple_sweeps(const igraph_t *g, struct graph_data *gd,
                     igraph_integer_t start, unsigned nb_sweeps);

#endif // SWEEPS_H
