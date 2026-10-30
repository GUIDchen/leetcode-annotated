// 题目：2742. 给墙壁刷油漆（Painting the Walls）
// 核心思路：记忆化搜索，把「付费刷一面墙可免费刷 time[i] 面」折算成剩余免费额度，付费或免费两种选择取最小花费。
// 时间复杂度：O(n^2)，状态数为 n * (2n+1) 个；空间复杂度：O(n^2)，记忆化数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int paintWalls(vector<int>& cost, vector<int>& time) {  // cost：付费刷每面墙的花费；time：付费后可免费刷的墙数
        int n = cost.size();  // 墙的总数
        int f[n][n << 1 | 1];  // 记忆化数组：f[墙下标][偏移后的免费额度]，-1 表示该状态尚未求解
        memset(f, -1, sizeof(f));  // 全部初始化为 -1，标记未计算
        function<int(int, int)> dfs = [&](int i, int j) -> int {  // dfs(当前墙下标 i, 额度 j)：返回刷完剩余墙的最小花费
            if (n - i <= j - n) {  // 用 j 减去偏移量 n 得到真实免费额度，够覆盖剩下的所有墙
                return 0;  // 剩余墙都能免费刷，不再产生花费
            }
            if (i >= n) {  // 墙已全部考虑完，但免费额度仍不够
                return 1 << 30;  // 返回足够大的值，表示该方案不可行
            }
            if (f[i][j] == -1) {  // 该状态还没算过，才开始求解，避免重复递归
                f[i][j] = min(dfs(i + 1, j + time[i]) + cost[i], dfs(i + 1, j - 1));  // 二选一：付费刷第 i 面墙（额度增加 time[i]），或让第 i 面墙被免费刷（额度减 1）
            }
            return f[i][j];  // 返回记忆化后的结果
        };
        return dfs(0, n);  // 从第 0 面墙开始，额度 0 用偏移量 n 表示
    }
};