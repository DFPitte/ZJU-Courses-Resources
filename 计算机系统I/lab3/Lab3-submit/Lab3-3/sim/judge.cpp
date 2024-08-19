#include <svdpi.h>
#include <stdio.h>

extern "C" unsigned int mul_judge (
    unsigned int multiplicand, 
    unsigned int multiplier,
    unsigned long int product
){
    
    // fill the code
    bool right;
    unsigned long int simulate_result = (unsigned long int) multiplicand * (unsigned long int) multiplier;
    right = simulate_result == product;

    if(right == 0)
    {
        printf("*********error***********\n");
        printf("simulation multiplicand = %08x, multiplier = %08x, product = %016llx\n", multiplicand, multiplier, simulate_result);
        printf("hardware   multiplicand = %08x, multiplier = %08x, product = %016llx\n", multiplicand, multiplier, product);
    }
    else printf("RIGHT!simulation multiplicand = %08x, multiplier = %08x, product = %016llx\n", multiplicand, multiplier, simulate_result);
    return right;
}
