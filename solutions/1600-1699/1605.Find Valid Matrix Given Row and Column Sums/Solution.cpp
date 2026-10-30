// 题目：1605. 给定行和列的和求可行矩阵（Find Valid Matrix Given Row and Column Sums）
// 思路：从左到右、从上到下贪心，每个格子填 min(剩余行和, 剩余列和)，再从两者中同时扣掉这个值，保证每步都不超过约束。
// 时间复杂度：O(mn)，每个格子访问一次；空间复杂度：O(mn)，答案矩阵本身的开销。
class Solution {  // 题解类
public:  // 对外接口
    vector<vector<int>> restoreMatrix(vector<int>& rowSum, vector<int>& colSum) {  // rowSum 是每一行元素之和，colSum 是每一列元素之和
        int m = rowSum.size(), n = colSum.size();  // m 为行数，n 为列数
        vector<vector<int>> ans(m, vector<int>(n));  // 答案矩阵，先全部初始化为 0
        for (int i = 0; i < m; ++i) {  // 逐行构造
            for (int j = 0; j < n; ++j) {  // 逐列构造
                int x = min(rowSum[i], colSum[j]);  // 贪心：该位置最多能放「本行剩余和」与「本列剩余和」中的较小者
                ans[i][j] = x;  // 把取到的值填入矩阵
                rowSum[i] -= x;  // 本行还需要凑的和减去刚用掉的部分
                colSum[j] -= x;  // 本列还需要凑的和减去刚用掉的部分
            }  // 列循环结束
        }  // 行循环结束
        return ans;  // 返回构造出来的可行矩阵
    }
};