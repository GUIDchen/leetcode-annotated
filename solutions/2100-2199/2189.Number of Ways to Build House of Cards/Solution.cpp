// 题目：2189. 建造纸牌屋的方法数（Number of Ways to Build House of Cards）
// 思路：第 k 层三角形要 3k+2 张牌且层数必须递增，于是记忆化搜索 (剩余牌数, 下一层编号)：可以摆下这一层，也可以跳过它；恰好用完算一种方案。
// 时间复杂度：O(n²) 个状态、每个 O(1)；空间复杂度：O(n²)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int houseOfCards(int n) {  // n：可用纸牌总数
        int f[n + 1][n / 3 + 1];  // 记忆化数组：f[n][k] 表示剩 n 张牌、下一层是第 k 层时的方案数
        memset(f, -1, sizeof(f));  // -1 表示该状态还没计算过
        auto dfs = [&](this auto&& dfs, int n, int k) -> int {  // C++23 显式对象参数：让递归 lambda 能引用自身
            int x = 3 * k + 2;  // 第 k 层三角形需要 3k+2 张牌
            if (x > n) {  // 剩余牌不够摆这一层
                return 0;  // 这种摆法不成立
            }  // 分支结束
            if (x == n) {  // 恰好用完，说明这一种方案完整
                return 1;  // 记一种方案
            }  // 分支结束
            if (f[n][k] != -1) {  // 状态已经算过
                return f[n][k];  // 直接取记忆化结果
            }  // 分支结束
            return f[n][k] = dfs(n - x, k + 1) + dfs(n, k + 1);  // 摆下这一层 / 跳过这一层，两种选择求和并记忆
        };  // lambda 定义结束
        return dfs(n, 0);  // 从剩 n 张牌、第 0 层开始搜索
    }  // 方法结束
};  // 类定义结束
