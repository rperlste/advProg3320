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

#include "pa2functions.h"

int main( int argc, const char* argv[] ){
    Matrix<int>*                matrix = NULL;
    pa2functions::VertexMap     vertexMap;
    unsigned                    edgeCount = 0;

    pa2functions::PrintGreeting();
    if( !pa2functions::ParseFileForMatrix(  argc, 
                                            argv[1], 
                                            matrix, 
                                            vertexMap, 
                                            edgeCount )){      
        std::cout << (*matrix);
        do{
            pa2functions::FindShortestPath(    matrix, 
                                               vertexMap, 
                                               edgeCount );
        } while( pa2functions::ContinueSP() );
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}