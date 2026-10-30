// 题目：1901. 寻找峰值 II（Find a Peak Element II）
// 思路：对行号二分。取中间行的最大值所在列 j，若该值小于下一行同列的值，则峰值必在下方，否则峰值在上方（含当前行），不断收缩行区间，最后一行最大值即为峰值。
// 时间复杂度：O(n log m)，m 为行数、n 为列数；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> findPeakGrid(vector<vector<int>>& mat) {  // mat：二维矩阵，相邻元素互不相等
        int l = 0, r = mat.size() - 1;  // 对行号二分，区间为 [l, r]
        while (l < r) {  // 行区间还没收缩到一行
            int mid = (l + r) >> 1;  // 取中间行 mid
            int j = distance(mat[mid].begin(), max_element(mat[mid].begin(), mat[mid].end()));  // 用 max_element 找中间行最大值，distance 求出它所在的列 j
            if (mat[mid][j] > mat[mid + 1][j]) {  // 当前行比下一行高，峰值不可能在下方
                r = mid;  // 保留上半部分（含 mid）
            } else {  // 下一行更高，峰值一定在下方
                l = mid + 1;  // 丢掉上半部分
            }
        }
        int j = distance(mat[l].begin(), max_element(mat[l].begin(), mat[l].end()));  // 最终这一行最大值所在的列
        return {l, j};  // 该元素左右不小于邻居、下方不小于邻行，必为峰值
    }
};