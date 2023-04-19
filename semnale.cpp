// SPDX-License-Identifier: EUPL-1.2
/* Copyright Mitran Andrei-Gabriel 2023 */

#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

// This number is prime
const uint mod = ((uint)1e9 + 7);

/**
 * @brief
 * Time O(log y)
 * Space O(1)
 * 
 * @param x the base
 * @param y the exponent
 * @param p mod
 * 
 * @return (x^y) modulo p
 */
uint64_t fastPowMod(uint64_t x, uint y, uint p) {
	uint64_t res = 1UL;

	// x may be greater than p
	x %= p;

	while (y) {
		// If y is odd
		if (y & 1) {
			// Multiplies the result with x
			res *= x;
			res %= p;
		}

		// y is even now, so y = y/2 is not rounded
		y >>= 1;

		// Multiplies x with x
		x *= x;
		x %= p;
	}

	return res;
}

/**
 * @brief
 * Time O(log (p - 2))
 * Space O(1)
 * 
 * Uses Fermat's little theorem
 * 
 * n^p = n (mod p)
 * n^(p - 1) = 1 (mod p)
 * n^(p - 2) = 1/n (mod p)
 * 
 * @param n the number
 * @param p a prime number (mod)
 * 
 * @return (1/n) modulo p
 */
uint64_t invMod(uint64_t n, uint p) {
	return fastPowMod(n, p - 2, p);
}

/**
 * @brief
 * Time O(n)
 * Space O(n) (this is just *additional* space)
 * 
 * Fills factorial array so that we can find all factorial of k, n and n - k
 * 
 * @param n the array contains all factorials up to n!
 * @param p mod
 * 
 * @return factorial array
 */
vector <uint64_t> calcFactMod(uint64_t n, uint p) {
	vector <uint64_t> fact(n + 1);

	fact[0] = 1UL;

	for (auto i = 1UL; i <= n; ++i)
		fact[i] = (fact[i - 1] * i) % p;

	return fact;
}

/**
 * @brief
 * Time O(log p)
 * Space O(1) 
 *  
 * @param n the number of elements
 * @param k how many times they are taken
 * @param p mod
 * @param
 * 
 * @return nCk (mixture of n elements taken k at a time without repetition)
 * modulo p 
 */
uint64_t combFermatMod(uint64_t n, uint k, uint p, vector <uint64_t> fact) {
	// If n < k
	if (n < k)
		// nCk is 0
		return 0UL;

	return (fact[n] * invMod(fact[k], p) % p * invMod(fact[n - k], p) % p) % p;
}

/**
 * @brief
 * Time O(max(x, y) + log mod) ~ O(max(x, y))
 * Space O(max(x, y)) (overall, including params)
 *
 * log mod ~ 30 (and is a constant)
 *
 * The signal cannot contain 2 or more consecutive 1s
 * 
 * @param x the number of 0s
 * @param y the number of 1s
 * 
 * @return the number of different signals
 */
uint type1(uint x, uint y) {
	// Calculates the number of different signals
	return combFermatMod(x + 1, y, mod, calcFactMod(max(x + 1, y), mod));
}

/**
 * @brief
 * Time O(max(x, y) + y * log mod) ~ O(max(x, y) + y)
 * Space O(max(x, y)) (overall, including params)
 *
 * log mod ~ 30 (and is a constant)
 *
 * The signal cannot contain 3 or more consecutive 1s
 * 
 * @param x the number of 0s
 * @param y the number of 1s
 * 
 * @return the number of different signals
 */
uint type2(uint x, uint y) {
	auto fact = calcFactMod(max(x + 1, y), mod);

	uint sum = 0U;

	// Calculates the number of different signals
	for (auto i = (y + 1) >> 1; i <= y; ++i) {
		sum += combFermatMod(x + 1, i, mod, fact) *
			combFermatMod(i, y - i, mod, fact) % mod;

		sum %= mod;
	}

	return sum;
}

int main() {
	freopen("semnale.in", "r", stdin);
	freopen("semnale.out", "w", stdout);

	uint sig_type, x, y;

	cin >> sig_type >> x >> y;

	switch (sig_type) {
		case 1:
			cout << type1(x, y);;
			break;
		case 2:
			cout << type2(x, y);
			break;
		default:
			cout << "wrong task number" << endl;
	}

	return 0;
}
