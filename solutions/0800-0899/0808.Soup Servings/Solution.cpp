// 题目：808. 分汤（Soup Servings）
// 思路：记忆化搜索，dfs(i, j) 表示两种汤各剩 i、j 份时 A 先耗尽的概率，每次操作等概率（各 1/4）；n 足够大时概率已趋近于 1，直接返回。
// 时间复杂度：O(N²)，N 为按 25 归一化后的份数（不超过 200）；空间复杂度：O(N²)，记忆化表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    double soupServings(int n) {  // n：初始份数（毫升）；返回 A 先耗尽的概率
        double f[200][200] = {0.0};  // 记忆化表，值为 0 表示尚未计算（概率恒为正）
        auto dfs = [&](this auto&& dfs, int i, int j) -> double {  // C++23 推导 this 的递归 lambda，先把自身捕获进来才能递归
            if (i <= 0 && j <= 0) return 0.5;  // 两种汤同时耗尽，按题意各算一半
            if (i <= 0) return 1;  // A 先耗尽，算成功
            if (j <= 0) return 0;  // B 先耗尽，算失败
            if (f[i][j] > 0) return f[i][j];  // 已经算过就直接复用
            double ans = 0.25 * (dfs(i - 4, j) + dfs(i - 3, j - 1) + dfs(i - 2, j - 2) + dfs(i - 1, j - 3));  // 四种操作等概率，各占 1/4，累加子问题结果
            f[i][j] = ans;  // 把结果记入记忆化表
            return ans;  // 返回本次计算结果
        };  // lambda 定义结束
        return n > 4800 ? 1 : dfs((n + 24) / 25, (n + 24) / 25);  // n 超过 4800 时概率已足够接近 1 直接返回；否则按 25 份向上取整后搜索
    }  // 方法结束
};  // 类定义结束