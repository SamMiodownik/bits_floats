#include "assignment.h"

#include <math.h>
#include <stddef.h>

unsigned bitset_symmetric_difference_count(uint32_t a, uint32_t b) {
    unsigned answer = 0;
    for(int i = 0; i < 32; i++){
        if(((a>>i) & 1) != ((b>>i) & 1)){
            answer++;
        }
    }
    return answer;
}

uint32_t bit_range_mask(unsigned low, unsigned high) {
    uint32_t result = 0;
    for(unsigned i = low; i <= high; i++){
        result |= (1 << i);
    }
    return result;
}

uint32_t splice_bits(
    uint32_t destination,
    uint32_t source,
    unsigned low,
    unsigned high
) {
    uint32_t mask = bit_range_mask(low, high);
    destination &= ~mask;
    destination |= ((source << low) & mask);
    return destination;
}

int32_t decode_twos_complement(uint32_t bits, unsigned width) {
    uint32_t mask = bit_range_mask(0, width-1);
    bits &= mask;
    int total = 0;
    int a = 1;
    if(bits>>(width-1) == 0){
        for(unsigned i = 0; i < width; i++){
            if((bits>>i & 1) == 1){
                total += a;
            }
            a*=2;
        }
        return total;
    }

    uint32_t flipped = ~bits + 1;
    for(unsigned i = 0; i < width; i++){
        if((flipped>>i & 1) == 1){
            total += a;
        }
        a*=2;
    }
    return (-total);
}

bool add_signed_width(
    uint32_t a_bits,
    uint32_t b_bits,
    unsigned width,
    uint32_t *sum_bits
) {

    uint32_t mask = bit_range_mask(0, width-1);
    a_bits &= mask;
    b_bits &= mask;
    uint32_t result = (a_bits + b_bits) & mask;
    
    if (sum_bits != NULL) {
        *sum_bits = result;
    }
    
    uint32_t sign_bit = 1u << (width - 1);

    bool a_negative = (a_bits & sign_bit) != 0;
    bool b_negative = (b_bits & sign_bit) != 0;
    bool result_negative = (result & sign_bit) != 0;

    if (!a_negative && !b_negative && result_negative) {
        return true;
    }

    if (a_negative && b_negative && !result_negative) {
        return true;
    }
    return false;
}

int compare_signed_unsigned_math(
    int32_t signed_value,
    uint32_t unsigned_value
) {
    uint32_t new_unsigned_value = 0;
    if((signed_value>>31&1) == 1){
        return -1;
    }else{
        new_unsigned_value = signed_value;
    }
    if(new_unsigned_value < unsigned_value){
        return -1;
    }
    if(new_unsigned_value > unsigned_value){
        return 1;
    }
    return 0;
}

uint32_t multiply_by_24(uint32_t x) {
    uint32_t result = (x<<5) - (x<<3);
    return result;
}

fp32_info_t fp32_decode(uint32_t bits) {
    (void)bits;

    fp32_info_t info = {
        .negative = false,
        .kind = FP32_ZERO,
        .exponent_bits = 0,
        .fraction_bits = 0,
        .unbiased_exponent = -126,
    };
    return info;
}

double fp32_exact_value(uint32_t bits) {
    (void)bits;
    return 0.0;
}

uint32_t fp32_next_up_bits(uint32_t bits) {
    (void)bits;
    return 0;
}

bool fp32_truncate_to_int(uint32_t bits, int32_t *out) {
    (void)bits;

    if (out != NULL) {
        *out = 0;
    }
    return false;
}
