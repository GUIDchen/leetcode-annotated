// 题目：3806. 增加操作后最大按位与的结果（Maximum Bitwise AND After Increment Operations）
// 思路：从高位到低位贪心确定答案的每一位；计算把每个数补成 target 超集的最小增量，取最小的 m 个看总增量是否超过 k。
// 时间复杂度：O(32 · n log n)，每个二进制位排序一次代价数组；空间复杂度：O(n)，存放每个数的最小增量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumAND(const vector<int>& nums, int k, int m) {  // 总共可以加 k，从中选 m 个数使按位与最大，返回该最大值
        int max_val = ranges::max(nums) + k;  // 单个元素加完 k 之后的最大可能值
        int mx = max_val > 0 ? 32 - __builtin_clz(max_val) : 0;  // 该上界的二进制位数，决定需要枚举的位范围

        int ans = 0;  // 从高位到低位逐位确定答案
        vector<int> cost(nums.size());  // 把每个数变成当前 target 的超集所需的最小增量

        for (int bit = mx - 1; bit >= 0; bit--) {  // 从最高位开始，贪心地尝试把这一位设为 1
            int target = ans | (1 << bit);  // 假设答案在这一位可取 1 后的目标值
            for (size_t i = 0; i < nums.size(); i++) {  // 计算每个数的代价
                int x = nums[i];  // 当前数
                int diff = target & ~x;  // target 有、而 x 没有的位
                int j = diff == 0 ? 0 : 32 - __builtin_clz(diff);  // diff 的最高位位置 + 1（diff 为 0 时取 0，表示不用加）
                long long mask = (1L << j) - 1;  // 只保留到这个最高位的掩码
                cost[i] = (target & mask) - (x & mask);  // 只改低位就能让 x 覆盖 target 的这些位，所需增量即两段之差
            }  // 结束 for (size_t i = 0; i < nums.size(); i++)

            ranges::sort(cost);  // 按代价升序排列，贪心地选最便宜的前 m 个
            long long sum = accumulate(cost.begin(), cost.begin() + m, 0LL);  // 前 m 小的代价之和
            if (sum <= k) {  // 总代价不超过 k，说明这一位可以保留
                ans = target;  // 确认这一位为 1
            }  // 结束 if (sum <= k)
        }  // 结束 for (int bit = mx - 1; bit >= 0; bit--)

        return ans;  // 返回能得到的最大按位与
    }  // 结束 int maximumAND(const vector<int>& nums, int k, int m)
};  // 结束 class Solution
