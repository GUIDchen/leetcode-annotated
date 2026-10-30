// 3471. Find the Largest Almost Missing Integer / 3471. 找出最大的几近缺失整数
// 核心思路：按 k 分三种情况——k = 1 取只出现一次的最大值，k = n 取整个数组最大值，其余只判断首尾元素是否唯一。
// 复杂度：时间 O(n)，空间 O(n)。

class Solution {  // LeetCode 题解统一使用 Solution 类
public:  // 公有接口
    int largestInteger(vector<int>& nums, int k) {  // 返回在所有长度 k 子数组中都恰好出现一次的最大整数
        if (k == 1) {  // k 等于 1 时长度为 1 的子数组就是元素本身
            unordered_map<int, int> cnt;  // 用哈希表统计每个值的出现次数
            for (int x : nums) {  // 遍历数组
                ++cnt[x];  // 累加当前值的频次
            }  // 统计结束
            int ans = -1;  // 没有满足条件的值时为 -1
            for (auto& [x, v] : cnt) {  // 遍历每个值与对应频次
                if (v == 1) {  // 只出现一次才是候选
                    ans = max(ans, x);  // 取候选中的最大值
                }  // 候选判断结束
            }  // 频次遍历结束
            return ans;  // 返回 k = 1 时的答案
        }  // k = 1 分支结束
        int n = nums.size();  // 数组长度
        if (k == n) {  // k 等于 n 时只有一个长度为 n 的子数组
            return ranges::max(nums);  // 任何不同值在该子数组中都只出现一次，直接返回最大值
        }  // k = n 分支结束
        auto f = [&](int k) -> int {  // lambda：判断下标 k 处的值是否在别处重复出现
            for (int i = 0; i < n; ++i) {  // 遍历整个数组
                if (i != k && nums[i] == nums[k]) {  // 别处出现了相同值
                    return -1;  // 不是唯一，返回 -1
                }  // 重复判断结束
            }  // 遍历结束
            return nums[k];  // 唯一则返回该值本身
        };  // lambda 定义结束
        return max(f(0), f(n - 1));  // 1 < k < n 时只有首尾两个元素必然落入每个子数组
    }  // 方法结束
};  // 类定义结束
