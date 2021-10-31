#include<fstream>
#include<vector> // std::vector
#include<string>
#include<sstream>
#include<iostream> // std::cout
#include<algorithm>    // std::sort
#include<math.h> //sqrt

// FUNCTION DECLARATION...............................................................................................................

void ReadFile(std::string in_fname, std::vector<std::vector<double>> *const image_data);

void WriteFile(std::string out_fname, std::vector<std::vector<double>> binarized_vec);

void glob_thresh(std::vector<std::vector<double>> *const image_data, double &glob_T, int num_row , int num_col); 

double SD(double temp_array[]);

void loc_thresh(std::vector<std::vector<double>> *const image_data , std::vector<std::vector<double>> *const loc_T , int num_row ,
 int num_col , std::string size_neighbor); 

void binz (std::vector<std::vector<double>> *const image_data , std::vector<std::vector<double>>*const binarized_vec
     , std::string type , int num_row , int num_col , double glob_T , std::vector<std::vector<double>> *const loc_T);

// MAIN FUNCTION...............................................................................................................

int main(int argc, char** argv){

    std::vector<std::vector<double>> image_data;
    std::vector<std::vector<double>>binarized_vec;
    std::vector<std::vector<double>> loc_T;
    std::string type, in_fname, out_fname , size_neighbor;
    int num_row , num_col;
    double glob_T;

    // get command line arguments
    
    if (argc==4){

        type = argv[1];
 
        in_fname = argv[2];

        out_fname = argv[3];  
    }
    else if(argc == 5){

        type = argv[1];

        in_fname = argv[2];

        out_fname = argv[3];

        size_neighbor = argv[4];
    }

    
    ReadFile( in_fname, &image_data); // read_image into a 2-d vector (image_data)

    num_row = image_data.size();

    num_col = image_data[0].size();

    if(type == "global"){ // Finding global threshold
 
        glob_thresh(&image_data, glob_T , num_row , num_col); //it retuen the global theshold value and also saved values in num_row and num_col
    }

    
    else if(type == "local"){ // Finding local threshold

        loc_thresh(&image_data , &loc_T , num_row , num_col , size_neighbor); //returning a 2-d vector (loc_T) that holds threshold values
    }  

    binz (&image_data , &binarized_vec, type , num_row ,  num_col , glob_T , &loc_T); // Binarize pixels
    
    WriteFile(out_fname, binarized_vec);  // Writing to a new file cow2.img
}

// FUNCTIONS DEFINITIONS............................................................................................................

    void ReadFile(std::string in_fname, std::vector<std::vector<double>> *const image_data){ //it is a pointer to a vector,therefore, after end of func, it will still exist // Create the input filestream - opens the file & prepares it for reading
    
        std::ifstream file(in_fname);

        std::string str; // Temporary string to hold a single line of the file

        while (std::getline(file, str)) { // Reads all lines in the file, 1 at at time
            
        std::vector<double> new_row; // Creates a temporary vector to represent one row
        
        std::istringstream ss(str); // Converts our string into a stringstream
        
        double token; // Temp double to store a converted value from a line

            
            while(ss >> token){ // Reads all values from the stringstream (current row), converts to double
                
                new_row.push_back(token); // Adds the converted value to the row
            }
            
            image_data->push_back(new_row); // Pushes our constructed vector of doubles to the 2D vector
        }
    }


void WriteFile(std::string out_fname, std::vector<std::vector<double>> binarized_vec){
    
    std::ofstream output_file(out_fname); // Opens the output file, prepares it for writing
    
    for(unsigned int i = 0; i < binarized_vec.size(); i++){ // Loop rows
        
        for(unsigned int j = 0; j < binarized_vec[i].size(); j++){ // Loop columns 
            
            output_file << binarized_vec[i][j] << " "; // Output each value and a space
        }
        
        output_file << "\n"; // Output a newline character after every row
    }
}


void glob_thresh(std::vector<std::vector<double>> *const image_data , double &glob_T , int num_row , int num_col){ //passed by reference to an int

    std::vector<double> temp_vec;// sorting all elements of 2-d vector in a 1-d vector

    // std::cout<<num_row;

        for (int i = 0 ; i < num_row ; i++){

            for (int j = 0 ; j < num_col ; j++){

                temp_vec.push_back((*image_data)[i][j]); //make a 1-d vector from 2-d vector of image to use for finding median

            }
        }

    std::sort(temp_vec.begin() , temp_vec.end()); //sorting 1-d temp_vec

    if (temp_vec.size() % 2 == 0){ //if size of 1-d vector is even

        glob_T = ( (temp_vec [ temp_vec.size() / 2 ] + temp_vec[ temp_vec.size() / 2 - 1 ]) / 2 ); //median is average of two middle elements
    }
    else if (temp_vec.size() % 2 != 0){ //else if size of 1-d vector is odd

        glob_T = ( temp_vec [ temp_vec.size() / 2 ]); //median is the middle element
    }
    }

