#include <assert.h>
#include <fstream>
#include "../generate_subgroups.h"
#include "../carpark.h"

int main(){
    // Calculate the total revenue of carpark of limited capacity time (10,...,100) over both business and leisure custoemrs.
    // Outputs the capacity and  expected total revenue.
    // Store all these results in an output file = n_vs_std_capacity_50.txt
    std::srand(std::time(NULL));
    std::ofstream outputFile;
    if (!outputFile) return 1;
    outputFile.open("capacity_vs_revenue.txt");
    int N = 2000;
    for (int capacity = 10; capacity <=100; capacity=capacity+10){
        outputFile.width(25);outputFile << capacity;
        std::vector<double> revenue_each_iteration;
        assert(revenue_each_iteration.size() == 0);
        for (int iter = 1; iter <= N; iter++){
            // Generate a group of customers a 
            Customers C = generate_both();
            CarPark carpark(C, 0, 150, capacity, 10, 5); 
            revenue_each_iteration.push_back(carpark.GetTotalRevenue());
        }
        double expected_total_revenue = 0;
        for (int index =0; index <revenue_each_iteration.size(); index++){
            expected_total_revenue += revenue_each_iteration[index];
        }
        expected_total_revenue = expected_total_revenue/ revenue_each_iteration.size();
        outputFile.width(25); outputFile << expected_total_revenue;
        outputFile << std::endl;

         // Calculate the relative error = correlation of variation = standard deviation / mean
         // Verify it's less than 0.01
        double standard_dev = 0;
        for (int i = 0; i < revenue_each_iteration.size(); i++) {
            standard_dev += (revenue_each_iteration[i] - expected_total_revenue)*(revenue_each_iteration[i] - expected_total_revenue);
        } 
        standard_dev =sqrt(standard_dev* 1 / (N* (N-1)));
       
        double corr_of_variation = standard_dev / expected_total_revenue;
        assert(corr_of_variation <= .01);
    }
    outputFile.close();
    return 0;
}
