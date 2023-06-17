#ifndef BOOKING_H 
#define BOOKING_H 
#include <iostream>

class Booking
{
public:
    double bookingTime;
    int arrivalTime;
    int departureTime;

    void operator<<(int n)
    {
        std::cout<< "Booking Time: " << bookingTime<< std::endl;
        std::cout<< "Arrival Time: " << arrivalTime<< std::endl;
        std::cout<< "Departure Time: " << departureTime<< std::endl;
    }

};

#endif
