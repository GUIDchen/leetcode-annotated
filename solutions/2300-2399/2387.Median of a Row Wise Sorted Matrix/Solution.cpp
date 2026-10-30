// 题目：2387. 行排序矩阵的中位数（Median of a Row Wise Sorted Matrix）🔒
// 思路：在 [0, 1e6] 上二分答案；count(x) 用每行的 upper_bound 统计 ≤ x 的元素个数，第一个使 count(x) ≥ 中位序号的 x 就是中位数。
// 时间复杂度：O(m·log n·log V)，V 为值域大小；空间复杂度：O(1)，只使用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int matrixMedian(vector<vector<int>>& grid) {  // grid：每行升序的 m×n 矩阵
        int m = grid.size(), n = grid[0].size();  // m 是行数，n 是列数（各行列数相同）
        int left = 0, right = 1e6 + 1;  // 二分区间 [left, right)：答案不会超过题目给定的最大值 1e6
        int target = (m * n + 1) >> 1;  // 中位数是第 ⌈(m*n+1)/2⌉ 小的元素，因为 m*n 为奇数
        auto count = [&](int x) {  // 闭包：统计整个矩阵中不大于 x 的元素个数
            int cnt = 0;  // 计数器累加各行的贡献
            for (auto& row : grid) {  // 逐行处理
                cnt += (upper_bound(row.begin(), row.end(), x) - row.begin());  // 每行有序，upper_bound 的下标即该行 ≤ x 的个数
            }  // 行循环结束
            return cnt;  // 返回矩阵中 ≤ x 的元素总数
        };  // 闭包定义结束
        while (left < right) {  // 二分：寻找最小的 x 使得 count(x) ≥ target
            int mid = (left + right) >> 1;  // 取区间中点，向下取整
            if (count(mid) >= target) {  // mid 处已经覆盖到中位数所在排名，答案可能是 mid 或更小
                right = mid;  // 收缩右界，保留 mid
            } else {  // 覆盖不足，说明中位数严格大于 mid
                left = mid + 1;  // 收缩左界，排除 mid
            }  // 分支结束
        }  // 二分结束，left == right 即答案
        return left;  // 收敛点就是矩阵的中位数
    }  // 方法结束
};  // 类定义结束