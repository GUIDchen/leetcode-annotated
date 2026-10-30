// 题目：546. 移除盒子（Remove Boxes）
// 思路：区间 DP + 记忆化搜索，状态 f[i][j][k] 表示「区间 [i, j] 右侧还挂着 k 个与 boxes[j] 同色的盒子」时的最大得分；先把右端连续同色并进 k，再枚举区间内同色位置与之合并。
// 时间复杂度：O(n^4)，状态数 O(n^3) 且每个状态枚举 O(n) 个合并点；空间复杂度：O(n^3)，记忆化表的大小。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int removeBoxes(vector<int>& boxes) {  // boxes 是颜色序列，返回按最优策略消除全部盒子能得到的最大得分
        int n = boxes.size();  // 盒子的数量 n
        vector<vector<vector<int>>> f(n, vector<vector<int>>(n, vector<int>(n)));  // 记忆化表 f[i][j][k]：区间 [i, j] 右端额外挂着 k 个同色盒子时的最大得分
        function<int(int, int, int)> dfs;  // 先声明 function 对象，lambda 才能在内部递归调用自身
        dfs = [&](int i, int j, int k) {  // 计算状态 (i, j, k)：i/j 为区间端点，k 为挂在右端的同色盒子数
            if (i > j) return 0;  // 空区间贡献 0 分
            while (i < j && boxes[j] == boxes[j - 1]) {  // 把右端连续同色的盒子并进 k，减少重复状态
                --j;  // 右端点左移一位
                ++k;  // 同色盒子计数加一
            }  // 连续同色合并结束
            if (f[i][j][k]) return f[i][j][k];  // 已经算过就直接返回（合法得分恒为正，所以 0 表示未计算）
            int ans = dfs(i, j - 1, 0) + (k + 1) * (k + 1);  // 方案一：先把右端这一组同色盒子整体消掉，再递归处理左边剩下的部分
            for (int h = i; h < j; ++h) {  // 方案二：在区间内找与 boxes[j] 同色的位置 h，先把中间段消掉，让同色盒子连成一片
                if (boxes[h] == boxes[j]) {  // 只有颜色相同才值得合并
                    ans = max(ans, dfs(h + 1, j - 1, 0) + dfs(i, h, k + 1));  // 先消除 (h, j) 之间的部分，再把 h 与右端 k 个同色盒子一起处理
                }  // 结束同色判断
            }  // 结束枚举合并点 h
            f[i][j][k] = ans;  // 记忆化保存当前状态的结果
            return ans;  // 返回该状态的最优得分
        };  // lambda 定义结束
        return dfs(0, n - 1, 0);  // 从整个数组开始求解，右端没有额外同色盒子
    }  // 结束 removeBoxes
};  // 类定义结束