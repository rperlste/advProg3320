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
 *    are performed on this object.
 */

#include "pa2functions.h"
void pa2functions::PrintGreeting(){
    std::cout   << "\nThis program computes the shortest path on a graph G=(V,U),"
                << "\nfrom vertices u to v using the properties of an"
                << "\nadjacency matrix and matrix multiplication."
                << "\n\nThe user provides a specifically formatted input"
                << "\nfile that represents the graph by its vertex set"
                << "\nand edge set. Using this data, a specialized"
                << "\ntemplate class, Matrix<int> is initialized, and the"
                << "\noperations required to determine the shortest path"
                << "\nare performed on this object.\n\n";
}
int pa2functions::ParseFileForMatrix(   const int argc,
                                        const char* input, 
                                        Matrix<int>*& matrix,
                                        pa2functions::VertexMap& vertexSet, 
                                        unsigned& edgeCount ){
    // Test for command argument
    if( argc < 2 ){
        std::cerr 
            << "\n\nError: Please pass in a a properly formatted input file."
            << "\n\n";
        return EXIT_FAILURE;
    }

    // Test valid file
    std::fstream fileIn( input );
    if( !fileIn ){
        std::cerr << "\n\nThe input file is invalid.\n\n";
        return EXIT_FAILURE;
    }

    if( matrix != NULL ) delete matrix;
    
    std::string currentLine;
    // Read matrix dimensions
    std::getline( fileIn, currentLine );
    matrix = new Matrix<int>(   atoi(currentLine.c_str()), 
                                atoi(currentLine.c_str()) );

    // Read vertex set
    std::getline( fileIn, currentLine );
    std::string currentVertex;
    int i = 0;
    int matrixOffset = 0;
    while( i < currentLine.length() ){
        currentVertex = "";
        while(     currentLine[i] != ' '  
                && currentLine[i] != '\n' 
                && i < currentLine.length() ){
            currentVertex += currentLine[i];
            ++ i;
        }
        ++ i;
        vertexSet[currentVertex] = matrixOffset;
        ++ matrixOffset;
    }

    // Read edge count
    std::getline( fileIn, currentLine );
    edgeCount = atoi( currentLine.c_str() );

    // Read vertices
    int vertexCount = 0;
    std::string vertexU;
    std::string vertexV;
    while( !fileIn.eof() ){
        std::getline( fileIn, currentLine );
        i = 0;
        vertexU = "";
        vertexV = "";
        while(     i < currentLine.length() 
                && currentLine[i] != ' '){
            vertexU += currentLine[i];
            ++ i;
        }
        if( i == currentLine.length() ){
            std::cerr << "\n\nThe input is an invalid format.\n\n";
            return EXIT_FAILURE;
        }
        ++ i;
        while(     i < currentLine.length() 
                && currentLine[i] != ' '){
            vertexV += currentLine[i];
            ++ i;
        }
        ++ vertexCount;
        if(    vertexSet.find(vertexU) == vertexSet.end()
            || vertexSet.find(vertexV) == vertexSet.end() ){
                std::cerr << "\n\nThe input is an invalid format: Edge(" 
                << vertexU << "," << vertexV << ")\n\n";
                return EXIT_FAILURE;
        }
        (*matrix)[vertexSet[vertexU]][vertexSet[vertexV]] += 1;
        (*matrix)[vertexSet[vertexV]][vertexSet[vertexU]] += 1;
    }

    // Test edge count against input edges
    if( vertexCount != edgeCount ){
        std::cerr << "\n\nThe edge count does not match the edge list.\n\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
bool pa2functions::ContinueSP(){
    char choice = ' ';
    do {
        std::cout << std::string( 80, '-' )
            << "\nWould you like to test any additional vertices?\n\n"
            << "Type 1 for YES, or 0 for NO. Then press enter: ";
        std::cin >> choice;
    } while( choice != '0' && choice != '1' );

    return atoi(&choice);
}
pa2functions::VertexPair 
pa2functions::GetVertUV( pa2functions::VertexMap vertexSet ){
    std::string choice1;
    std::string choice2;
    std::cout << "\n\nChoose vertices from the vertex set: \n{ ";
    for( VertexMapIt it = vertexSet.begin(); it != vertexSet.end(); ++ it ){
        std::cout << (*it).first << " ";
    }
    std::cout << "}";

    // Vertex u
    do{
        std::cout << "\n\nPlease enter a vertex u: ";
        std::cin >> choice1;
    } while ( vertexSet.find( choice1 ) == vertexSet.end() );

    // Vertex v
    do{
        std::cout << "\nPlease enter a vertex v: ";
        std::cin >> choice2;
    } while ( vertexSet.find( choice2 ) == vertexSet.end() ); 
    return VertexPair( choice1, choice2 );
}
void pa2functions::FindShortestPath( const Matrix<int>* matrix,
                                     const pa2functions::VertexMap& vertexSet,
                                     const unsigned& edgeCount ){
    int pathLength = 1;
    VertexPair vertexPair = GetVertUV( vertexSet );
    Matrix<int> spMatrix( (*matrix) );
    if( spMatrix[vertexSet.find( vertexPair.first )->second]
                    [vertexSet.find( vertexPair.second )->second] == 0 ){ 
        do {
            spMatrix = spMatrix * (*matrix);
            ++ pathLength;
        } while(    ( pathLength < edgeCount )
                 && ( spMatrix[vertexSet.find( vertexPair.first )->second]
                        [vertexSet.find( vertexPair.second )->second] == 0 ));
    }
    if( ( spMatrix[vertexSet.find( vertexPair.first )->second]
                        [vertexSet.find( vertexPair.second )->second] == 0 )){
        std::cout << "\nThere is no path from V(" << vertexPair.first
                    << "," << vertexPair.second << ")\n\n";
    } else {
        std::cout    << "\nThe shortest path, p, from V(" << vertexPair.first
                    << "," << vertexPair.second << ") is p = " << pathLength
                    << "\n\nA^" << pathLength << "=\n" << spMatrix;
    }
                
}
