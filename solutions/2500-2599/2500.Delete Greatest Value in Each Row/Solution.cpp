// 题目：2500. 删除每行中的最大值（Delete Greatest Value in Each Row）
// 思路：先把每行升序排序，之后第 j 轮删除各行的最大值（即各行的第 j 列），本轮得分为列最大值，逐轮累加。
// 时间复杂度：O(m·n log n)，m 行 n 列，每行排序 O(n log n)；空间复杂度：O(1)，不计排序的栈开销。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int deleteGreatestValue(vector<vector<int>>& grid) {  // grid：m 行 n 列的矩阵；返回每轮删除的最大值之和
        for (auto& row : grid) {  // 引用遍历每一行，排序结果直接写回矩阵
            ranges::sort(row);  // C++20 的 ranges::sort：把该行升序排序，最大值落到行尾
        }  // 本行排序完成
        int ans = 0;  // ans：累加每一轮删除得到的分数
        for (int j = 0; j < grid[0].size(); ++j) {  // 共 n 轮，每轮删除各行当前的最大值（排序后即第 j 列）
            int t = 0;  // t：本轮各列中的最大值，也就是本轮删除的最大值
            for (int i = 0; i < grid.size(); ++i) {  // 遍历所有行，取排序后各行的第 j 列
                t = max(t, grid[i][j]);  // 不断更新本轮的最大值
            }  // 行遍历结束
            ans += t;  // 把本轮得分累加到答案
        }  // 轮次（列）循环结束
        return ans;  // 返回所有轮次得分之和
    }  // 方法结束
};  // 类定义结束
