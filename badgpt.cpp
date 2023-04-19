// SPDX-License-Identifier: EUPL-1.2
/* Copyright Mitran Andrei-Gabriel 2023 */

#include <cstdint>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

const uint mod = ((uint)1e9 + 7);

/**
 * @brief
 * Time O(1)
 * Space O(1)
 * 
 * Multiplies two 2x2 matrixes (modulo p)
 * 
 * @param F the first matrix (which is used to store the result)
 * @param S the second matrix
 */
void multMod(uint64_t A[2][2], uint64_t B[2][2], uint mod) {
	uint64_t A00 = (A[0][0] * B[0][0] % mod + A[0][1] * B[1][0] % mod) % mod;
	uint64_t A01 = (A[0][0] * B[0][1] % mod + A[0][1] * B[1][1] % mod) % mod;
	uint64_t A10 = (A[1][0] * B[0][0] % mod + A[1][1] * B[1][0] % mod) % mod;
	uint64_t A11 = (A[1][0] * B[0][1] % mod + A[1][1] * B[1][1] % mod) % mod;

	// Storing the result in the first matrix
	A[0][0] = A00;
	A[0][1] = A01;
	A[1][0] = A10;
	A[1][1] = A11;
}

/**
 * @brief
 * Time O(log n)
 * Space O(1)
 * 
 * @param F the base (a matrix), also used to store the result
 * @param n the exponent
 * @param p mod
 */
void fastPowMod(uint64_t M[2][2], uint64_t n, uint p) {
	uint64_t res[2][2] = {{1, 0},
						  {0, 1}};

	// M may have elements greater than p
	M[0][0] %= p;
	M[0][1] %= p;
	M[1][0] %= p;
	M[1][1] %= p;

	while (n) {
		// If n is odd
		if (n & 1)
			// Multiplies the result with M
			multMod(res, M, p);

		// n must be even now, so n = n/2 is not rounded
		n >>= 1;

		// Multiplies M with M
		multMod(M, M, p);
	}

	// Storing the result into the given matrix M
	M[0][0] = res[0][0];
	M[0][1] = res[0][1];
	M[1][0] = res[1][0];
	M[1][1] = res[1][1];
}

/**
 * @brief
 * Time O(log n)
 * Space O(1)
 * 
 * Uses the powers of the matrix M = {{1, 1}, {1, 0}} in order to find the nth
 * Fibonacci number (modulo p)
 * 
 * M^n = {{fibo(n + 1), fibo(n)}, {fibo(n), fibo(n - 1)}}
 * Fibonacci sequence: 0, 1, 1, 2, 3, 5, 8... so fibo(0) = 0, fibo(1) = 1...
 * 
 * @param n which Fibonacci number is calculated
 * @param p mod
 * 
 * @return the nth Fibonacci number (fibo(0) = 0 !!!)
 */
uint64_t fiboMod(uint64_t n, uint p) {
	uint64_t F[2][2] = {{1, 1},
						{1, 0}};

	// F becomes F^n
	fastPowMod(F, n, p);

	// fibo(n)
	return F[0][1];
}

/**
 * @brief
 * Time O(G * log L)
 * Space O(1)
 * 
 * G = the number of compressed groups (l followed by n)
 * L = the length of the uncompresed string (sum of all ns) 
 * 
 * @return the number of distinct strings that can be formed
 */
uint64_t solve(istream &is) {
	uint8_t l;
	uint64_t n, ans = 1;

	// Going through all comphelperFsed groups
	while (is >> l >> n) {
		// If 'n' or 'u' is found
		if (l == 'n' || l == 'u') {
			// Calculates the number of strings that can be formed
			ans *= fiboMod(++n, mod);
			ans %= mod;
		}
	}

	return ans;
}

int main() {
	freopen("badgpt.in", "r", stdin);
	freopen("badgpt.out", "w", stdout);

	cout << solve(cin) << endl;

	return 0;
}
