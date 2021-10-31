#include<vector>
#include<iostream>
#include<string>
#include <algorithm>
#include <random>
#include<cstdlib>
#include<fstream> //Write file
#include <utility>// std::pair, std::make_pair

class maze{

    public:

        // data members///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        int row_num, col_num;

        std::string fname;

        std::vector<std::vector<std::pair<std::pair<int , int> , std::pair<int , int>>>> cell_status; //A 2-d vector of pair of pairs type int
        
        // member functions///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        void generateVecPair( std::vector<std::vector<std::pair<std::pair<int , int> , std::pair<int , int>>>> &cell_status);

        void recursion(std::vector<std::vector<std::pair<std::pair<int , int> , std::pair<int , int>>>> &cell_status , int &seed ,  int row_num , int col_num); //getting the initial values for r and c and updating that by passed by refrence

        void WriteFile(std::string fname, std::vector<std::vector<std::pair<std::pair<int , int> , std::pair<int , int>>>> cell_status);
    
};
