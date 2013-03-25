/*
 *    Robert Perlstein
 *    101130094
 *    Advanced Programming
 *    Spring 2013
 *    HW2 - Matrices, Template Specialization, and Shortest Path 
 *    
 *    This program computes the shortest path on a graph G=(V,U),
 *    from vertices u to v using the properties of an
 *    adjacency matrix and matrix multiplication.
 *    The user provides a specifically formatted input
 *    file that represents the graph by its vertex set,
 *    and edge set. Using this data, a specialized
 *    template class, Matrix<int> is initialized, and the
 *    operations required to determine the shortest path
 *    are performeed on this object.
 */

/********** PRE/POST CONDITIONS ***********************************************

void    PrintGreeting();
PRE:    None
POST:   Prints a program description

int     ParseFileForMatrix(             const int& argc,
                                        const char* input, 
                                        Matrix<int>*& matrix, 
                                        VertexMap& vertexSet, 
                                        unsigned& edgeCount );
PRE:    matrix is assigned to NULL or has already been initialized.
POST:   Reads an input file that follows a specification that provides the
        information about a graph G. This information is parsed, and the
        matrix is loaded with the approriate information.

bool    ContinueSP();
PRE:    matrix was properly initialized
POST:   Prompts user to continue, returns true if yes.

VertexPair    GetVertUV(                 VertexMap vertexMap );
PRE:    vertexMap has contents
POST:   Returns a std::pair<std::string,std::string> that represents
        a pair of vertices from the graph.

void    FindShortestPath(                   const Matrix<int>* matrix, 
                                            const VertexMap& vertexSet,
                                            const unsigned& edgeCount );
PRE:    matrix is initilized
POST:   Prints the shortest path

******************************************************************************/


#ifndef _pa2functions
#define _pa2functions

#include <iostream>
#include <utility>
#include <map>
#include <cstdlib>
#include <fstream>
#include <string>
#include "matrix.h"

namespace pa2functions{
    typedef std::map <std::string, 
                      unsigned>            VertexMap;
    typedef VertexMap::iterator            VertexMapIt;
    typedef std::pair <std::string,
                       std::string>        VertexPair;

    void            PrintGreeting();
    int             ParseFileForMatrix(    const int argc,
                                           const char* input, 
                                           Matrix<int>*& matrix, 
                                           VertexMap& vertexSet, 
                                           unsigned& edgeCount );
    bool            ContinueSP();
    VertexPair      GetVertUV(             VertexMap vertexMap );
    void            FindShortestPath(      const Matrix<int>* matrix, 
                                           const VertexMap& vertexSet,
                                           unsigned edgeCount );
}


#endif