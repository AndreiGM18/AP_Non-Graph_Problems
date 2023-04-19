// SPDX-License-Identifier: EUPL-1.2
/* Copyright Mitran Andrei-Gabriel 2023 */

#include <cstdint>
#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

using namespace std;

/**
 * @brief
 * Time O(m * n)
 * Space O(m) (this is just *additional* space)
 * 
 * Calculates sushi platters' total grades
 * A sushi platter's total grade is the sum of all grades given to it
 * 
 * @param g all sushi platters' grades
 * @param m the number of sushi platters
 * @param n the number of customers
 * 
 * @return sushi platters' total grades
 */
vector <uint> getTotGrades(vector <vector <uint> > &g, uint m, uint n) {
	vector <uint> totGrades(m, 0U);

	for (auto j = 0U; j < m; ++j)
		for (auto i = 0U; i < n; ++i)
			totGrades[j] += g[i][j];

	return totGrades;
}

/**
 * @brief
 * Time O(m * n * x)
 * Space O(m * n + n * x) = O (n * (m + x)) (overall, including params)
 * 
 * Uses dynamic programming
 * Can pick just one serving per sushi platter
 * 
 * @param n the number of friends
 * @param m the number of sushi platters
 * @param x the maximum contribution of each friend
 * @param p all sushi platters' prices 
 * @param g all sushi platters' grades
 * 
 * @return the maxium price for the order of sushi
 */
uint task1(uint n, uint m, uint x, vector <uint> &p,
		   vector <vector <uint> > &g) {
	auto totGrades = getTotGrades(g, m, n);

	// The dp vector
	vector <uint> dp(n * x + 1);

	// For a maximum price of 0, no sushi platters can be ordered
	dp[0] = 0U;

	// Going through all sushi platters
	for (auto i = 0U; i < m; ++i)
		// Going through all prices
		for (auto price = n * x; price >= p[i]; --price)
			// Choosing whether we add the serving
			dp[price] = max(dp[price], dp[price - p[i]] + totGrades[i]);

	return dp[n * x];
}

/**
 * @brief
 * Time O(m * n * x)
 * Space O(m * n + n * x) = O (n * (m + x)) (overall, including params)
 * 
 * Uses dynamic programming
 * Can pick two servings per sushi platter
 * 
 * @param n the number of friends
 * @param m the number of sushi platters
 * @param x the maximum contribution of each friend
 * @param p all sushi platters' prices 
 * @param g all sushi platters' grades
 * 
 * @return the maxium price for the order of sushi
 */
uint task2(uint n, uint m, uint x, vector <uint> &p,
		   vector <vector <uint> > &g) {
	auto totGrades = getTotGrades(g, m, n);

	// The dp vector
	vector <uint> dp(n * x + 1);

	// For a maximum price of 0, no sushi platters can be ordered
	dp[0] = 0U;

	// Going through all sushi platters
	for (auto i = 0U; i < m; ++i)
		// Going through all prices
		for (auto price = n * x; price >= p[i]; --price) {
			// Choosing whether we add a serving or not
			dp[price] = max(dp[price], dp[price - p[i]] + totGrades[i]);

			// If we can add two servings
			if (price >= 2 * p[i])
				// Choosing whether we add two servings or not
				dp[price] = max(dp[price],
								dp[price - 2 * p[i]] + 2 * totGrades[i]);
		}

	return dp[n * x];
}

/**
 * @brief
 * Time O(m * n^2 * x)
 * Space O(m * n + n^2 * x) = O(n * (m + n * x)) (overall, including params)
 * 
 * Uses dynamic programming
 * Can pick two servings per sushi platter
 * Can only pick a number of servings equal to the number of friends
 * 
 * @param n the number of friends
 * @param m the number of sushi platters
 * @param x the maximum contribution of each friend
 * @param p all sushi platters' prices 
 * @param g all sushi platters' grades
 * 
 * @return the maxium price for the order of sushi
 */
uint task3(uint n, uint m, uint x, vector <uint> &p,
		   vector <vector <uint> > &g) {
	auto totGrades = getTotGrades(g, m, n);

	// The dp vector
	vector < vector <uint> > dp(n * x + 1, vector <uint> (n + 1));

	// For a maximum price of 0, no sushi platters can be ordered,
	// regardless of how many platters we end up "selecting"
	// If we select 0 platters, we would also not order anything
	// In both cases, the price ends up being 0
	for (auto sel = 0U; sel < n; ++sel)
		dp[0][sel] = 0U;

	// Going through all sushi platters
	for (auto i = 0U; i < m; ++i)
		// Going through all prices
		for (auto price = n * x; price >= p[i]; --price)
			// Selecting "sel" items
			// If we add a serving, we "select" it as well,
			// so we look in dp[][sel - x], where x is the number of servings
			// that have been selected
			for (auto sel = 1U; sel <= n; ++sel) {
				// Choosing whether we add a serving or not
				dp[price][sel] = max(dp[price][sel],
					dp[price - p[i]][sel - 1] + totGrades[i]);

				// If we can add two servings
				if (price >= 2 * p[i] && sel > 1)
					// Choosing whether we add two servings or not
					dp[price][sel] = max(dp[price][sel],
										 dp[price - 2 * p[i]][sel - 2] +
										 2 * totGrades[i]);
			}

	return dp[n * x][n];
}

int main() {
	freopen("sushi.in", "r", stdin);
	freopen("sushi.out", "w", stdout);

	uint task;  // task number

	uint n;  // number of friends
	uint m;  // number of sushi types
	uint x;  // how much each of you is willing to spend

	cin >> task;
	cin >> n >> m >> x;

	vector <uint> prices(m, 0U);  // prices of each sushi type
	// the grades you and your friends gave to each sushi type
	vector <vector <uint> > grades(n, vector <uint> (m, 0U));

	// price of each sushi
	for (auto i = 0U; i < m; ++i) {
		cin >> prices[i];
	}

	// each friends rankings of sushi types
	for (auto i = 0U; i < n; ++i) {
		for (auto j = 0U; j < m; ++j) {
			cin >> grades[i][j];
		}
	}

	int ans = -1;

	switch (task) {
		case 1:
			ans = task1(n, m, x, prices, grades);
			break;
		case 2:
			ans = task2(n, m, x, prices, grades);
			break;
		case 3:
			ans = task3(n, m, x, prices, grades);
			break;
		default:
			cout << "wrong task number" << endl;
	}

	cout << ans << endl;

	return 0;
}
