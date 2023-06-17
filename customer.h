#ifndef CUSTOMER_H 
#define CUSTOMER_H
#include <vector>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include "booking.h"

/* Generate the customer bookings */

// compare for sort algorithms
bool operator<(const Booking &x,const Booking &y){
    if (x.bookingTime < y.bookingTime) {return true;}
    return false;
}

class Customers
{
private:
    std::vector<Booking> vectorBookings;
public:
    double generateNextEvent(double lambda, double t_n_minus_one) {
    // Generate the next event t_n following t_n_minus_one.
    // Generated with a poisson distribution where the difference between t_n and t_n_minus_one is
    // exp(lambda) distributed.
    double u_n = rand()/static_cast<double>(RAND_MAX); 
    while (u_n == 0) { // generate a new value of u_n non-zero.
        u_n = rand()/static_cast<double>(RAND_MAX);
    }
    double t_n = t_n_minus_one - 1/lambda * log(u_n);
    return t_n;
    }

    void generateBookings(double bookingRate,double arrivalRate,
    double departureRate,double startTime,double finishTime) {
    // Generaste first booking
    double bookingTime = startTime;
    double arrivalTime  = generateNextEvent(arrivalRate, bookingTime);  
    double departureTime = generateNextEvent(departureRate, arrivalTime);
    // determine if a list addinb is faster or vector adding is faster.
    while (bookingTime <= finishTime) { 
        // in built error checking, won't add if finish time < start time
        // add current valid bookingTime booking
        Booking b;
        b.bookingTime = bookingTime;
        b.arrivalTime =  arrivalTime;
        b.departureTime =  departureTime;
        vectorBookings.push_back(b);
        // Generate next booking;
        bookingTime  = generateNextEvent(bookingRate, bookingTime);
        arrivalTime = generateNextEvent(arrivalRate, bookingTime);  
        departureTime = generateNextEvent(departureRate, arrivalTime);
    }
    }

    
	Booking operator[](int index) const { //allow access to vectorBookings 
		// add range checking
		if (index >= 0 &  index < vectorBookings.size()){
			return vectorBookings[index];
		} else {
			std::cout << index << "is invalid index of the MVector" << std::endl;
			return vectorBookings[0];
		}
	}

	void operator<<(int j){
		for (int i = 0 ; i < j; i++) {
            std::cout << i << ": ";
			vectorBookings[i]<<(2);
		}
	}

    int size() const { return vectorBookings.size(); } // return number of elements in vectorBookings.

    void sort() {std::sort(vectorBookings.begin(),vectorBookings.end());}  // sort vectorBookings by bookingTime.

    void addBookings(Customers &C) {
        // Add booking from another customer class to this customer class.
        for (int index= 0; index < C.size(); index++){
            vectorBookings.push_back(C[index]);
        } 
        sort();
    }

    void addBooking(Booking &b) {
        // Add an inidividual booking from another customer class to this customer class.
        vectorBookings.push_back(b);
        sort();
    }
};

#endif
