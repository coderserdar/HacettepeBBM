#include <iostream>             // cin,cout,cerr,endl
#include <stdio.h>              // fopen,fclose,fgetc,fscanf,sscanf
#include <stdlib.h>             // exit,EXIT_SUCCESS,EXIT_FAILURE

using namespace std;

#define MAXNODES 30

struct graph_s {
    int nodes;
    int adjacency[MAXNODES][MAXNODES];
};
typedef struct graph_s graph_t;

void read_matrix(FILE *fp, graph_t &g);


int main(int argc, char *argv[])
{
    FILE *fp;
    graph_t graph;
    int vertices[MAXNODES];
    bool visited[MAXNODES];
    int start_vertex, next_vertex;
    int count, index, i;

    if (argc != 3) {
        cerr << "Kullaným: " << argv[0]
             << " matris_dosyasý baþlangýç_düðümü" << endl;
        return EXIT_FAILURE;
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        cerr << "Matris dosyasý açýlamadý." << endl;
        exit(EXIT_FAILURE);
    }
    sscanf(argv[2], "%d", &start_vertex);

    read_matrix(fp, graph);

    for (i = 0; i < graph.nodes; i++)
        visited[i] = false;

    vertices[0] = start_vertex;
    visited[start_vertex] = true;
    count = 1;
    index = 0;
    while ((index < graph.nodes) && (count < graph.nodes)) {
        next_vertex = vertices[index];
        for (i = 0; i < graph.nodes; i++) {
            if ((graph.adjacency[next_vertex][i] == 1)
                 && (!visited[i])) {
                vertices[count] = i;
                visited[i] = true;
                count++;
            }
        }
        index++;
    }

    for (i = 0; i < graph.nodes; i++)
        cout << vertices[i] << endl;

    fclose(fp);
    return EXIT_SUCCESS;
}


void read_matrix(FILE *fp, graph_t &g)
{
    int c;
    int i = 0, j = 0;

    fscanf(fp, "%d\n", &g.nodes);
    while (true) {
        c = fgetc(fp);
        if (c == EOF)
            break;
        if (c == '\n') {
            i++;
            j = 0;
            continue;
        }
        g.adjacency[i][j] = c - '0';
        j++;
    }
}
