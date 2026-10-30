// 题目：2318. 不同骰子序列的数目（Number of Distinct Roll Sequences）
// 核心思路：动态规划，dp[k][i][j] 表示长度为 k、最后两面点数为 i+1 与 j+1 的合法序列数；转移时再枚举倒数第三面 h，要求三面相邻互质且两两不等。
// 时间复杂度：O(n·6³)，每层状态由 6 个前驱转移而来；空间复杂度：O(n·6²)，三维 dp 表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int distinctSequences(int n) {  // n：骰子投掷次数；返回相邻两面互质且互不相同的序列个数
        if (n == 1) return 6;  // 只有 1 次投掷时，6 个面各自构成一种序列，直接返回
        int mod = 1e9 + 7;  // 结果对 1e9+7 取模，防止累加溢出
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(6, vector<int>(6)));  // dp[k][i][j]：长度为 k 且最后两面为点数 i+1、j+1 的合法序列数，三维表全部初始化为 0
        for (int i = 0; i < 6; ++i)  // 枚举倒数第二个面的下标 i（0..5 对应点数 1..6）
            for (int j = 0; j < 6; ++j)  // 枚举最后一个面的下标 j
                if (gcd(i + 1, j + 1) == 1 && i != j)  // 长度为 2 的合法条件：相邻两面点数互质且不相等
                    dp[2][i][j] = 1;  // 长度为 2 时每种合法组合恰好 1 种序列
        for (int k = 3; k <= n; ++k)  // 从长度 3 开始逐层递推到长度 n
            for (int i = 0; i < 6; ++i)  // 枚举新序列最后两面中的前一个面 i
                for (int j = 0; j < 6; ++j)  // 枚举新序列最后两面中的后一个面 j
                    if (gcd(i + 1, j + 1) == 1 && i != j)  // 末两面 (i, j) 同样必须互质且不相等
                        for (int h = 0; h < 6; ++h)  // 枚举倒数第三个面 h，用来向 dp[k][i][j] 转移
                            if (gcd(h + 1, i + 1) == 1 && h != i && h != j)  // 转移合法性：h 与 i 互质（相邻互质），且 h 既不等于 i（相邻不等）也不等于 j（间隔两面也不等）
                                dp[k][i][j] = (dp[k][i][j] + dp[k - 1][h][i]) % mod;  // 累加上一状态 dp[k-1][h][i]，并即时取模
        int ans = 0;  // 答案累加器，初始为 0
        for (int i = 0; i < 6; ++i)  // 枚举长度 n 序列的倒数第二个面 i
            for (int j = 0; j < 6; ++j)  // 枚举长度 n 序列的最后一个面 j
                ans = (ans + dp[n][i][j]) % mod;  // 把 dp[n][i][j] 累加到答案并取模
        return ans;  // 返回长度为 n 的合法序列总数
    }  // distinctSequences 结束

    int gcd(int a, int b) {  // 辅助函数：欧几里得算法求最大公约数，用于判断两面点数是否互质
        return b == 0 ? a : gcd(b, a % b);  // b 为 0 时 a 即最大公约数，否则递归计算 gcd(b, a % b)
    }  // gcd 结束
};  // 类定义结束