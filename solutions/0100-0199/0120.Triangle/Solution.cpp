// 题目：120. 三角形最小路径和（Triangle）
// 思路：自底向上 DP，f[i][j] 表示从位置 (i, j) 走到最底部的最小路径和，等于下面两个相邻位置的最小值加上当前格子的值。
// 时间复杂度：O(n^2)，三角形所有格子各算一次；空间复杂度：O(n^2)，需要 (n+1) x (n+1) 的 DP 表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumTotal(vector<vector<int>>& triangle) {  // triangle 是金字塔形二维数组，返回自顶向下的最小路径和
        int n = triangle.size();  // n 是层数，也等于最后一层的元素个数
        vector<vector<int>> f(n + 1, vector<int>(n + 1, 0));  // DP 表多开一行一列，方便处理最后一层「下面没有节点」的边界，初值 0
        for (int i = n - 1; i >= 0; --i) {  // 自底向上递推，i 是行号
            for (int j = 0; j <= i; ++j) {  // 第 i 行只有 i+1 个元素
                f[i][j] = min(f[i + 1][j], f[i + 1][j + 1]) + triangle[i][j];  // 从下一层左下方、右下方里挑更小的，加上当前格子的值
            }
        }
        return f[0][0];  // 顶点处的值就是从顶到底的最小路径和
    }
};  // 类定义结束
