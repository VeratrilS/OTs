
# AP Removal

**Topic:** Interval DP

---

## Problem Statement

You are given an array `A` of `N` integers.

In one operation, you may choose **three consecutive elements** `A[i], A[i+1], A[i+2]` that form an **arithmetic progression**, i.e.

```
A[i+1] - A[i] == A[i+2] - A[i+1]
```

and remove them from the array. The remaining elements are concatenated in their original order, which may create new groups of three consecutive elements that form an arithmetic progression.

You may perform this operation any number of times (possibly zero).

Find the **minimum possible length** of the array after an optimal sequence of operations.

### Input

- The first line contains an integer `N` (`1 ≤ N ≤ 200`).
- The second line contains `N` integers `A1, A2, …, AN` (`-10^9 ≤ Ai ≤ 10^9`).

### Output

- Print a single integer: the minimum possible length of the array.

---

## Examples

**Example 1**

```
Input
6
3 4 5 5 6 7

Output
0
```

Remove `(5, 6, 7)` to get `[3, 4, 5]`, then remove `(3, 4, 5)`.

**Example 2**

```
Input
5
1 2 3 4 5

Output
2
```

Remove any three consecutive values, e.g. `(1, 2, 3)`, leaving `[4, 5]`.

**Example 3**

```
Input
3
1 2 4

Output
3
```

No arithmetic progression exists, so nothing can be removed.

---

## Intuition

1. When a triple is removed, its neighbours join, so three elements that are **far apart** can become consecutive once everything between them has been removed.
2. First answer a smaller question: **can segment `[l..r]` be deleted completely?** Call it `can[l][r]`.
3. Consider how `A[l]` and `A[r]` leave the segment:
   - **Together** in one triple `(l, j, r)`: both gaps `[l+1..j-1]` and `[j+1..r-1]` must vanish first, and `2*A[j] == A[l] + A[r]`.
   - **Separately**: the segment splits into two removable blocks `[l..m]` and `[m+1..r]`.
4. Finally, run a prefix DP: each element is either kept (+1) or is the end of a fully removable block (+0).

---

## Recurrence

```
can[l][l-1] = true                      (empty segment)

can[l][r] = true if
    exists j in (l, r):  2*A[j] == A[l] + A[r]
                         && can[l+1][j-1] && can[j+1][r-1]
    OR
    exists m in [l, r):  can[l][m] && can[m+1][r]

best[0] = 0
best[i] = min( best[i-1] + 1,
               best[j]  for all j < i with can[j+1][i] )

answer = best[N]
```

Only segments whose length is a multiple of 3 can be fully removed.

---

## Solution (C++)

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> a(n + 2);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<vector<char>> can(n + 2, vector<char>(n + 2, 0));
    for (int i = 1; i <= n + 1; i++) can[i][i - 1] = 1;   // empty segment

    for (int l = n; l >= 1; l--) {
        for (int r = l + 2; r <= n; r += 3) {             // length must be a multiple of 3

            // Case 1: a[l], a[j], a[r] is the last triple removed
            for (int j = l + 1; j < r && !can[l][r]; j++)
                if (2 * a[j] == a[l] + a[r] && can[l + 1][j - 1] && can[j + 1][r - 1])
                    can[l][r] = 1;

            // Case 2: split into [l..m] and [m+1..r]
            for (int m = l + 2; m < r && !can[l][r]; m += 3)
                if (can[l][m] && can[m + 1][r])
                    can[l][r] = 1;
        }
    }

    vector<int> best(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        best[i] = best[i - 1] + 1;                 // keep a[i]
        for (int j = 0; j < i; j++)
            if (can[j + 1][i])
                best[i] = min(best[i], best[j]);   // delete block a[j+1..i]
    }

    cout << best[n] << "\n";
    return 0;
}
```

---

## Complexity

- **Time:** `O(N^3)` (about 2.7·10^6 operations for `N = 200`)
- **Space:** `O(N^2)`

---

## Similar Problems

| Problem                                                                   | Platform   | Rating |
| ------------------------------------------------------------------------- | ---------- | ------ |
| [Burst Balloons](https://leetcode.com/problems/burst-balloons/)            | LeetCode   | Hard   |
| [Strange Printer](https://leetcode.com/problems/strange-printer/)          | LeetCode   | Hard   |
| [Zuma Game](https://leetcode.com/problems/zuma-game/)                      | LeetCode   | Hard   |
| [Remove Boxes](https://leetcode.com/problems/remove-boxes/)                | LeetCode   | Hard   |
| [1132F Clear the String](https://codeforces.com/problemset/problem/1132/F) | Codeforces | ~2000  |
| [1312E Array Shrinking](https://codeforces.com/problemset/problem/1312/E)  | Codeforces | ~2100  |
