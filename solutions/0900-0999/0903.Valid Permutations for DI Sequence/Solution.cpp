// 题目：903. DI 序列的有效排列（Valid Permutations for DI Sequence）
// 核心思路：区间 DP，f[i][j] 表示长度 i+1、末位元素排第 j 小的合法排列数，按 s[i-1] 是 D 还是 I 转移。
// 时间复杂度：O(n^3)，三重循环；空间复杂度：O(n^2) 的 DP 表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numPermsDISequence(string s) {  // s：由 'D' 与 'I' 组成的序列
        const int mod = 1e9 + 7;  // 取模常数，防止结果溢出
        int n = s.size();  // 序列长度，排列长度为 n + 1
        int f[n + 1][n + 1];  // DP 表：f[i][j] 表示长度 i + 1 且末位排第 j 小的方案数
        memset(f, 0, sizeof(f));  // 全部清零
        f[0][0] = 1;  // 只有 1 个数字时，唯一排列的末位排第 0 小
        for (int i = 1; i <= n; ++i) {  // 逐步把排列长度从 1 扩到 n + 1
            if (s[i - 1] == 'D') {  // 第 i 个关系是下降，新加的元素排在原末位之前
                for (int j = 0; j <= i; ++j) {  // 枚举新排列末位元素的排名 j
                    for (int k = j; k < i; ++k) {  // 原来的末位排名 k 必须不小于 j 才能插到它前面
                        f[i][j] = (f[i][j] + f[i - 1][k]) % mod;  // 累加所有可转移的前驱状态并取模
                    }
                }
            } else {  // 第 i 个关系是上升，新加的元素排在原末位之后
                for (int j = 0; j <= i; ++j) {  // 枚举新排列末位元素的排名 j
                    for (int k = 0; k < j; ++k) {  // 原来的末位排名 k 必须小于 j 才能插到它后面
                        f[i][j] = (f[i][j] + f[i - 1][k]) % mod;  // 累加所有可转移的前驱状态并取模
                    }
                }
            }
        }
        int ans = 0;  // 汇总答案
        for (int j = 0; j <= n; ++j) {  // 末位元素的排名可以是 0 到 n 任意一个
            ans = (ans + f[n][j]) % mod;  // 累加长度 n + 1 的全部合法方案并取模
        }
        return ans;  // 返回取模后的方案总数
    }
};