#include <assert.h>
#include "customers.h"

void test_order(Customers &C){
    // calculate the average difference in time;
    for (int index = 1; index < C.size(); index++){
        assert(C[index].bookingTime >= C[index-1].bookingTime);
    }
}

void test_valid_range(double startTime, double finishTime, Customers &C){
    for (int index = 0; index <C.size(); index ++){
        assert(C[index].bookingTime <= finishTime);
        assert(C[index].bookingTime >= startTime);
    }
}

int main(){
    std::srand(std::time(NULL));
    
    // Generate two groups of bookings and verify they booking times are in the right range`
    double bookingRate = 5, arrivalRate= 1.0/14.0, departureRate = 1.0/7.0, startTime = 0, finishTime=2;//finishTime = 150;
    Customers C_1;
    C_1.generateBookings(bookingRate, arrivalRate, departureRate, startTime, finishTime);
    test_valid_range( startTime, finishTime, C_1); // Verify range of bookings
    //Generate a bookings group 2
    bookingRate = 25; arrivalRate= 2; departureRate = 1; startTime = 0; finishTime=2;//finishTime = 250;
    Customers C_2;
    test_valid_range( startTime, finishTime, C_2); // Verify range of bookings
    C_2.generateBookings(bookingRate, arrivalRate, departureRate, startTime, finishTime);
    
    // Verify the order of both customer instances
    test_order(C_1); // Verify order 
    test_order(C_2); // Verify order 
    
    // Verify addBookings to an empty customer instance returns sorted vector
    Customers C_3;
    C_3.addBookings(C_2);
    test_order(C_2); // Verify order 
    assert(C_3.size() == C_2.size());

    // Verify adding two sets of generated bookings returns a sorted vectorBookings and has the expected size
    int prev_C_1_size = C_1.size();
    C_1.addBookings(C_2);
    test_order(C_1); // Verify order 
    assert(C_1.size() == C_2.size() + prev_C_1_size);
    return 0;

    // Test addBooking create a single booking
    Booking b_1;
    b_1.bookingTime =1; b_1.arrivalTime = 14; b_1.departureTime = 21;

    Booking b_2;
    b_2.bookingTime =0; b_2.arrivalTime = 13; b_2.departureTime = 20;
    // Add both to the list 
    Customers C_4;
    C_4.addBooking(b_1);
    C_4.addBooking(b_2);
    // verify b_2 is index 0, and b_1 is index 1 as it has a larger booking time
    assert(C_4[0].bookingTime == b_2.bookingTime);
    assert(C_4[1].bookingTime == b_1.bookingTime);
    assert(C_4[0].arrivalTime == b_2.arrivalTime);
    assert(C_4[1].arrivalTime == b_1.arrivalTime);
    assert(C_4[0].departureTime == b_2.departureTime);
    assert(C_4[1].departureTime == b_1.departureTime);

    // Add these two booking to C_1
    prev_C_1_size = C_1.size();
    C_1.addBookings(C_4);
    test_order(C_1); // Verify order 
    assert(C_1.size() == C_4.size() + prev_C_1_size);
    return 0;
    

}