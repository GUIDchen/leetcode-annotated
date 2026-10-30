// 4063. 至多一次取反能被 K 整除的最长子数组 I  Longest Subarray Divisible by K with At Most One Negation I
// 核心思路：枚举被取反的下标（含不取反的情况），用前缀和余数首次出现的位置求最长可整除子数组。
// 复杂度：时间 O(n^2)，空间 O(k)。

class Solution {
public:
    int longestSubarray(vector<int>& nums, int k) {  // 返回至多取反一个元素后，和能被 k 整除的最长子数组长度
        int n = nums.size();  // 数组长度
        vector<int> d(k, -2);  // d[余数] 记录该余数首次出现的下标，-2 表示尚未出现

        auto f = [&](int skip) {  // 辅助函数：把下标 skip 的元素取反（skip 为 -1 表示不取反）后的答案
            fill(d.begin(), d.end(), -2);  // 每轮先重置余数表，避免上一轮数据干扰
            d[0] = -1;  // 空前缀的余数为 0，其虚拟下标为 -1
            int s = 0, res = 0;  // s 为当前前缀和余数，res 为最长长度
            for (int i = 0; i < n; ++i) {  // 依次枚举每个位置
                int x = i == skip ? -nums[i] : nums[i];  // 命中 skip 时取反，否则保持原值
                s = (s + x) % k;  // 更新前缀和余数
                if (s < 0) {  // C++ 取模可能为负
                    s += k;  // 调整为非负余数
                }
                if (d[s] != -2) {  // 该余数此前出现过
                    res = max(res, i - d[s]);  // 用当前下标减去最早下标更新答案
                } else {  // 该余数首次出现
                    d[s] = i;  // 记录其最早下标
                }
            }
            return res;  // 返回本轮的最长长度
        };

        int ans = f(-1);  // 完全不取反时的答案
        for (int i = 0; i < n; ++i) {  // 枚举每一个被取反的位置
            ans = max(ans, f(i));  // 取反第 i 个元素后更新答案
        }
        return ans;  // 返回最终最大长度
    }
};
