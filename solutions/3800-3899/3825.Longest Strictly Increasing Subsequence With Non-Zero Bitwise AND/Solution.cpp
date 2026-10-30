// 3825. Longest Strictly Increasing Subsequence With Non-Zero Bitwise AND | 3825. 按位与结果非零的最长上升子序列
// 核心思路：按位与非零等价于存在某一位全为 1，枚举该位筛出元素后求最长严格上升子序列，所有位取最大值
// 复杂度：时间 O(log M · n log n)，空间 O(n)
class Solution {
public:
    int longestSubsequence(vector<int>& nums) {  // 求按位与结果非零的最长严格递增子序列长度
        auto lis = [&](const vector<int>& arr) {  // 求 arr 的最长严格上升子序列长度（贪心 + 二分，即耐心排序）
            vector<int> g;  // g[i] 表示长度为 i+1 的上升子序列中可能的最小结尾值
            for (int x : arr) {  // 依次处理 arr 中的每个元素
                auto it = lower_bound(g.begin(), g.end(), x);  // 找到第一个大于等于 x 的位置
                if (it == g.end()) {  // x 比所有结尾都大
                    g.push_back(x);  // 说明可以接出更长的上升子序列
                } else {  // 否则替换同长度的结尾值
                    *it = x;  // 让该长度的结尾更小，便于后续继续延长
                }
            }
            return (int) g.size();  // g 的长度即最长严格上升子序列长度
        };

        int ans = 0;  // 答案初始为 0
        int mx = ranges::max(nums);  // 数组最大值，用于确定需要枚举的二进制位数
        int m = mx == 0 ? 0 : 32 - __builtin_clz(mx);  // 最大值的二进制位数（全为 0 时特判为 0 位）

        for (int i = 0; i < m; ++i) {  // 枚举子序列全体共同为 1 的那一位
            vector<int> arr;  // 该位为 1 的元素按原相对顺序组成的候选序列
            ranges::copy_if(nums, back_inserter(arr), [&](int x) {  // 筛选出第 i 位为 1 的元素
                return (x >> i) & 1;  // 只保留第 i 位为 1 的数
            });
            ans = max(ans, lis(arr));  // 用该位候选序列的 LIS 长度更新答案
        }

        return ans;  // 返回所有位中的最大长度
    }
};
