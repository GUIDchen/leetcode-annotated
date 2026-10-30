// 题目：3193. 统计逆序对的数目（Count the Number of Inversions）
// 思路：按「前缀长度 → 前缀逆序对数」做动态规划，把元素逐个插入到排列最前面，插入位置决定新增逆序对数，并用 requirements 限定每层可取的数目。
// 时间复杂度：O(n·m·n)（m 为要求中的最大逆序对数）；空间复杂度：O(n·m)，即整张 dp 表 f。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numberOfPermutations(int n, vector<vector<int>>& requirements) {  // n：排列长度；requirements：形如 [endIndex, cnt] 的前缀逆序对约束
        vector<int> req(n, -1);  // req[i] 表示长度为 i+1 的前缀要求的逆序对数，-1 表示没有约束
        int m = 0;  // 记录所有约束中最大的逆序对数，作为 dp 的列上界
        for (const auto& r : requirements) {  // 遍历每条约束
            req[r[0]] = r[1];  // 把约束填到对应前缀下标上
            m = max(m, r[1]);  // 同步维护最大值 m
        }
        if (req[0] > 0) {  // 长度为 1 的前缀不可能有逆序对
            return 0;  // 约束自相矛盾，方案数为 0
        }
        req[0] = 0;  // 长度为 1 的前缀逆序对数固定为 0
        const int mod = 1e9 + 7;  // 取模常量，防止方案数溢出
        vector<vector<int>> f(n, vector<int>(m + 1, 0));  // f[i][j]：长度为 i+1 且逆序对数为 j 的排列个数
        f[0][0] = 1;  // 边界：只含一个元素且逆序对为 0 的排列恰好有一种
        for (int i = 1; i < n; ++i) {  // 逐步把前缀长度从 2 扩展到 n
            int l = 0, r = m;  // 本层 j（逆序对数）的枚举区间
            if (req[i] >= 0) {  // 该前缀带有逆序对数约束
                l = r = req[i];  // 只计算被约束的那一个 j 值
            }
            for (int j = l; j <= r; ++j) {  // 枚举长度为 i+1 的前缀允许的逆序对数
                for (int k = 0; k <= min(i, j); ++k) {  // 枚举新元素插入后新增的逆序对数 k，最多 min(i, j) 个
                    f[i][j] = (f[i][j] + f[i - 1][j - k]) % mod;  // 转移：从少 k 个逆序对的上一层累加过来
                }
            }
        }
        return f[n - 1][req[n - 1]];  // 返回长度为 n 且满足最终约束的排列个数
    }
};