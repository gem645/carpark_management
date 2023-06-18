#include <assert.h>
#include <fstream>
#include "../generate_subgroups.h"
#include "../carpark.h"

int main(){
    // Calculate the expected number of cars at time =150, absolute error (standard deviation), 
    // relative error (coefficient of variation) over different sample sizes from N=50, 100,.. 1500.
    // Store all these results in an output file = n_vs_std_cov.txt
    std::srand(std::time(NULL));
    std::ofstream outputFile;
    if (!outputFile) return 1;
    outputFile.open("rev_n_vs_std_cov.txt");
    for (int N = 50; N <=1500; N=N+50){
        outputFile.width(25);outputFile << N;
        std::vector<double> revenue_over_N;
        assert(revenue_over_N.size() == 0);
        for (int iter = 1; iter <= N; iter++){
            // Generate a group of customers a 
            Customers C = generate_both();
            CarPark carpark(C); 
            revenue_over_N.push_back(carpark.GetRevenueGeneratedTimeK(150));
        }
        std::cout <<"car present over N size" << revenue_over_N.size() <<std::endl;
        double expected_revenue = 0;
        for (int index =0; index <revenue_over_N.size(); index++){
            expected_revenue += revenue_over_N[index];
        }
        expected_revenue = expected_revenue/ revenue_over_N.size();
        outputFile.width(25); outputFile << expected_revenue;
    
        // Calculate the standard deviation == absolute error
        double standard_dev = 0;
        for (int i = 0; i < revenue_over_N.size(); i++) {
            standard_dev += (revenue_over_N[i] - expected_revenue)*(revenue_over_N[i] - expected_revenue);
        } 
        standard_dev =sqrt(standard_dev* 1 / (N* (N-1)));
        outputFile.width(25); outputFile << standard_dev;
        // Calculate the relative error = correlation of variation = standard deviation / mean
        double corr_of_variation = standard_dev / expected_revenue;
        outputFile.width(25); outputFile <<corr_of_variation;
        outputFile << std::endl;
    }
    outputFile.close();
    return 0;
}
