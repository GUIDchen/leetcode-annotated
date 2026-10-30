class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numWays(int steps, int arrLen) {  // steps：总步数；arrLen：数组长度，位置合法范围是 [0, arrLen-1]
        int f[steps][steps + 1];  // 记忆化数组：f[i][j] 存位置 i、剩余 j 步时的方案数（边长取 steps 的变长数组）
        memset(f, -1, sizeof f);  // 全部初始化为 -1，表示该状态还没计算过
        const int mod = 1e9 + 7;  // 取模常量，防止方案数溢出
        function<int(int, int)> dfs = [&](int i, int j) -> int {  // dfs(i, j)：当前位置 i，还剩 j 步，返回之后的走法数
            if (i > j || i >= arrLen || i < 0 || j < 0) {  // 越界，或剩余步数不足以回到 0 号位置，方案数为 0
                return 0;  // 非法状态没有任何方案
            }  // 结束 if 块
            if (i == 0 && j == 0) {  // 走完所有步且正好停在 0 号位置
                return 1;  // 这是一种合法走法
            }  // 结束 if 块
            if (f[i][j] != -1) {  // 该状态之前算过
                return f[i][j];  // 直接返回缓存结果
            }  // 结束 if 块
            int ans = 0;  // 累加三种走法的方案数
            for (int k = -1; k <= 1; ++k) {  // 枚举 -1 左移、0 原地、+1 右移
                ans = (ans + dfs(i + k, j - 1)) % mod;  // 先递归子状态再取模，避免溢出
            }  // 结束 for 循环
            return f[i][j] = ans;  // 结果写入记忆化数组后返回
        };  // lambda 定义结束
        return dfs(0, steps);  // 从位置 0、剩余 steps 步开始搜索
    }  // numWays 方法结束
};  // Solution 类定义结束