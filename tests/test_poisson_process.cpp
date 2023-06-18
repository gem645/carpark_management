#include <assert.h>
#include "../customer.h"

void test_interarrivaltime(double theta, std::vector<double> &intertimes){

    // calculate the average difference in time;
    double mean = 0;
    for (double intertime: intertimes){
        mean += intertime;
    }
    mean = mean/intertimes.size();
    double inverse_theta = 1.0 / theta;
    std::cout <<"Inverse theta " << inverse_theta <<" Mean " << mean <<std::endl;
    std::cout <<abs(inverse_theta - mean) << std::endl;
    // Relative tolerance /// Expected value and the variance are both mu == 1/theta
    assert (abs(inverse_theta - mean) < .05*inverse_theta);
}


int main(){
    std::srand(std::time(NULL));
    
    // Generate the low price leisure customers
    double bookingRate = 5, arrivalRate= 1.0/15.0, departureRate = 1.0/7.0, startTime = 0, finishTime = 500;
    Customers C;
    C.generateBookings(bookingRate, arrivalRate, departureRate, startTime, finishTime);
    
    // Verify booking rate theta
    std::vector<double> test_bookings_rate_vector;
    for (int i = 1; i < C.size(); i++) {
        test_bookings_rate_vector.push_back(C[i].bookingTime-C[i-1].bookingTime);
    }
    test_interarrivaltime(bookingRate, test_bookings_rate_vector);

    // Verify arrival rate theta
    std::vector<double> test_arrival_rate_vector;
    for (int i = 0; i < C.size(); i++) {
        test_arrival_rate_vector.push_back(C[i].arrivalTime-(int) C[i].bookingTime);
    }
    test_interarrivaltime(arrivalRate, test_arrival_rate_vector);

    // Verify departure rate theta
    std::vector<double> test_departure_ratte;
    for (int i = 0; i < C.size(); i++) {
        test_departure_ratte.push_back(C[i].departureTime-C[i].arrivalTime);
    }
    test_interarrivaltime(departureRate, test_departure_ratte);
    return 0;
}