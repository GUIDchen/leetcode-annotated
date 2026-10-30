// 题目：1380. 矩阵中的幸运数（Lucky Numbers in a Matrix）
// 思路：先统计每行的最小值 rows[i] 与每列的最大值 cols[j]，再挑出同时等于两者、即行列最值相等的元素。
// 时间复杂度：O(m*n)，矩阵只被扫描两遍；空间复杂度：O(m+n)，保存行最小值与列最大值。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> luckyNumbers(vector<vector<int>>& matrix) {  // matrix：m 行 n 列的输入矩阵
        int m = matrix.size(), n = matrix[0].size();  // m 是行数，n 是列数（题目保证列数不为 0）
        int rows[m];  // rows[i] 保存第 i 行的最小值，初值设为无穷大
        int cols[n];  // cols[j] 保存第 j 列的最大值，初值设为 0
        memset(rows, 0x3f, sizeof(rows));  // 0x3f3f3f3f 是「足够大」的哨兵，方便后续取 min
        memset(cols, 0, sizeof(cols));  // 矩阵元素都是正数，初值 0 不会干扰取 max
        for (int i = 0; i < m; ++i) {  // 逐行扫描
            for (int j = 0; j < n; ++j) {  // 逐列扫描，即遍历整个矩阵
                rows[i] = min(rows[i], matrix[i][j]);  // 用当前元素更新第 i 行的最小值
                cols[j] = max(cols[j], matrix[i][j]);  // 用当前元素更新第 j 列的最大值
            }  // 本行扫描结束
        }  // 所有行列的最值统计完毕
        vector<int> ans;  // 收集所有幸运数
        for (int i = 0; i < m; ++i) {  // 第二次逐行扫描
            for (int j = 0; j < n; ++j) {  // 第二次逐列扫描
                if (rows[i] == cols[j]) {  // 行最小值与列最大值相等，说明该元素既是本行最小又是本列最大
                    ans.push_back(rows[i]);  // 题目保证矩阵中至多一个幸运数，直接记录这个值
                }  // 判断结束
            }  // 本行检查结束
        }  // 全矩阵检查结束
        return ans;  // 返回找到的幸运数列表（没有则为空数组）
    }  // luckyNumbers 结束
};  // Solution 类结束