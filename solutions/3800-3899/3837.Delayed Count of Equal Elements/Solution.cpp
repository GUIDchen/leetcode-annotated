// 3837. 相等元素的延迟计数 / Delayed Count of Equal Elements（中等）
// 核心思路：倒序遍历并维护一个滑动计数窗口；处理下标 i 时把 nums[i+k+1] 加入计数器，此时窗口中恰好是下标大于 i+k 的所有元素，答案就是其中与 nums[i] 相等的个数。
// 复杂度：时间 O(n)，空间 O(n)。
class Solution {  // LeetCode 要求的类名
public:  // 对外接口区
    vector<int> delayedCount(vector<int>& nums, int k) {  // 返回每个下标 i 对应的延迟计数值
        int n = nums.size();  // 数组长度
        unordered_map<int, int> cnt;  // 计数器：记录下标大于 i+k 的元素出现次数
        vector<int> ans(n);  // 答案数组，初始全为 0
        for (int i = n - k - 2; i >= 0; --i) {  // 从右往左枚举；起点保证 i+k+1 不越界
            ++cnt[nums[i + k + 1]];  // 把下标 i+k+1 的元素纳入窗口（窗口右端逐步扩张）
            ans[i] = cnt[nums[i]];  // 窗口内与 nums[i] 相等的元素个数即为答案
        }  // 循环结束
        return ans;  // 返回全部下标的结果
    }  // 方法结束
};  // 类定义结束
