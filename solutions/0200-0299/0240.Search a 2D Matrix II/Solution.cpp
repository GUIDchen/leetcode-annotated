// 题目：240. 搜索二维矩阵 II（Search a 2D Matrix II）
// 思路：矩阵每行递增，于是逐行对目标值做二分查找；命中下标后还要判越界并确认值恰好相等。
// 时间复杂度：O(m log n)，m 行每行二分一次；空间复杂度：O(1)，只用常数个额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool searchMatrix(vector<vector<int>>& matrix, int target) {  // matrix：行、列都递增的矩阵；target：目标值
        for (auto& row : matrix) {  // 逐行处理
            int j = lower_bound(row.begin(), row.end(), target) - row.begin();  // 在本行二分找第一个大于等于 target 的位置
            if (j < matrix[0].size() && row[j] == target) {  // 先防止下标越界，再确认该位置的值恰好等于 target
                return true;  // 找到目标值，立即返回成功
            }
        }
        return false;  // 所有行都扫完仍未命中
    }
};  // 题解类定义结束