#include <assert.h>
#include <fstream>
#include "generate_subgroups.h"
#include "carpark.h"

int main(){
    // Calculate the expected number of cars from the mean of the random generation
    std::ofstream outputFile;
    if (!outputFile) return 1;
    outputFile.open("time_vs_revenue_expected.txt");
    double alpha =10.0, beta=5.0; 
    std::vector<double> output(180,0);
    
    for (int time = 0; time <= 150; time++){
        // add leisure 
        // expected 5 customers a day, arrival 14 days later, stay for 7 days
        int leisure_arrival_time = time + 14;
        double duration = 8;
        for (int t =leisure_arrival_time; t<=leisure_arrival_time+7; t++){
            output[t] += 5*(beta+ alpha/duration);
        }
        int business_arrival_time = time +1;
        duration = 1.0;
        for (int t =business_arrival_time; t<business_arrival_time+1; t++){
            output[t] += 12.5*(beta+ alpha/duration);
        }
        duration = 2.0;
        for (int t =business_arrival_time; t<=business_arrival_time+1; t++){
            output[t] += 12.5*(beta+ alpha/duration);
        }
    }
    double total =0;
    for (int index = 0; index < output.size(); index++){
        outputFile.width(25); outputFile << index;
        outputFile.width(25); outputFile << output[index];
        outputFile << std::endl;
        total += output[index];
    }
    std::cout<<"total "<< total << std::endl;
    outputFile.close();
    return 0;
}
