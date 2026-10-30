// 题目：2022. 将一维数组转变成二维数组（Convert 1D Array Into 2D Array）
// 思路：先判断元素个数是否恰好等于 m * n，不等则无法构造并返回空数组；否则按行优先顺序把一维数组逐行填入 m 行 n 列的矩阵。
// 时间复杂度：O(m * n)，每个元素访问一次；空间复杂度：O(m * n)，用于存放结果矩阵。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> construct2DArray(vector<int>& original, int m, int n) {  // original：一维数组；m、n：目标矩阵的行数与列数
        if (m * n != original.size()) {  // 元素个数与 m * n 不匹配时无法无冲突地构造
            return {};  // 返回空二维数组表示失败
        }  // 长度检查结束
        vector<vector<int>> ans(m, vector<int>(n));  // 预先分配 m 行 n 列的结果矩阵
        for (int i = 0; i < m; ++i) {  // 逐行填充
            for (int j = 0; j < n; ++j) {  // 逐列填充
                ans[i][j] = original[i * n + j];  // 一维下标 i * n + j 正好对应第 i 行第 j 列
            }  // 列循环结束
        }  // 行循环结束
        return ans;  // 返回构造好的二维矩阵
    }  // construct2DArray 方法结束
};  // Solution 类定义结束