void loc_thresh(std::vector<std::vector<double>> *const image_data , std::vector<std::vector<double>> *const loc_T , int num_row , int num_col , std::string size_neighbor ){

    int dist = (std::stoi(size_neighbor))/2;//rows/cols on the sides of a cell, forming a neighborhood //converting cpp string to int

    double max_value = 0;
    
    double min_value = 255;

     for (int i = 0; i < num_row; i++) { //Finding min and max of whole image

        for (int j = 0; j < num_col; j++) {

            if ((*image_data)[i][j] > max_value) {
                max_value = (*image_data)[i][j];
            }

            if ((*image_data)[i][j] < min_value) {
                min_value = (*image_data)[i][j];
            }
        }
    }

    // std::cout<<min_value<<std::endl;

    for(int i = 0 ; i <num_row ; i++){ //Going over rows of 2-d vector

        std::vector<double> temp_loc_T; //pusher 1-d vector

        for (int j = 0 ; j < num_col ; j++){ //Going over cols of 2-d vector

            int new_i_top = i - dist; //top edge

            int new_i_bot = i + dist; //bottom edge

            int new_j_left = j - dist; //left edge

            int new_j_righ = j + dist; //right edge

            std::vector<double> temp_vec; // neighborhood of each pixel

            int count = 0;

            double sum = 0 , mean , SD;

            for(int k = new_i_top ; k <= new_i_bot ; k++){//

                for (int l = new_j_left ; l <= new_j_righ ; l++){//equal sign

                    if (k >= 0 && k < num_row && l >= 0 && l < num_col){

                        // std::cout<< (*image_data)[k][l];// checking original image
                        sum += (*image_data)[k][l];

                        count++;
                    
                        temp_vec.push_back((*image_data)[k][l]);/////////////////////////////
                    }
                }
            }

            
            mean = sum / count;

            double accmulator = 0.0;

            for(int x = 0 ; x < count ; x++ ){

                    accmulator += pow((temp_vec[x] - mean) , 2);

            }

            SD = sqrt(accmulator / (temp_vec.size())); //N or N-1?

            // std::cout<< SD << std::endl;

            temp_loc_T.push_back (  mean * ( 1 + 0.2 * ( ( SD / (0.5 * ( max_value - min_value ) ) - 1) ) ) );

            // for(int i = 0 ; i < temp_loc_T.size() ; i++){

            //     std::cout<< temp_loc_T[i] << std::endl;
            // }

    }
            (*loc_T).push_back(temp_loc_T);
}
}

    // binarizing pixels
    
    void binz (std::vector<std::vector<double>> *const image_data , std::vector<std::vector<double>>*const binarized_vec
     , std::string type , int num_row , int num_col , double glob_T , std::vector<std::vector<double>> *const loc_T){


    if (type == "global"){

        for (int i = 0 ; i < num_row ; i++){ //Going over the rows$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

            std::vector<double>temp_vec;

            for (int j = 0 ; j < num_col ; j++){ //Going over columns$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

                if ((*image_data)[i][j] < glob_T){  

                    temp_vec.push_back (0); //pusshing binarized pixel to the 1-d vec$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
                }
                else if ((*image_data)[i][j] >= glob_T){ 

                    temp_vec.push_back (255); //pusshing binarized pixel to the 1-d vec$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
        }
                }
                    (*binarized_vec).push_back (temp_vec); //pushing 1-d vector to the 2-d vector
                
                }       
            }
    

    else if (type == "local"){

        // std::cout<<"max";
// std::cout<<num_row;
        for (int i = 0 ; i < num_row ; i++){ //Going over rows of 2-d vec

            std::vector<double> temp_vec; //pusher vector

            // std::cout<<"mas";

            for (int j = 0 ; j < num_col ; j++){ //Going over cols of 2-d vec

                    if((*image_data)[i][j] < (*loc_T)[i][j]){

                        temp_vec.push_back(0); //pusshing binarized pixel to the 1-d vec$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

                        // std::cout<<"max";
                    }

                    else if((*image_data)[i][j] >= (*loc_T)[i][j]){

                        temp_vec.push_back(255); //pusshing binarized pixel to the 1-d vec$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
                    }

                    }
                (*binarized_vec).push_back(temp_vec); //pushing 1-d vector to the 2-d vector
            }
        }   
     }

    
   