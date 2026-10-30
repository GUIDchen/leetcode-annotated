// 3877. 达到目标异或值的最少删除次数（Minimum Removals to Achieve Target XOR）
// 核心思路：删除次数最少等价于保留元素最多。先确定异或值需要的二进制位数 m；用 f[i][j] 表示前 i 个数中异或和为 j 时最多能保留多少个元素，最终答案是 n - f[n][target]。
// 复杂度：时间复杂度 O(n·2^m)，空间复杂度 O(n·2^m)。
class Solution {  // 题解类
public:  // 公有成员
    int minRemovals(vector<int>& nums, int target) {  // 返回使异或和等于 target 的最少删除次数
        int mx = ranges::max(nums);  // 数组中的最大元素
        int m = 0;  // m 表示表示这些数值所需的最小二进制位数
        while ((1 << m) <= mx) {  // 不断左移，直到 2^m 大于最大值
            ++m;  // 位数加一
        }  // 位数计算结束
        if ((1 << m) <= target) {  // target 超出了所有可能异或和的取值范围
            return -1;  // 无论怎么删都无法得到 target
        }  // 范围判断结束

        int n = nums.size();  // 数组长度
        vector<vector<int>> f(n + 1, vector<int>(1 << m, INT_MIN));  // f[i][j]：前 i 个数异或和为 j 时最多保留的元素个数
        f[0][0] = 0;  // 空集异或和为 0，保留 0 个元素

        for (int i = 1; i <= n; i++) {  // 逐个考虑数组元素
            int x = nums[i - 1];  // 当前考虑的元素
            for (int j = 0; j < (1 << m); j++) {  // 枚举所有可能的异或和
                f[i][j] = max(f[i - 1][j], f[i - 1][j ^ x] + 1);  // 不选 x 或选 x（选则保留数加一）
            }  // 枚举异或和结束
        }  // 动态规划结束

        if (f[n][target] < 0) {  // 没有任何子集的异或和等于 target
            return -1;  // 无法达成目标
        }  // 可行性判断结束
        return n - f[n][target];  // 总个数减去最多保留的个数即为最少删除次数
    }  // 方法结束
};  // 类结束
