// SPDX-License-Identifier: EUPL-1.2
/* Copyright Mitran Andrei-Gabriel 2023 */

#include <cstdint>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

/**
 * @brief
 * Time O(n * log (sum g - max g)) ~ O(57 * n) = O(n)
 * Space O(n) (overall, including params)
 * 
 * sum g <= max n * max g = 10^5 * 10^12 = 10^17
 * log (sum g - max g) <= log (10^17 - 10^5) <= 56.48 <= 57
 * 1 <= n <= 10^5
 * 10^5 >> (much greater than) 57
 * 
 * Uses binary search
 * 
 * @param g vector that contains the weight of each car
 * @param n the number of cars
 * @param k the number of ferries
 * @param l the left counter for binary searching
 * @param r the right counter for binary searching
 * 
 * @return the smallest maximum cost
 */
uint64_t solveTask(const vector <uint64_t> &g, uint n, uint k,
				   uint64_t l, uint64_t r) {
	// The smallest maximum cost was found
	if (l > r)
		return l;

	// middle = (left + right) / 2
	uint64_t mid = l + ((r - l) >> 1);

	// The number of available ferries left
	uint cnt = k;

	// The cost of the current set of cars
	uint64_t cost = 0UL;

	// Going through all cars
	for (auto i = 0U; i < n; ++i) {
		// Adding the weight to the current cost
		cost += g[i];

		// The current cost is greater than maximum one
		if (cost > mid) {
			// The cost is now just the current car's weight
			cost = g[i];

			// Decreasing the number of available ferries left
			// If there are no more available ferries left
			if (!(--cnt))
				// The maximum cost is greater than the current one
				return solveTask(g, n, k, mid + 1, r);
		}
	}

	// We could fit all cars on ferries using this maximum cost.
	// but there may be a smaller maximum, so we keep searching
	return solveTask(g, n, k, l, mid - 1);
}

/**
 * @brief
 * Time O(n)
 * Space O(n)
 * 
 * Reads a vector from a file
 * 
 * @param is the file
 * @param size the vector's size
 * 
 * @return the vector
 */
vector <uint64_t> readVector(istream &is, uint size) {
	vector <uint64_t> vec(size);

	for (auto &num : vec) {
		is >> num;
	}

	return vec;
}

int main() {
	ifstream fin("feribot.in");
	ofstream fout("feribot.out");

	// The number of cars and th number of ferries
	uint n, k;
	fin >> n >> k;

	// Vector that contains the weight of each car
	auto g = readVector(fin, n);

	// Setting the left counter as the heaviest car's weight
	uint64_t l = *max_element(g.begin(), g.end());

	// Setting the right counter as the sum of all the cars' weights
	uint64_t r = accumulate(g.begin(), g.end(), 0UL);

	auto res = solveTask(g, n, k, l, r);

	fout << res << endl;

	return 0;
}
