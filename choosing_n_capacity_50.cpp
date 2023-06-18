#include <assert.h>
#include <fstream>
#include "generate_subgroups.h"
#include "carpark.h"

int main(){
    // Calculate the expected time a carpark of capacity 50 FIRST reaches capacity.
    // Outputs the expected value, standard deviation, coefficient of variation over different sample sizes from N=50, 100,.. 1500.
    // Store all these results in an output file = n_vs_std_capacity_50.txt
    std::srand(std::time(NULL));
    std::ofstream outputFile;
    if (!outputFile) return 1;
    outputFile.open("n_vs_std_capacity_50.txt");
    for (int N = 50; N <=2000; N=N+50){
        outputFile.width(25);outputFile << N;
        std::vector<double> capacity_over_N;
        assert(capacity_over_N.size() == 0);
        for (int iter = 1; iter <= N; iter++){
            // Generate a group of customers a 
            Customers C = generate_both();
            CarPark carpark(C, 0, 150, 50, 10, 5); 
            int first_t_capaacity_50;
            for (int index =0; index < carpark.GetCarsPresentSize(); index++){
                if (carpark.GetCarPresentTimeK(index) >= 50){
                    first_t_capaacity_50 = index;
                    break;
                }
            }
            capacity_over_N.push_back(first_t_capaacity_50);
        }
        std::cout <<"capacity for N size" << capacity_over_N.size() <<std::endl;
        double expected_capacity = 0;
        for (int index =0; index <capacity_over_N.size(); index++){
            expected_capacity += capacity_over_N[index];
        }
        expected_capacity = expected_capacity/ capacity_over_N.size();
        outputFile.width(25); outputFile << expected_capacity;
    
        // Calculate the standard deviation == absolute error
        double standard_dev = 0;
        for (int i = 0; i < capacity_over_N.size(); i++) {
            standard_dev += (capacity_over_N[i] - expected_capacity)*(capacity_over_N[i] - expected_capacity);
        } 
        standard_dev =sqrt(standard_dev* 1 / (N* (N-1)));
        outputFile.width(25); outputFile << standard_dev;
        // Calculate the relative error = correlation of variation = standard deviation / mean
        double corr_of_variation = standard_dev / expected_capacity;
        outputFile.width(25); outputFile <<corr_of_variation;
        outputFile << std::endl;
    }
    outputFile.close();
    return 0;
}
