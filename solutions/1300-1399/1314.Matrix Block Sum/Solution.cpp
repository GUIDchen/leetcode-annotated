// 题目：1314. 矩阵区域和（Matrix Block Sum）
// 思路：先构造二维前缀和数组，再用容斥原理 O(1) 求出每个位置 k 邻域矩形的元素和。
// 时间复杂度：O(m·n)；空间复杂度：O(m·n)，前缀和数组与答案矩阵各占一份。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int k) {  // 方法签名：mat 为输入矩阵，k 为邻域半径
        int m = mat.size();  // 矩阵行数 m
        int n = mat[0].size();  // 矩阵列数 n（题目保证矩阵非空，可直接取第 0 行）

        vector<vector<int>> s(m + 1, vector<int>(n + 1));  // 前缀和数组 s，多开一行一列，使 s[i][j] 表示 mat 前 i 行前 j 列之和
        for (int i = 0; i < m; ++i) {  // 逐行累加，构造二维前缀和
            for (int j = 0; j < n; ++j) {  // 逐列累加
                s[i + 1][j + 1] = s[i][j + 1] + s[i + 1][j] - s[i][j] + mat[i][j];  // 递推式：上 + 左 - 左上 + 当前格，减去被重复计算的左上部分
            }  // 内层列循环结束
        }  // 外层行循环结束

        vector<vector<int>> ans(m, vector<int>(n));  // 答案矩阵，尺寸与 mat 相同
        for (int i = 0; i < m; ++i) {  // 枚举答案的每一行
            for (int j = 0; j < n; ++j) {  // 枚举答案的每一列
                int x1 = max(i - k, 0);  // 邻域上边界：i - k 可能越界，夹到 0
                int y1 = max(j - k, 0);  // 邻域左边界：j - k 可能越界，夹到 0
                int x2 = min(m - 1, i + k);  // 邻域下边界：i + k 可能越界，夹到 m - 1
                int y2 = min(n - 1, j + k);  // 邻域右边界：j + k 可能越界，夹到 n - 1
                ans[i][j] = s[x2 + 1][y2 + 1] - s[x1][y2 + 1] - s[x2 + 1][y1] + s[x1][y1];  // 容斥求矩形和：四角加减，注意前缀和下标整体 +1
            }  // 内层列循环结束
        }  // 外层行循环结束
        return ans;  // 返回每个位置 k 邻域内元素之和
    }  // 方法结束
};  // 类定义结束