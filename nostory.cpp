// SPDX-License-Identifier: EUPL-1.2
/* Copyright Mitran Andrei-Gabriel 2023 */

#include <cstdint>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

/** @brief
 * Time O(n log n)
 * Space O(n) (overall, including params)
 * 
 * @param a the first number list
 * @param b the second number list
 * 
 * @return the score
 */
uint64_t solveTask1(vector <uint> &a, vector <uint> &b) {
	// Sorting the first one in ascending order (O(n log n))
	sort(a.begin(), a.end());

	// Sorting the second one in descending order (O(n log n))
	sort(b.begin(), b.end(), greater <uint>());

	uint64_t score = 0ULL;

	// Choosing the greater one to add to the score
	for (auto i = 0UL; i < a.size(); ++i)
		score += max(a[i], b[i]);

	return score;
}

/** @brief
 * Time O(n log n)
 * Space O(n) (overall, including params)
 * 
 * @param a the first number list
 * @param b the second number list
 * @param moves the number of moves that can be made
 * 
 * @return the score
 */
uint64_t solveTask2(vector <uint> &a, vector <uint> &b, uint moves) {
	// Swapping elements of the same position between vectors does not
	// count as a move, as such we can have the first one containing
	// all the numbers we would add to the score if we made no moves
	for (auto i = 0UL; i < a.size(); ++i)
		if (b[i] > a[i])
			swap(a[i], b[i]);

	// Sorting the first one in ascending order (O(n log n))
	sort(a.begin(), a.end());

	// Sorting the second one in descending order (O(n log n))
	sort(b.begin(), b.end(), greater<uint>());

	uint64_t score = 0ULL;

	// Choosing the greater one to add to the score
	// (only doing this for the allowed number of moves)
	for (auto i = 0U; i < moves; ++i)
		score += max(a[i], b[i]);

	// The first vector contains the numbers that would be picked,
	// had we made 0 moves. as such we can the sum of the remaing
	// numbers after we made all available moves to the score
	score += accumulate(a.begin() + moves, a.end(), 0ULL);

	return score;
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
vector <uint> readVector(istream &is, uint size) {
	vector <uint> vec(size);

	for (auto &num : vec) {
		is >> num;
	}

	return vec;
}

int main() {
	ifstream fin("nostory.in");
	ofstream fout("nostory.out");

	uint task;
	fin >> task;

	uint n, moves;
	if (task == 1) {
		fin >> n;
	} else {
		fin >> n >> moves;
	}

	auto a = readVector(fin, n);
	auto b = readVector(fin, n);

	auto res = task == 1 ? solveTask1(a, b) : solveTask2(a, b, moves);
	fout << res << endl;

	return 0;
}
