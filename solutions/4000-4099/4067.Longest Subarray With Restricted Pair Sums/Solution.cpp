// 4067. 数对和受限的最长子数组  Longest Subarray With Restricted Pair Sums
// 核心思路：维护窗口内所有数对的和与差的计数，新元素若与窗口内某元素的和或差相同就左移窗口直到不冲突。
// 复杂度：时间 O(n^2)，空间 O(mx)，其中 mx 为数组最大值。

class Solution {
public:
    int maxSubarray(vector<int>& nums) {  // 返回满足“任意两数之和互不相同且之差互不相同”的最长子数组长度
        int mx = ranges::max(nums);  // 数组最大值，用于确定计数数组规模

        vector<int> cntS((mx << 1) | 1);  // 统计窗口内每种两数之和出现的次数，长度取奇数容纳 0..2*mx
        vector<int> cntD(mx + 1);  // 统计窗口内每种两数之差出现的次数

        int ans = 0;  // 记录最长子数组长度
        int l = 0;  // 窗口左边界

        for (int r = 0; r < nums.size(); r++) {  // 枚举窗口右端点 r
            int x = nums[r];  // 新加入窗口的元素

            while (cntS[x] > 0 || cntD[x] > 0) {  // 新元素与窗口内某元素之和或差等于 x，产生冲突
                int y = nums[l++];  // 取出窗口最左元素并右移左边界

                for (int i = l; i < r; i++) {  // 枚举移出 y 之后窗口中剩余的元素
                    int z = nums[i];  // 剩余窗口中的元素
                    cntS[y + z]--;  // 撤销 y 与 z 之和的计数
                    cntD[abs(y - z)]--;  // 撤销 y 与 z 之差的计数
                }
            }

            for (int i = l; i < r; i++) {  // 把 x 与窗口内每个已有元素配对
                int y = nums[i];  // 窗口中的元素
                cntS[x + y]++;  // 累加两数之和的计数
                cntD[abs(x - y)]++;  // 累加两数之差的计数
            }

            ans = max(ans, r - l + 1);  // 用当前窗口长度更新答案
        }

        return ans;  // 返回最长子数组长度
    }
};