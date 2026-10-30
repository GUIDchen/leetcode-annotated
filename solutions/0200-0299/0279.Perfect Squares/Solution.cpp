// 题目：279. 完全平方数（Perfect Squares）
// 思路：把 1²,2²,...,m² 看作完全背包的物品（面值 i²、代价 1），用二维 DP 求凑出 n 的最少物品数。
// 时间复杂度：O(m·n)=O(n√n)，两层循环；空间复杂度：O(m·n)，二维 DP 表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numSquares(int n) {  // n：要凑出的和，返回最少需要的完全平方数个数
        int m = sqrt(n);  // 能用到的最大的平方根根号 n
        vector<vector<int>> f(m + 1, vector<int>(n + 1, 1 << 30));  // f[i][j]：只考虑前 i 个平方数时凑出 j 的最少个数，先全部置为无穷大
        f[0][0] = 0;  // 一个数都不选就凑出 0，代价为 0
        for (int i = 1; i <= m; ++i) {  // 逐个枚举可用的平方数 i²
            for (int j = 0; j <= n; ++j) {  // 枚举要凑出的和 j
                f[i][j] = f[i - 1][j];  // 不选 i²：直接继承前 i-1 个物品的最优解
                if (j >= i * i) {  // 当前容量还放得下一个 i²
                    f[i][j] = min(f[i][j], f[i][j - i * i] + 1);  // 选 i²：同层转移，因为同一个平方数可以重复使用
                }
            }
        }
        return f[m][n];  // 用前 m 个平方数凑出 n 的最少个数
    }
};
