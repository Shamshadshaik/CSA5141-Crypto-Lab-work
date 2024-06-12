#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define SHA3_RATE_BITS 576
#define SHA3_CAPACITY_BITS 1024
#define SHA3_LANES 25
#define SHA3_LANE_SIZE_BITS 64

// Initialize the state matrix
void initialize_state(uint64_t state[SHA3_LANES]) {
    memset(state, 0, SHA3_LANES * sizeof(uint64_t));
}

// Check if all lanes in the capacity portion have at least one nonzero bit
int all_capacity_lanes_nonzero(uint64_t state[SHA3_LANES]) {
    for (int i = SHA3_RATE_BITS / SHA3_LANE_SIZE_BITS; i < SHA3_LANES; i++) {
        if (state[i] == 0) return 0;
    }
    return 1;
}

int main() {
    uint64_t state[SHA3_LANES];
    initialize_state(state);

    int message_blocks = 0;
    while (!all_capacity_lanes_nonzero(state)) {
        // Simulate absorbing a message block
        for (int i = 0; i < SHA3_RATE_BITS / SHA3_LANE_SIZE_BITS; i++) {
            state[i] ^= (uint64_t)rand() << 32 | rand();
        }
        message_blocks++;
    }

    printf("Number of message blocks to achieve nonzero capacity lanes: %d\n", message_blocks);
    return 0;
}


