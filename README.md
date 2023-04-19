**Name: Mitran Andrei-Gabriel**
**Group: 323CA**

## Homework #1 (Almost without Gigel)

### Organization and Complexity Analysis:
#### Ferryboat
* Let n be the number of cars, k be the number of ferries and g[0..(n-1)] be
the weight of each car. (Space O(n))
###### Time: O(n * log (sum g - max g)) ~ O(n), Space: O(n)
* Since we only need to store the weights, the Space Complexity is O(n).
* The smallest maximum cost lies somewhere between the heaviest car's weight
and the sum of all cars' weights.
* In order to find this cost, binary search is used, having the left counter
and the right counter as the two values mentioned above.
* A single search would have a time complexity of O(log (sum g - max g)),
assuming nothing else is done.
* When checking if the current middle is the smallest maximum cost, cars
are fitted on ferries one after another (not going over the current maximum
cost, which is dictated by the middle counter).
* If all cars can be fitted on less than or equal to how many available ferries
there are, then we can search for a smaller maximum (in the lower interval).
If not, we search for a greater one (in the upper interval).
* If the left counter ends up greater than the right one, then the left one is
the smallest maximum cost.
* Since each iteration of the search would have to check whether all cars fit
or not, meaning going through every single car, that is O(n) per iteration of
the binary search, adding up to an overall Time Complexity of
O(n * log (sum g - max g)).
* However, O(n * log (sum g - max g)) ~ O(57 * n) = O(n), since sum g <=
max n * max g = 10^5 * 10^12 = 10^17, which means that log (sum g - max g) <=
log (10^17 - 10^5) <= 56.48 <= 57 and since 1 <= n <= 10^5 and 10^5 is much
greater than 57, we can approximate a complexity of O(n) per overall search.

#### Nostory
* Let a be the first number list, b be the second number list, n be the size of
both and k be the number of moves that one is allowed to make.
* The lists also the program's Space Complexity: O(n).
##### Task 1: k -> Inf
###### Time O(n log n), Space O(n)
* Firstly, we sort a in ascending order and b in descending order. (O(n log n))
* We do this so that we can maximize which number we pick for each position.
* By having both maximums of each list at opposite ends, we can ensure that
each pick contributes the most to the score.
* Going through the lists simultaneously and picking the maximum between them
for each position would have a complexity of O(n).
* As such, the score ends up being the most it could possibly be.
* Overall, the Time Complexity of the program ends up being O(n log n + n) =
O(n log n).
##### Task 2: k is finite
###### Time O(n log n), Space O(n)
* We begin by storing all the elements that would be chosen, had no moves been
made, in the first list. That is, we put max(a[i], b[i]) in a[i]. In b[i] we
store the other element. (O(n))
* Swapping elements of the same position is technically not a move, since it
does not affect the score whatsoever. The same effect can be achieved by
using two other lists to store max(a[i], b[i]) and min(a[i], b[i]).
* Then, we sort a in ascending order and b in descending order. (O(n log n))
* By doing this, we repeat the same process of Task 1, but only for the given
amount of moves. (O(k))
* For the rest, we add up the remaining elements of a, since those are the
elements that would have been chosen anyway. (O(n - k))
* As such, we maximize the first k elements and the others are left as the
already maximum choice between the two original choices, had no moves been
made.
* Overall, the Time Complexity ends up O(n log n + k + n - k) = O(n log n + n)
= O(n).

