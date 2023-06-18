#ifndef GENERATE_SUBGROUPS_H // the 'include guard'
#define GENERATE_SUBGROUPS_H // see C++ Primer Sec. 2.9.2
#include "customer.h"

/* Initialising the required subgroups of customers. */
Customers generate_low_priced_customers(double l_bookingRate = 5, double l_arrivalRate = 1.0/14.0,
double l_departureRate= 1.0/7.0, double l_startTime= 0, double l_finishTime= 150){
    Customers low_priced_leisure_customers;
    low_priced_leisure_customers.generateBookings(l_bookingRate, l_arrivalRate, l_departureRate, l_startTime, l_finishTime);
    return low_priced_leisure_customers;
}

Customers generate_high_priced_customers(double h_bookingRate = 25, double h_arrivalRate = 1.0,
double h_departureRate = 2.0, double h_startTime = 0, double h_finishTime= 150){
    Customers high_priced_business_customers;
    high_priced_business_customers.generateBookings(h_bookingRate, h_arrivalRate, h_departureRate, h_startTime, h_finishTime);
    return high_priced_business_customers;
}

Customers generate_both(){
    Customers low_priced = generate_low_priced_customers();
    Customers high_priced = generate_high_priced_customers();
    int high_priced_size = high_priced.size();
    high_priced.addBookings(low_priced);
    assert(high_priced.size() == low_priced.size() + high_priced_size);
    return high_priced;
}

#endif