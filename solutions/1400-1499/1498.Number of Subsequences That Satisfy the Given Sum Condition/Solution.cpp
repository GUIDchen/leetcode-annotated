// 题目：1498. 满足条件的子序列数目（Number of Subsequences That Satisfy the Given Sum Condition）
// 思路：排序后固定最小值 nums[i]，二分找到最后一个满足 nums[i] + nums[j] <= target 的 j，中间元素任意取舍，每个 i 贡献 2^(j-i) 个子序列。
// 时间复杂度：O(n log n)，排序加 n 次二分；空间复杂度：O(n)，预计算 2 的幂表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numSubseq(vector<int>& nums, int target) {  // 统计和条件满足的非空子序列个数，结果对 1e9+7 取模
        sort(nums.begin(), nums.end());  // 排序后，子序列的最小值和最大值就对应区间的左右两端
        const int mod = 1e9 + 7;  // 取模常数
        int n = nums.size();  // 数组长度
        // 提前把 2 的幂全部算好，后面 O(1) 查询
        int f[n + 1];  // f[i] 保存 2^i % mod（变长数组，LeetCode 的 gnu++20 支持）
        f[0] = 1;  // 2^0 = 1
        for (int i = 1; i <= n; ++i) {  // 递推计算 2 的各次幂
            f[i] = (f[i - 1] * 2) % mod;  // 每次乘 2 后取模，防止溢出
        }  // 幂表构建完成
        int ans = 0;  // 累加答案
        for (int i = 0; i < n && nums[i] * 2 <= target; ++i) {  // 固定最小值为 nums[i]；若 2*nums[i] 已超过 target，更大的最小值更不可能满足，直接结束
            int j = upper_bound(nums.begin() + i + 1, nums.end(), target - nums[i]) - nums.begin() - 1;  // 在 i+1 之后二分，找到最后一个满足 nums[j] <= target - nums[i] 的下标 j
            ans = (ans + f[j - i]) % mod;  // 中间的 j-i 个元素可任选，共 2^(j-i) 个子序列；nums[i] 与 nums[j] 必选
        }  // for 结束
        return ans;  // 返回累加结果
    }  // 方法结束
};  // 类定义结束