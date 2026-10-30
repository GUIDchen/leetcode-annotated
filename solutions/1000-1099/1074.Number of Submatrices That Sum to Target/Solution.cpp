// 题目：1074. 元素和为目标值的子矩阵数量（Number of Submatrices That Sum to Target）
// 思路：枚举子矩阵的上边界 i，再向下扩展下边界 j，用 col[k] 维护当前行区间内第 k 列的元素和；此时问题降维成「一维数组中元素和为 target 的连续子数组个数」，用前缀和加哈希表 O(n) 统计。
// 时间复杂度：O(m^2 * n)，枚举上下边界 O(m^2) 且每次统计 O(n)；空间复杂度：O(n)，用于存放列和与哈希表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {  // matrix 是元素矩阵，target 是目标和
        int m = matrix.size(), n = matrix[0].size();  // m 行数，n 列数
        int ans = 0;  // 满足条件的子矩阵个数
        for (int i = 0; i < m; ++i) {  // 枚举子矩阵的上边界行 i
            vector<int> col(n);  // col[k] 累加从第 i 行到当前第 j 行在第 k 列上的和，初始全 0
            for (int j = i; j < m; ++j) {  // 枚举子矩阵的下边界行 j，从上边界向下扩展
                for (int k = 0; k < n; ++k) {  // 把第 j 行逐列累加到 col 上
                    col[k] += matrix[j][k];  // 得到行区间 [i, j] 内每一列的元素和
                }
                ans += f(col, target);  // 统计列和数组 col 中和为 target 的连续子数组个数，即对应的子矩阵个数
            }
        }
        return ans;  // 返回所有子矩阵的计数
    }

    int f(vector<int>& nums, int target) {  // 辅助函数：统计一维数组中和为 target 的连续子数组个数
        unordered_map<int, int> d{{0, 1}};  // 前缀和 -> 出现次数；预置 0:1 表示空前缀
        int cnt = 0, s = 0;  // cnt 计数，s 是从头开始的前缀和
        for (int& x : nums) {  // 顺序扫描数组的每个元素
            s += x;  // 累加得到当前前缀和
            if (d.count(s - target)) {  // 前面出现过前缀和 s-target，说明二者之间这段的和正好是 target
                cnt += d[s - target];  // 该前缀和出现几次，就有几个以当前位置结尾的合法子数组
            }
            ++d[s];  // 把当前前缀和计入哈希表，供后面的位置查询
        }
        return cnt;  // 返回合法子数组个数
    }
};