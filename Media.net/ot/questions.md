# Media.net OA — 3 Questions (Solutions in C++)

| # | Problem                   | Topic                                    | Time         |
| - | ------------------------- | ---------------------------------------- | ------------ |
| 1 | Array Combinations        | Combinatorics (stars & bars) + nCr mod p | O(MAX + Q)   |
| 2 | Rainwater Harvesting (2D) | Min-heap BFS from the border             | O(NM log NM) |
| 3 | Helping Each Other        | Inclusion–Exclusion                     | O(A)         |

---

## Q1. Array Combinations

### Problem

Given `N` and `M`, count pairs of arrays `Arr1`, `Arr2` (both length `N`) such that:

- `Arr1` is non-decreasing
- `Arr2` is non-increasing
- every element is in `[1, M]`
- `Arr1[i] <= Arr2[i]` for all `i`

Answer `Q` such questions (`N = A[i]`, `M = B[i]`), each modulo `1e9+7`.
Constraints: `Q, N, M <= 1e5`.

### Question in simple terms

`Arr1` only goes up, `Arr2` only goes down, and at every position `Arr1` must stay at or below `Arr2`. Count how many such pairs exist.

### Approach

1. **Only the last position matters.**
   `Arr1` keeps increasing and `Arr2` keeps decreasing, so they come closest at the last index.
   If `Arr1[N] <= Arr2[N]`, then for every earlier `i`:
   `Arr1[i] <= Arr1[N] <= Arr2[N] <= Arr2[i]`. ✔
2. **Glue the arrays into one.**
   Write `Arr1` and then `Arr2` reversed:
   `Arr1[1..N], Arr2[N], Arr2[N-1], ..., Arr2[1]`
   - `Arr1` part is non-decreasing
   - reversed `Arr2` is non-decreasing
   - the join point `Arr1[N] <= Arr2[N]` is exactly our condition
     So every valid pair ↔ one **non-decreasing array of length 2N** with values in `[1, M]` (one-to-one).
3. **Count non-decreasing arrays (stars & bars).**
   Number of non-decreasing arrays of length `L` with values in `[1, M]` = `C(M + L - 1, L)`.
   With `L = 2N`: **answer = C(M + 2N − 1, 2N)**.
