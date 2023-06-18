#include "../booking.h"
#include <assert.h>

int main(){
    // Simple test case the booking assigns three attributes, booking time of double,
    // arrival and departure times of type ints.
    Booking b;
    b.bookingTime = 14;
    b.arrivalTime = 15.3;
    b.departureTime = 18.5;
    assert (b.bookingTime == 14);
    assert (b.arrivalTime == 15);
    assert (b.departureTime == 18);
    return 0;
}