#### Sushi
* Let n be the number of friends, m be the number of sushi platters, x be the
maximum contribution of each friend, p[0..(m - 1)] be all sushi platters'
prices and g[0..(m - 1)][0..(n - 1)] be all sushi platters' grades.
(Space O(m + m * n) = O(m * (n + 1)) = O(m * n) for every task)
* Let totalGrade[0..(m - 1)] be the total grades of all sushi platters. The
total grade is the total sum of grades given to a sushi platter.
* The previous vector gives a Time Complexity of O(m * n) and a
Space Complexity of O(m) for every task, since the calculation is required for
each one.
* However, the Space one ends up O(m * n + m) = O(m * (n + 1)) = O(m * n)
for each task.
##### Task 1: Only one serving per sushi platter
###### Time O(m * n * x), Space O(n * (m + x))
* This problem is simply the backpack problem, but instead of profit and
weight, we have total grade and price, where total grade is the total sum of
grades given to all sushi platters and the price is the n * x (the maximum
possible price that the friends can pay).
* For a maximum price of 0, no platters can be ordered.
* Similarly to the problem, we iterate through all sushi platters and for each
one through all prices starting from the maximum to the sushi platter's price
and we choose whether we add a serving or not, maximising the total grade
of the order. (O(m * n * x))
* Instead of keeping a 2x2 array, we can make do with a vector. The only
dimension that is actually worth remembering is the price (or the limiting
factor of the backpack). This reduces the Space Complexity from
O(m * n + m * n * x) = O(m * n * x) to O(m * n + n * x) = O(m * (n + x)).
##### Task 2: Only two servings per sushi platter
###### Time O(m * n * x), Space O(n * (m + x))
* The same as task 1, but you simply add the condition so that two servings
can be added, after checking if only one can be added, regardless if it was
added or not.
##### Task 3: Only two servings per sushi platter, at most n servings 
###### Time O(m * n^2 * x), Space O(n * (m + n * x))
* We can add another dimension to the vector, specifically the number of
selected servings. O(m * n + n^2 * x) = O(n * (m + n * x))
* For a maximum price of 0, no platters can be ordered, regardless of
how many we 'select'. (O(n) for initializing with 0, negligable)
* Then, we iterate through all sushi platters and for each one through all
prices starting from the maximum to the sushi platter's price, then looping
from 1 to n selected items and we choose whether we add 1 or 2 servings,
maximising the total grade of the order. (O(m * n * x * x) = O(m * n^2 * x))

#### Signals
* Let x be the number of zeros and y be the number of ones.
* Let mod be 10^9 + 7, which is a prime number.
##### Task 1: Two or more consecutive 1s not allowed
###### Time O(max(x, y) + log mod) ~ O(max(x, y)), Space O(max(x, y))
* The number of signals is determined by how many 0s can come before a 1.
As a starting example: let us consider 3 0s and 2 1s:
10100 - (0 0s before the first one, 1 before the second one) -> (0; 1)
10010 - (0 0s before the first one, 2 before the second one) -> (0; 2)
10001 - (0 0s before the first one, 3 before the second one) -> (0; 3)
01010 - (1 0s before the first one, 2 before the second one) -> (1; 2)
01001 - (1 0s before the first one, 3 before the second one) -> (1; 3)
00101 - (2 0s before the first one, 3 before the second one) -> (2; 3)
* In this example, there are 6 (4C2) signals.
* It is easily observed that the mixture of (x + 1) elements taken y at a time
without repetition is the answer. In other words, given x and y, the answer
becomes (x + 1)Cy.
* In order to calculate the combination, we can precalculate all factorial up
to max(x + 1, y). O(max(x, y))
* Since we need division and modulo, Fermat's little theorem can be used:
n^p = n (mod p)
n^(p - 1) = 1 (mod p)
n^(p - 2) = 1/n (mod p)
* In order to calculate pow(n, p - 2), we can use a fast power algorithm.
We can break the exponent in a sum of powers of 2 and the result in a product
of the original number raised to each of those powers, which can be calculated
by repeatedly squaring the originial number. (O(log p), p = mod)
* A division would have a complexity of O(log mod) = O(30) ~ O(1).
##### Task 2: Three or more consecutive 1s not allowed
###### Time O(max(x, y) + y * log mod) ~ O(max(x, y) + y), Space O(max(x, y))
* Similarly to the first task, combinations are the basis for this solution as
well.
* Starting off with an example, let us consider 3 0s and 3 1s this time.
* The example from task 1 still stands. We simply need to add the remaining 1.
It can be added to either of the other 1s.
* This basic idea gives the general formula for x 0s and y 1s.
* Taking ciel(y/2) (at least half of y) 1s as 'fixed', we can generate an
example not too dissimilar to the original. That is, we would have
(x + 1)C(ciel(y/2)) ways of putting the 0s and half of the given 1s.
* Then we would, need to pair up the remaining 1s with the 'fixed' 1s. This
would be done in (ciel(y/2))C(y - ciel(y/2)) ways (there are y - ciel(y/2)
'free' 1s, since there are ciel(y/2) 1s).
* Overall the number of signals when we 'fix' exactly ciel(y/2) 1s is the
product of the two combination.
* If instead of 'fixing' at least half of the 1s, we 'fix' more it would yield
the general formula: (x + 1)Ci * iC(y - i) with i going from half of y to y.
* The overall number of signals would end up as the sum of all these products.
* The way the combinations are calculated in exactly the same way as in the
first task. O(max(x, y) + y * log mod) ~ O(max(x, y) + y), since we do the
calculations exactly half of y times.

