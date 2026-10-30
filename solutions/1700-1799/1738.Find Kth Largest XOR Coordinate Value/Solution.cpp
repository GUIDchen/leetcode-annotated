// 题目：1738. 找出第 K 大的异或坐标值（Find Kth Largest XOR Coordinate Value）
// 思路：令 s[i][j] 表示左上角到 (i-1, j-1) 子矩阵的异或和，用容斥 s[i][j] = s[i-1][j] ^ s[i][j-1] ^ s[i-1][j-1] ^ a[i-1][j-1] 递推，收集全部坐标值后排序取第 k 大。
// 时间复杂度：O(mn log(mn))，排序占主导；空间复杂度：O(mn)，前缀异或表与答案数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int kthLargestValue(vector<vector<int>>& matrix, int k) {  // matrix 是输入矩阵，k 表示要取第 k 大
        int m = matrix.size(), n = matrix[0].size();  // 矩阵的行数与列数
        vector<vector<int>> s(m + 1, vector<int>(n + 1));  // 多开一行一列的前缀异或表，省去边界判断，初值全 0
        vector<int> ans;  // 收集每个坐标对应的异或值
        for (int i = 0; i < m; ++i) {  // 遍历每一行
            for (int j = 0; j < n; ++j) {  // 遍历每一列
                s[i + 1][j + 1] = s[i + 1][j] ^ s[i][j + 1] ^ s[i][j] ^ matrix[i][j];  // 容斥：左块与上块异或，重叠的左上块被异或两次抵消，最后并上当前格子
                ans.push_back(s[i + 1][j + 1]);  // 把该坐标的异或值加入结果集合
            }
        }
        sort(ans.begin(), ans.end());  // 升序排序，便于按下标直接取第 k 大
        return ans[ans.size() - k];  // 第 k 大对应下标 size - k
    }
};