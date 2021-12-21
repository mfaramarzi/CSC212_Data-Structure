#include <iostream>
#include <fstream>
using namespace std;

class Cellgrid {
    private:
        // dimensions of the grid, think rowCount, columnCount
        int rows, cols;
        // grid will store the actual grid in 1D space
        bool *grid;
    public:
        /* Class constructors and destructors */
        // class constructor using a file
        Cellgrid(const char *fname, int m, int n);
        // class destructor
        ~Cellgrid();
        /* Member functions */
        // count the number of cells in grid
        int countCells(int row, int col, int conn);
        // counts the number of blobs in grid
        int countBlobs(int conn);
        // prints the Cellgrid in 2D format
        void print();
};




// reads a file containing 1's and 0's and the dimesnsions to expect and
// creates a Cellgrid object
Cellgrid::Cellgrid(const char *fname, int m, int n) {
    // assign row and col counters
    rows = m;
    cols = n;

    // create the grid on the heap, this will have to be deallocated later in
    // the destructor
    grid = new bool[rows*cols];

    // create a file reader stream to read data from a file
    ifstream infile;

    // open a stream to the given file
    infile.open(fname);

    // we are using row-major order in order to store this grid in 1D
    // instead of accessing grid like grid[a][b], we instead do:
    // grid[(a * number of columns) + b]
    for(int i = 0; i < rows; i++) {
        // calculate "(a * number of columns)" from above
        // in order to save some unnecessary computation
        int base = i * cols;
        for(int offset = 0; offset < cols; offset++) {
            // read data from filestream and store it in grid
            infile >> grid[base + offset];
        }
    }

    // close the filestream once we are done with it
    infile.close();
}

// destruct object where not implicit to the program
Cellgrid::~Cellgrid() {
    // since we allocated memory on the heap, we must deallocate that memory
    delete[] grid;
}

// this is the function call which will be made by the autograder to test
// your implementation for problem 1. (row, col) is the "start point" for
// counting the cells, conn is the type of connection to consider (4 or 8).
int Cellgrid::countCells(int row, int col, int conn) {
  
//   base case/ we are trying to find bad celss/ doing the base case based on that

if ( row <= 0 || col <= 0 || row > rows || col > cols || grid [ ( (row - 1) * cols ) + (col - 1)] == false){

    return 0;
}

else {
    if ( conn == 4){

        grid [( (row - 1) * cols ) + (col - 1)] = 0; //row major order

        return 1 + countCells(row - 1 , col, conn) + countCells(row + 1 , col , conn) + countCells( row , col - 1 , conn) + countCells( row , col + 1 , conn);

    }

    else if (conn == 8){

         grid [( (row - 1) * cols ) + (col - 1)] = 0;

        return 1 + countCells(row - 1 , col, conn) + countCells(row + 1 , col , conn) + countCells( row , col - 1 , conn) + countCells( row , col + 1 , conn) + countCells( row - 1 , col - 1 , conn)
        + countCells( row - 1 , col + 1 , conn) + countCells( row + 1, col - 1 , conn) + countCells( row +1 , col + 1 , conn);

    }


}

    return 0;
}

// this is the funciton call which will be made by the autograder to test
// your implementation for problem 2. conn is the type of connection
// to consider (4 or 8).
int Cellgrid::countBlobs(int conn) {
/*
we start from the first cell to the end, to find an alive cell.
if a cell is alive, we increase the value of count++
then we call the countcell func to kill all cells
then we continue looking for alive cells from the same spot
*/

int count = 0;

for (int i = 0 ; i <= rows * cols ; i++){

    // base case/ if we reach to the last cell, return count


    if (i == rows * cols ){

        return(count);
    }

    else{

        if (conn == 4){

            if (grid[i] == 1){

                count++; //adding 1 to the number of blobs

                countCells(i/cols + 1 , i%cols + 1 , conn); //killing all cells in the blob
            }
// std::cout<<count;

    }

    else if (conn == 8){

        if (grid[i] == 1){

                count++; //adding 1 to the number of blobs

                countCells(i/cols + 1 , i%cols + 1, conn); //killing all cells in the blob/finding row and col as argument of countcells, using i, rows and cols
            }
// std::cout<<count;
    }
    }

    
}
}

// this function prints your cellgrid in 2D format without trailing
// whitespace. Use this function to aid in debugging if you wish
void Cellgrid::print() {
    for(int i = 0; i < rows; i++) {
        int base = i * cols;
        std::cout << grid[base];
        for(int offset = 1; offset < cols; offset++) {
            std::cout << ' ' << grid[base + offset];
        }
        std::cout << std::endl;
    }
}


#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    // declare variables
    int M,N,row, col, conn;

    // get .txt file containing the grid
    char *fname = argv[1];

    // convert argument strings to integers
    // don't worry about how this works, we'll
    // cover it later in the course
    M = atoi(argv[2]);
    N = atoi(argv[3]);
    row = atoi(argv[4]);
    col = atoi(argv[5]);
    conn = atoi(argv[6]);

    // create a Cellgrid object
    Cellgrid myGrid(fname, M, N);

    // example test call for problem #1
    cout << myGrid.countCells(row, col, conn) << endl;

    return 0;
}