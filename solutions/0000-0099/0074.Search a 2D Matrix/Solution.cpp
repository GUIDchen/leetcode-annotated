// 题目：74. 搜索二维矩阵（Search a 2D Matrix）
// 思路：把 m×n 矩阵看成长度为 m*n 的有序一维数组，做「找第一个 >= target 的位置」的下界二分，最后再判断该位置是否恰好等于 target。
// 时间复杂度：O(log(m*n))，只做一次二分；空间复杂度：O(1)，只用了常数个下标变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool searchMatrix(vector<vector<int>>& matrix, int target) {  // matrix 是行、列都递增的二维矩阵，target 是待查找的目标值
        int m = matrix.size(), n = matrix[0].size();  // m 是行数，n 是列数，后面用它们做一维下标与二维坐标的换算
        int left = 0, right = m * n - 1;  // 把矩阵展平成一维后，二分查找的闭区间是 [left, right]
        while (left < right) {  // 区间里还剩不止一个元素时继续二分，结束时 left == right 即为候选答案
            int mid = left + right >> 1;  // 取中点；'+' 的优先级高于 '>>'，等价于 (left + right) / 2 向下取整
            int x = mid / n, y = mid % n;  // 把一维下标 mid 换算成第 x 行、第 y 列
            if (matrix[x][y] >= target) {  // 中点值不小于目标，说明首个 >= target 的位置在左半边，且 mid 本身可能就是答案
                right = mid;  // 保留 mid，把区间收缩成 [left, mid]
            } else {  // 中点值小于目标，答案一定落在 mid 的右侧
                left = mid + 1;  // 丢弃 mid，把区间收缩成 [mid + 1, right]
            }
        }
        return matrix[left / n][left % n] == target;  // 二分结束时 left 是首个 >= target 的位置，判断它是否真的等于 target
    }
};