4. **Fast nCr for many queries.**
   Largest top value = `1e5 + 2·1e5 − 1 < 3e5 + 5`.
   Precompute `fact[]` and `invFact[]` (via Fermat's little theorem) once, then each query is O(1).

**Check:** N = 1, M = 2 → pairs `(a, b)` with `a <= b`: (1,1), (1,2), (2,2) = 3.
Formula: `C(2 + 2 − 1, 2) = C(3, 2) = 3` ✔

### Complexity

- **Time: O(MAX + Q)** — factorials are built once (`MAX ≈ 3e5`), the single modular inverse costs O(log mod), then each query is one O(1) formula.
- **Space: O(MAX)** — the two factorial arrays.

### C++ Code

```cpp
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007LL;
const int MAXV = 300005;

long long power(long long b, long long e) {
    long long r = 1;
    b %= MOD;
    while (e > 0) {
        if (e & 1) r = r * b % MOD;
        b = b * b % MOD;
        e >>= 1;
    }
    return r;
}

vector<int> solve(vector<int>& A, vector<int>& B) {
    static vector<long long> fact(MAXV), invFact(MAXV);
    static bool built = false;
    if (!built) {
        fact[0] = 1;
        for (int i = 1; i < MAXV; i++) fact[i] = fact[i - 1] * i % MOD;
        invFact[MAXV - 1] = power(fact[MAXV - 1], MOD - 2);
        for (int i = MAXV - 1; i > 0; i--) invFact[i - 1] = invFact[i] * i % MOD;
        built = true;
    }

    auto nCr = [&](int n, int r) -> long long {
        if (r < 0 || r > n) return 0;
        return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
    };

    vector<int> ans(A.size());
    for (size_t i = 0; i < A.size(); i++) {
        int N = A[i], M = B[i];
        ans[i] = (int)nCr(M + 2 * N - 1, 2 * N);
    }
    return ans;
}
```

---

## Q2. Rainwater Harvesting (Trapping Rain Water II)

### Problem

Given an `N x M` height map, return the total volume of water trapped after raining.
Constraints: `N, M <= 110`, heights `<= 19999`.

Example:

```
A = [
  [1, 4, 3, 1, 3, 2],
  [3, 2, 1, 3, 2, 4],
  [2, 3, 3, 2, 3, 1]
]
Output: 4
```

### Question in simple terms

Think of the grid as land with heights. Rain fills the low spots, and water escapes off the edges. How much water stays?

### Approach

1. **Water level is set by the lowest wall around it.**
   Water at a cell can rise only up to the lowest point on the "wall" surrounding it — like a bucket leaking from its lowest side.
2. **Start from the border.**
   Border cells can never hold water (water spills out). Push all border cells into a **min-heap** keyed by height, and mark them visited.
3. **Always expand from the lowest wall.**
   Pop the lowest cell `(h, r, c)`. It is the weakest point of the current wall, so it decides the level for its unvisited neighbours.
4. **Process each neighbour `(nr, nc)`:**
   - If `A[nr][nc] < h` → it traps `h − A[nr][nc]` water.
   - Push it with height `max(h, A[nr][nc])` — after filling, it becomes part of the wall at that level.
   - Mark it visited.
5. Repeat until the heap is empty. The sum of trapped water is the answer.

### Complexity

- **Time: O(NM log(NM))** — every cell is pushed and popped from the heap once, each heap operation costs log(NM).
- **Space: O(NM)** — visited array plus the heap.

### C++ Code

```cpp
#include <bits/stdc++.h>
using namespace std;

int solve(vector<vector<int>>& A) {
    int n = A.size();
    if (n == 0) return 0;
    int m = A[0].size();
    if (n < 3 || m < 3) return 0;          // no inner cell can hold water

    // {height, row, col}, smallest height on top
    priority_queue<array<int, 3>, vector<array<int, 3>>, greater<array<int, 3>>> pq;
    vector<vector<bool>> vis(n, vector<bool>(m, false));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == 0 || j == 0 || i == n - 1 || j == m - 1) {
                pq.push({A[i][j], i, j});
                vis[i][j] = true;
            }
        }
    }

    int dr[4] = {1, -1, 0, 0};
    int dc[4] = {0, 0, 1, -1};
    long long water = 0;

    while (!pq.empty()) {
        auto [h, r, c] = pq.top();
        pq.pop();
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k], nc = c + dc[k];
            if (nr < 0 || nc < 0 || nr >= n || nc >= m || vis[nr][nc]) continue;
            vis[nr][nc] = true;
            if (A[nr][nc] < h) water += h - A[nr][nc];
            pq.push({max(h, A[nr][nc]), nr, nc});
        }
    }
    return (int)water;
}
```

---

## Q3. Helping Each Other

### Problem

There are `A` tasks and three people: **You, Tom, Jerry**.

- Every task must be assigned to **at least one** person (1, 2, or all 3 can share it).
- You solve exactly `B` tasks, Tom exactly `C`, Jerry exactly `D`.

Count the number of ways, modulo `1e9+7`.
Constraints: `A, B, C, D <= 30`.

### Question in simple terms

Each person picks their own set of tasks: You pick `B`, Tom picks `C`, Jerry picks `D` (out of `A` tasks). Picks may overlap, but no task may be left unpicked. Count the ways.

### Approach

1. **Without the "no task left" rule** it's easy — each person chooses independently:
   `C(A, B) · C(A, C) · C(A, D)`.
   But this also counts choices that leave some tasks uncovered.
2. **Remove bad cases using Inclusion–Exclusion.**
   Suppose we force some `k` specific tasks to be **unpicked by everyone**. Then all three choose only from the remaining `A − k` tasks:
   `C(A−k, B) · C(A−k, C) · C(A−k, D)` ways.
   There are `C(A, k)` ways to choose which `k` tasks are skipped.
3. **Alternate signs** (add for even `k`, subtract for odd `k`) to cancel every uncovered case exactly:

   **answer = Σ (k = 0 to A) (−1)^k · C(A, k) · C(A−k, B) · C(A−k, C) · C(A−k, D)**
4. Values are at most 30, so build `C[n][r]` with **Pascal's triangle** under mod.

**Check:** A = 2, B = C = D = 1 → each person picks 1 of 2 tasks (2³ = 8 ways), minus cases where all pick the same task (2 ways) = **6**.
Formula: k=0 → 1·2·2·2 = 8; k=1 → −2·1·1·1 = −2; k=2 → 0. Total = **6** ✔

### Complexity

- **Time: O(A²)** for Pascal's triangle (31×31, tiny) + **O(A)** for the sum → effectively O(1) at these limits.
- **Space: O(A²)** for the binomial table.

### C++ Code

```cpp
#include <bits/stdc++.h>
using namespace std;

int solve(int A, int B, int C, int D) {
    const long long MOD = 1000000007LL;

    // Pascal's triangle: comb[n][r] = C(n, r) mod MOD
    vector<vector<long long>> comb(A + 1, vector<long long>(A + 1, 0));
    for (int n = 0; n <= A; n++) {
        comb[n][0] = 1;
        for (int r = 1; r <= n; r++)
            comb[n][r] = (comb[n - 1][r - 1] + comb[n - 1][r]) % MOD;
    }

    auto nCr = [&](int n, int r) -> long long {
        if (r < 0 || r > n) return 0;
        return comb[n][r];
    };

    long long ans = 0;
    for (int k = 0; k <= A; k++) {
        int left = A - k;
        long long term = nCr(A, k) * nCr(left, B) % MOD
                         * nCr(left, C) % MOD
                         * nCr(left, D) % MOD;
        if (k % 2 == 0) ans = (ans + term) % MOD;
        else            ans = (ans - term + MOD) % MOD;
    }
    return (int)ans;
}
```

---

## One-line summaries

- **Q1:** Glue `Arr1` + reversed `Arr2` into one non-decreasing array of length `2N` → `C(M + 2N − 1, 2N)`.
- **Q2:** Min-heap from the border; always fill from the lowest wall.
- **Q3:** Total free choices minus "some task left out", via inclusion–exclusion.
