#ifndef RUBBIX_CUBE_SOLVER_PERMUTATION_INDEXER_H
#define RUBBIX_CUBE_SOLVER_PERMUTATION_INDEXER_H

#include "math.h"
#include "bits/stdc++.h"
using namespace std;

template<size_t N, size_t K = N>
class Permutation_indexer{
    private:
    // Precomputed table containing the number of ones in the binary
    // representation of each number. The largest N-bit number is (1 << N) - 1.
        array<uint32_t, (1 << N)> onesCountLookup;

    // Precomputed table of factorials (or "picks" if N != K). They're in reverse order.
        array<uint32_t, K> factorials;
    public:
        Permutation_indexer(){
            for(uint32_t i = 0; i < (1 << N); ++i){
                bitset<N> bits(i);
                this->onesCountLookup[i] = bits.count();
            }
            for(uint32_t i = 0; i < K; ++i){
                this->factorials[i] = pick(N - 1 - i, K - 1 - i);
            }
        }
        uint32_t rank(const array<uint8_t, K> &permu) const{
            // this will hold lehmer code (in a factorial number system)
            array<uint8_t, K> lehmer;

            // set of "seen" digit in permutation.
            bitset<N> seen;

            // the first digit of lehmer code is always the digit of permutation
            lehmer[0] = permu[0];

            // Mark the digit as seen (bitset uses right_to_left indexing)
            seen[N - 1 - permu[0]] = 1;

            for(uint8_t i = 1; i < K; ++i){
                seen[N - 1 - permu[i]] = 1;
                // number of "seen" digit to the left of this digit is the count of ones
                // left of this digit
                uint32_t numOnes = this->onesCountLookup[seen.to_ulong() >> (N - permu[i])];
                lehmer[i] = permu[i] - numOnes;
            }
            uint32_t index = 0;
            for(uint32_t i = 0; i < K; ++i){
                index += lehmer[i] * this->factorials[i];
            }
            return index;
        }
};
#endif 