#### BadGPT (Bonus)
* Let l be a letter of the string and n be the number of times it appears.
* Let G be the number of compressed groups (l followed by n) and L be the
length of the uncompressed string (sum of all ns). 
###### Time O(G * log L), Space O(1)
* We can go through all letters and ignore all of them besides 'n' and 'u'.
* When encountering one of them, the number of ways to form different strings
from them can be calculated as the (n + 1)th Fibonacci number.
* The reason for this can be explained due to the fact that, knowing that
for 'n1' or 'u1' the number of different strings is 1 (just 'n' or 'u') and
for 'n2' or 'u2' the number is 2 ('nn' and 'm' or 'uu' and 'w'), we can
calculate the number of strings starting from these two cases.
* In the general case, 'nn' or 'un' (for n 'n's or 'u's), if we have,
for example 'u u... u u u' (n times), then the we can either group the last two
or not like so: 'u u... u (uu)' -> 'u u... u w' (n - 2 'u's left) or
'u u... u u |u|' (n - 1 'u's left, the last 'u' can not be grouped with any
other u, while the penultimate one can).
* As such, if we knew the number of different strings that n - 2 and n - 1
letters generate, then we would know the number for n as well. If we keep
going all the way, we end up at the base cases.
* As such we get the Fibonacci sequence starting from the 2nd 1: 1 2 3 5 8
and so on. The sequence typically goes like so: 0 1 1 2 3 5 8... Since for
'n1' or 'u1' (n = 1) we get 1 (fibo(2)) and for 'n2' and 'u2' (n = 2)
we get 2 (fibo(3)), we can generalize that for 'nn' or 'un' we get fibo(n + 1).
* For generating fibo(n), we can use the powers of the matrix {{1, 1}, {1, 0}}.
At the nth power, it yields {{fibo(n + 1), fibo(n)}, {fibo(n), fibo(n - 1)}},
for n >= 1. This can be easily proven by using induction.
* For actually rasing the matrix to the nth power, we can use the same fast
power algorithm that was used for the Signals problem, only instead of usual
multiplication we use 2x2 matrix multiplication. (O(log n))
* For multiple appearances of groups of 'n' or 'u', the overall number of
different strings that can be formed is merely the product of all numbers of
strings that can be formed by each individual group, since all combinations are
possible.

### Implementation:
* Every functionality required for this homework was implemented.
* Every problem (and all its tasks) was solved.

### Compilation:
* In order to compile, we use:
```
make
```

### Comments:
* The Space Complexity for the helper functions simply refer to *additional*
space, while the functions that solve tasks have the *overall* complexity
listed, since it is meant to act as the overall algorithm, so I thought it
was fair to include the parameters in its Space Complexity.

### Resources:
* Everything provided by the AP team
* [Linux Manual](https://www.man7.org/linux/man-pages/index.html)