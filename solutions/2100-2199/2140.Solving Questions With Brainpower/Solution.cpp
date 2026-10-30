// 题目：2140. 解决智力问题（Solving Questions With Brainpower）
// 思路：记忆化搜索，dfs(i) 表示从第 i 题起能拿到的最大分数；做第 i 题得 p 分并跳到 i+b+1，不做则跳到 i+1，取较大者。
// 时间复杂度：O(n)，每个状态只计算一次；空间复杂度：O(n)，记忆化数组 f 与深度为 O(n) 的递归栈。
class Solution {  // LeetCode 约定的题解类
public:
    long long mostPoints(vector<vector<int>>& questions) {  // questions[i] = [分数 p, 需要跳过的题数 b]
        int n = questions.size();  // 题目数量，作为递归的越界边界
        long long f[n];  // 记忆化数组：f[i] 表示从第 i 题开始能获得的最大分数（0 表示尚未计算）
        memset(f, 0, sizeof(f));  // 全部清零
        auto dfs = [&](this auto&& dfs, int i) -> long long {  // C++23 显式对象参数，让 lambda 能把自身作为 dfs 递归调用
            if (i >= n) {  // 越界说明已经没有题可做
                return 0;  // 得分为 0
            }
            if (f[i]) {  // 该状态已经算过，直接复用结果
                return f[i];  // 返回记忆化的值
            }
            int p = questions[i][0], b = questions[i][1];  // p 是本题分数，b 是做完后必须跳过的题数
            return f[i] = max(p + dfs(i + b + 1), dfs(i + 1));  // 二选一：做第 i 题则跳过 b 题，不做则直接看下一题；结果写回 f[i]
        };
        return dfs(0);  // 从第 0 题开始求解
    }
};  // 题解类结束
