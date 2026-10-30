// 题目：1727. 重新排列后的最大子矩阵（Largest Submatrix With Rearrangements）
// 思路：先把每格改成「以该格结尾、向上连续 1 的个数」；因为列可以任意重排，把每行降序排序后，前 j+1 列的最小高度就是 row[j]，面积即 (j+1)*row[j]。
// 时间复杂度：O(m*n*log n)，每行排序的代价；空间复杂度：O(1)，直接在原矩阵上就地修改。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int largestSubmatrix(vector<vector<int>>& matrix) {  // matrix：只含 0/1 的矩阵，列可以任意重排
        int m = matrix.size(), n = matrix[0].size();  // m 是行数，n 是列数
        for (int i = 1; i < m; ++i) {  // 从第二行开始向上累加
            for (int j = 0; j < n; ++j) {  // 逐列处理
                if (matrix[i][j]) {  // 当前格是 1 才能与上方的连续段接续
                    matrix[i][j] = matrix[i - 1][j] + 1;  // 改成以本格结尾、向上连续 1 的高度
                }  // 为 0 时保持 0，表示这一列的连续段在此断开
            }  // 列枚举结束
        }  // 高度预处理完成，matrix[i][j] 即该列向上的连续 1 个数
        int ans = 0;  // 记录最大全 1 子矩阵面积
        for (auto& row : matrix) {  // 把每一行当作子矩阵的底边
            sort(row.rbegin(), row.rend());  // 降序排序，相当于按高度把列重排到左侧
            for (int j = 0; j < n; ++j) {  // 枚举底边宽度 j + 1
                ans = max(ans, (j + 1) * row[j]);  // 前 j+1 列的最小高度是 row[j]，据此算面积
            }  // 宽度枚举结束
        }  // 所有底边处理完毕
        return ans;  // 返回最大面积
    }  // 方法结束
};  // 类结束