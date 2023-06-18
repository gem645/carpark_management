#include <assert.h>
#include "../carpark.h"

// First check the generate car present functions work
int booking_in_carpark(const Booking &x, int time_interval){ 
    // Determine if a booking is in the carpark for a given day/time interval.
    if (time_interval <= x.arrivalTime && x.arrivalTime < time_interval+1) {return 1;}
    // Modified here (time_interval <= x.departureTime) since we rounded down x.departureTime to integer to reduce storage.
    if (time_interval <= x.departureTime && x.departureTime < time_interval+1) {return 1;}
     // Modified here (x.departureTime > time_interval) since we rounded down x.departureTime to integer to reduce storage.
    if (x.arrivalTime < time_interval && x.departureTime > time_interval ){return 1;}
    return 0;}

std::vector<int> CarsPresent_slow(const Customers &C, const double startTime_t, const double k){
    std::vector<int> cars_present(k, 0);
    for (int customerIndex = 0; customerIndex < C.size(); customerIndex++){
        // iterate through everyday the booking is in the car park.
        Booking b = C[customerIndex];
        for (int time = startTime_t; time <= startTime_t+k-1; time++){
            int index = time - startTime_t;
            cars_present[index] += booking_in_carpark(b, time);
        }
    }
    return cars_present;
}

int main(){
    std::srand(std::time(NULL));
    for (int iter = 0; iter <= 100; iter++ ){
        double bookingRate = 5, arrivalRate= 1.0/14.0, departureRate = 1.0/7.0, startTime = 0, finishTime=2;
        Customers C;
        C.generateBookings(bookingRate, arrivalRate, departureRate, startTime, finishTime);
        CarPark carpark(C);
        std::vector<int> carpresent_vec = CarsPresent_slow(C, 0, 151);
        for (int time = 0; time <= 150; time++){
            assert (carpresent_vec[time] == carpark.GetCarPresentTimeK(time));
        }
    } 
    return 0;
}