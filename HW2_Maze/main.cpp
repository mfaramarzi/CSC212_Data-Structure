// Libraries.......................................................................................................................

#include"maze.h"

// MAIN FUNCTION...............................................................................................................

int main(int argc, char** argv){ //argc = 5 

    // Define variables

    int seed;
    
    maze obj;

    // get command line arguments

    seed = std::stoi(argv[1]);

    obj.row_num = std::stoi (argv[2]);

    obj.col_num = std::stoi (argv[3]);

    obj.fname = argv[4];

    std::srand(seed);


    obj.generateVecPair(obj.cell_status);

    obj.recursion(obj.cell_status , seed ,  obj.row_num , obj.col_num);

    obj.WriteFile(obj.fname, obj.cell_status);
    
}