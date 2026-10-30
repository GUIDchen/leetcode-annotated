// 题目：2033. 获取单值网格的最小操作数（Minimum Operations to Make a Uni-Value Grid）
// 思路：每次把某个数加减 x，所以所有数对 x 取余必须相同，否则无解；把网格摊平排序后，最优目标值就是中位数（中位数使绝对偏差之和最小），答案为 ∑|v - mid| / x。
// 时间复杂度：O(mn log(mn))，主要开销是排序；空间复杂度：O(mn)，用一维数组存放整个网格。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minOperations(vector<vector<int>>& grid, int x) {  // grid 是二维网格，x 是每次操作允许的增减量
        int m = grid.size(), n = grid[0].size();  // m 为行数，n 为列数
        int mod = grid[0][0] % x;  // 取左上角元素对 x 的余数作为基准：所有元素必须同余，否则永远凑不到同一个值
        int nums[m * n];  // 摊平用的一维数组，长度 m*n（LeetCode 数据规模下可直接开在栈上）
        for (int i = 0; i < m; ++i) {  // 枚举行
            for (int j = 0; j < n; ++j) {  // 枚举列
                if (grid[i][j] % x != mod) {  // 某个元素与基准余数不同，说明它在 x 的步长下无法与其它元素对齐
                    return -1;  // 直接判无解
                }  // 结束同余判断
                nums[i * n + j] = grid[i][j];  // 把二维坐标(i, j)映射成一维下标 i*n+j，做行优先摊平
            }  // 结束内层列循环
        }  // 结束外层行循环
        sort(nums, nums + m * n);  // 排序后按下标就能直接取到中位数
        int mid = nums[(m * n) >> 1];  // 取中位数作为最终统一成的目标值：它让绝对偏差之和最小
        int ans = 0;  // 记录总操作次数
        for (int v : nums) {  // 遍历每个元素
            ans += abs(v - mid) / x;  // 每次操作只能改变 x，所以需要 |v - mid| / x 次（同余保证能整除）
        }  // 结束累加循环
        return ans;  // 返回最少操作次数
    }  // 结束 minOperations
};  // 结束 Solution 类