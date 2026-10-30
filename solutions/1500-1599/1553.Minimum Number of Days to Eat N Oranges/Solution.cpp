// 题目：1553. 吃掉 N 个橘子的最少天数（Minimum Number of Days to Eat N Oranges）
// 思路：记忆化搜索。每天要么吃 1 个，要么先吃 n%2 个再整除以 2，要么先吃 n%3 个再整除以 3，取三者最优。
// 时间复杂度：O(log^2 n)（状态数约为 O(log n)，每个状态常数级转移）；空间复杂度：O(log n)（哈希表存记忆化结果）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解成员对外可见
    unordered_map<int, int> f;  // 记忆化表：键是剩余橘子数 n，值是吃完它所需的最少天数

    int minDays(int n) {  // n：一开始的橘子总数
        return dfs(n);  // 交给记忆化搜索求解
    }

    int dfs(int n) {  // 求吃完 n 个橘子的最少天数
        if (n < 2) {  // 只剩 0 个或 1 个橘子时，只能一天吃一个
            return n;  // 0 个需要 0 天，1 个需要 1 天
        }
        if (f.count(n)) {  // 该状态之前算过，直接复用，避免重复递归
            return f[n];  // 返回记忆化表里存的最优值
        }
        int res = 1 + min(n % 2 + dfs(n / 2), n % 3 + dfs(n / 3));  // 今天先用若干天凑整除，再分别走"除以 2"或"除以 3"分支，取更省的那条
        f[n] = res;  // 把算好的结果写进记忆化表
        return res;  // 返回该状态的最少天数
    }
};