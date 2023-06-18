#ifndef CARPARK_H
#define CARPARK_H 
#include "customer.h"
#include <numeric>

/* From customer bookings determines the number cars present in the carpark and revenue generated*/

class CarPark
{
private: 
    std::vector<int> vectorCarsPresent;
    std::vector<double> vectorRevenueGenerated;
    std::vector<bool> vectorCustomerAccepted;
    const int capacity;
    const double startTime, finishTime, alpha, beta;
    double total_revenue;
    
    bool AcceptBooking(const Booking &B){
        if (capacity == 0){
            return true;
        }
        for (int time = (int) B.arrivalTime - (int) startTime; time <= B.departureTime - (int) startTime; time ++){
            if ((time < 0) || (time >= vectorCarsPresent.size() )){
                std::cout << "Error trying to accessing time in SpaceAvailable" << time <<std::endl;
            }
            if (vectorCarsPresent[time] +1 > capacity){
                return false;
            }
        }
        return true;
    }

   void FillCarPark(const Customers &C){
        // declare the revenue, cars present to be zero vector of the total duration
        // determine max departure time
        double maxDepartureTime = finishTime;
        for (int customerIndex = 0; customerIndex < C.size(); customerIndex++){
            if (C[customerIndex].departureTime > maxDepartureTime){
                maxDepartureTime = C[customerIndex].departureTime;
            }
        }
        vectorCarsPresent.resize((int)(maxDepartureTime-startTime)+1, 0);
        vectorRevenueGenerated.resize((int)(maxDepartureTime-startTime)+1, 0);
        vectorCustomerAccepted.resize(C.size(), false);
        // Fill the carpark until it has reached capacity
        for (int customerIndex = 0; customerIndex < C.size(); customerIndex++){
            if (AcceptBooking(C[customerIndex])) {
                vectorCustomerAccepted[customerIndex] = true; // store the booking was accepted
                int duration = (int) (C[customerIndex].departureTime) -(int)(C[customerIndex].arrivalTime) +1;
                for (int time = (int) C[customerIndex].arrivalTime - (int) startTime; time <= C[customerIndex].departureTime - (int) startTime; time ++){
                    if ((time < 0 )|| (time >= vectorCarsPresent.size())){
                        std::cout << "Error time trying to access at carpresent vecotr in FillCarPark" << time << std::endl;
                    }
                    vectorCarsPresent[time] += 1;
                    double price_per_day = beta +(alpha/ duration);     // Equation (4.6)
                    if ((time < 0 )|| (time >= vectorRevenueGenerated.size())){
                        std::cout << "Error time trying to access at carpresent vecotr in FillCarPark" << time << std::endl;
                    }
                    vectorRevenueGenerated[time] += price_per_day;
                }
            }
        }
        // Calculate the total revenue
        total_revenue = 0;
        for (int index = 0; index < vectorRevenueGenerated.size(); index++){
            total_revenue+= vectorRevenueGenerated[index];
        }
    }

public:
    CarPark(const Customers &C, double startTime_input=0, double finishTime_input=150, 
    int capacity_input=0, double alpha_input=10, double beta_input=5) 
    : startTime(startTime_input), finishTime(finishTime_input), capacity(capacity_input)
    , alpha(alpha_input), beta(beta_input) {
        FillCarPark(C);
    }

    double GetTotalRevenue(){
        return total_revenue;
    }

    int GetCarsPresentSize(){
        return vectorCarsPresent.size();
    }
    int GetCarPresentTimeK(double k){
        int index = (int)(k -startTime);
        if ((index < 0) || (index >= vectorCarsPresent.size())){
            std::cout << "Error trying to access an invalid time" << k <<std::endl;
        }
        return vectorCarsPresent[index];
    }

    double GetRevenueGeneratedTimeK(double k){
        int index = (int)(k -startTime);
        if ((index < 0) || (index >= vectorRevenueGenerated.size())){
            std::cout << "Error trying to access an invalid time" << k <<std::endl;
        }
        return vectorRevenueGenerated[index];
    }

    bool GetCustomerAccepted(int index){
        if (index < 0 || index >= vectorCustomerAccepted.size()){
            std::cout << "Error invalid customer index requested: " << index << std::endl;
            return false;
        }
        return vectorCustomerAccepted[index];
    }
};

#endif
