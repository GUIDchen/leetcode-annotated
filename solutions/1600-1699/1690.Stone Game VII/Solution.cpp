// 题目：1690. 石子游戏 VII（Stone Game VII）
// 思路：区间 DP，dfs(i, j) 表示当前玩家在区间 [i, j] 上能取得的最大分差；拿左端或右端后用「剩余区间和 - 对手分差」转移。
// 时间复杂度：O(n^2) 个区间、每区间 O(1) 转移；空间复杂度：O(n^2) 记忆化数组 f 加 O(n) 前缀和。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int stoneGameVII(vector<int>& stones) {  // stones：每颗石子的分值
        int n = stones.size();  // 石子个数
        vector<vector<int>> f(n, vector<int>(n));  // f[i][j]：区间 [i, j] 上当前玩家能获得的最大分差，0 表示尚未计算
        vector<int> s(n + 1);  // s[i]：前 i 颗石子的分值前缀和
        for (int i = 0; i < n; ++i) {  // 逐步建立前缀和
            s[i + 1] = s[i] + stones[i];  // 累加第 i 颗石子
        }  // 前缀和循环结束
        auto dfs = [&](this auto&& dfs, int i, int j) -> int {  // 递归 lambda（用 C++23 显式对象参数 this auto&& 实现自递归），返回区间 [i, j] 的最大分差
            if (i > j) {  // 区间为空，没有石子可拿
                return 0;  // 空区间分差为 0
            }  // 空区间分支结束
            if (f[i][j]) {  // 该区间已经计算过
                return f[i][j];  // 直接返回记忆化结果，避免重复递归
            }  // 记忆化命中分支结束
            int a = s[j + 1] - s[i + 1] - dfs(i + 1, j);  // 拿左端：剩余区间和 s[j+1]-s[i+1] 减去对手在剩余区间的最优分差
            int b = s[j] - s[i] - dfs(i, j - 1);  // 拿右端：剩余区间和 s[j]-s[i] 减去对手在剩余区间的最优分差
            return f[i][j] = max(a, b);  // 两种取法取较大者，同时写入记忆化表并返回
        };  // 递归 lambda 定义结束
        return dfs(0, n - 1);  // 从整个区间开始求解
    }  // 方法结束
};  // 类结束
