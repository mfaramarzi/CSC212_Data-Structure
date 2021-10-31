#include"maze.h"



//Generate a 2-d vector of "pair of pairs of int", with (i,j) coordinate and default values and status
void maze::generateVecPair( std::vector<std::vector<std::pair<std::pair<int , int> , std::pair<int , int>>>> &cell_status) {

for (int i = 0 ; i <row_num ; i ++){

    std::vector<std::pair<std::pair<int , int> , std::pair<int , int>>>temp_vec; //temp vector for each row

    for (int j = 0 ; j <col_num ; j++){

        std::pair<std::pair<int , int> , std::pair<int , int>> temp_pair; //tempr pair of pair for each element

        temp_pair.first = std::make_pair(i , j);//assigning coordinates to all cells of vec_pair

        temp_pair.second = std::make_pair(15 , 0);//assigning default value 15 and not visited status to all cells of vec_pair

        temp_vec.push_back(temp_pair);//pusshing back the pair of pairs of each cell to the 1-d vector of each row
        }

    cell_status.push_back(temp_vec);
}
cell_status[0][0].second.first -= 8; //start cell default value

cell_status[0][0].second.second = 1; //start cell visited

cell_status[row_num - 1][col_num - 1].second.first -= 4; //end cell default value
}



void maze::recursion(std::vector<std::vector<std::pair<std::pair<int , int> , std::pair<int , int>>>> &cell_status , int &seed ,  int row_num , int col_num) {//getting the initial values for r and c and updating that by passed by refrence

        int row = 0;//One time initialization of row and col

        int col = 0;

        std::vector<std::pair<int , int>> visited; // VECTOR "A" IN HW DESCRIPTION // a vector of pairs of visited cells (kindda?????)

        std::pair<int , int> current; // A pair object name "current" for the (i , j) of current cell

        visited.push_back(cell_status[0][0].first); // inserting (0 , 0) at the end of "visited",


        while(visited.size() > 0){ // while loop to check if visited.size > 0;

            std::pair<int , int> sel_neigh;  // A pair object name "sel_neigh" Selected randomly (will be passed by reference to the direction func)

            std::vector<std::pair<int , int>> neighbors; // a vector of pairs of current neighbors not visited yet (will be passed by reference to the direction func)!!!!!!!!!!!!

            current = visited.back(); // removing last element from "visited" and assigning to "current"

            visited.pop_back();

            row = current.first; //row index of current cell

            col = current.second; //col index of current cell

            if(row - 1 >= 0){//checking top cell is not out of box

                if(cell_status[row - 1][col].second.second == 0){

                    neighbors.push_back(cell_status[row - 1][col].first);
                }
            }
            
            if(row + 1 <= row_num - 1 ){//checking down cell is not out of box

                if(cell_status[row + 1][col].second.second == 0){

                    neighbors.push_back(cell_status[row + 1][col].first);
                }
            }

              if(col + 1 <= col_num - 1){//checking right cell is not out of box

                if(cell_status[row][col + 1].second.second == 0){

                    neighbors.push_back(cell_status[row][col + 1].first);
                }
            }

            if(col - 1 >= 0){//checking left cell is not out of box

                if(cell_status[row][col - 1].second.second == 0){

                    neighbors.push_back(cell_status[row][col - 1].first);
                }
            }

          

            if(neighbors.size() > 0){


                visited.push_back(current);

                int idx = std::rand() / ((RAND_MAX + 1u) / neighbors.size());

                sel_neigh = neighbors[idx];

                char dir;

                if (sel_neigh.first> row){

                    dir = 'S';
                }

                else if (sel_neigh.first < row){

                    dir = 'N';
                }

                else if (sel_neigh.second > col){

                    dir = 'E';
                }

                else if (sel_neigh.second < col){

                    dir = 'W';
                }
                

                
                switch(dir){ //IT SHOULD NOT BE THE INDEX,IT SHOULD BE DIRECTION

                    case 'N': //up direction

                        cell_status[current.first][current.second].second.first -= 8;

                        cell_status[sel_neigh.first][sel_neigh.second].second.first -= 4;

                        break;

                    case 'S': //up direction

                        cell_status[current.first][current.second].second.first -= 4;

                        cell_status[sel_neigh.first][sel_neigh.second].second.first -= 8;

                        break;

                    case 'E': //up direction

                        cell_status[current.first][current.second].second.first -= 2;
                        
                        cell_status[sel_neigh.first][sel_neigh.second].second.first -= 1;

                        break;

                    case 'W': //up direction

                        cell_status[current.first][current.second].second.first -= 1;
                        
                        cell_status[sel_neigh.first][sel_neigh.second].second.first -= 2;

                        break;


            }

                    cell_status[sel_neigh.first][sel_neigh.second].second.second = 1;

                    visited.push_back(sel_neigh);


        }
        }
}

       
void maze::WriteFile(std::string fname,  std::vector<std::vector<std::pair<std::pair<int , int> , std::pair<int , int>>>> cell_status){

    std::ofstream output_file(fname); // Opens the output file, prepares it for writing //output_file is name of file stream //fname is the name of actual file

    for(unsigned int i = 0; i < cell_status.size(); i++){ // Loop rows

        for(unsigned int j = 0; j < cell_status[i].size(); j++){ // Loop columns 
    
            output_file << cell_status[i][j].second.first << " "; // Output each value and a space //writing to the file stream
}

        output_file << "\n"; // Output a newline character after every row
}
}
