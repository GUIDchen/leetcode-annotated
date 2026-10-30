// 题目：2639. 查询网格图中每一列的宽度（Find the Width of Columns of a Grid）
// 思路：先取第一行的长度得到列数，再逐行逐列把数字转成字符串量宽度，按列取最大值。
// 时间复杂度：O(m * n * L)，L 为单个数字的位数；空间复杂度：O(n)，只保存每列的答案。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> findColumnWidth(vector<vector<int>>& grid) {  // grid：m 行 n 列的整数网格
        int n = grid[0].size();  // 列数：题目保证至少一行，用第一行的长度即可
        vector<int> ans(n);  // 答案数组，初值 0，随后逐列维护最大宽度
        for (auto& row : grid) {  // 逐行扫描，宽度只需要按行累加比较
            for (int j = 0; j < n; ++j) {  // 遍历当前行的每一列
                int w = to_string(row[j]).size();  // 数字转字符串后取长度，即该数的显示宽度（负数含负号）
                ans[j] = max(ans[j], w);  // 用当前宽度更新第 j 列的最大宽度
            }
        }
        return ans;  // 返回每一列的宽度
    }
};