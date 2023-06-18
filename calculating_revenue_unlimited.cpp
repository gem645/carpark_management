#include <assert.h>
#include <fstream>
#include "generate_subgroups.h"
#include "carpark.h"

int main(){
    // Calculate the expected number of cars at time =150, absolute error (standard deviation), 
    // relative error (coefficient of variation) over different sample sizes from N=50, 100,.. 1500.
    // Store all these results in an output file = n_vs_std_cov.txt
    std::srand(std::time(NULL));
    std::ofstream outputFile;
    if (!outputFile) return 1;
    outputFile.open("time_vs_revenue.txt");
    int N = 750;
    std::vector<double> output;
    for (int iter = 1; iter < N; iter++){
        Customers C = generate_both();
        CarPark carpark(C); 
        for (int index = 0; index < carpark.GetCarsPresentSize(); index++){
            if (index >= output.size()){
                output.push_back(carpark.GetRevenueGeneratedTimeK(index));
            } else {
                output[index] += carpark.GetRevenueGeneratedTimeK(index);
            }
        }
    }
    // divide by 7500 to get the average
    for (int index = 0; index <= output.size(); index++){
        output[index] = output[index]/750.0;
    }
    // write to file   
    double total =0;
    
    for (int index = 0; index < output.size(); index++){
        outputFile.width(25); outputFile << index;
        outputFile.width(25); outputFile << output[index];
        outputFile << std::endl;
        total+= output[index];
    }
    std::cout<<"total "<< total << std::endl;
    outputFile.close();
    return 0;
}
