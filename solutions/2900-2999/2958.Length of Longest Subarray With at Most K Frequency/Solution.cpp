// 题目：2958. 最多 K 个重复元素的最长子数组（Length of Longest Subarray With at Most K Frequency）
// 思路：滑动窗口 + 频率哈希表，右端扩张后若某元素出现次数超过 k，就不断右移左端收缩窗口，让窗口始终合法。
// 时间复杂度：O(n)，左右指针各自最多移动 n 次；空间复杂度：O(n)，哈希表最多保存不同元素的个数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxSubarrayLength(vector<int>& nums, int k) {  // nums 为输入数组，k 为每个元素允许出现的最大次数
        int ans = 0;  // 记录最长合法子数组的长度
        unordered_map<int, int> cnt;  // 统计窗口内每个元素的出现次数
        for (int l = 0, r = 0; r < nums.size(); ++r) {  // l、r 为窗口左右端点，r 逐个右移扩张窗口
            ++cnt[nums[r]];  // 新元素进入窗口，计数加一
            while (cnt[nums[r]] > k) {  // 只有 nums[r] 可能超限，一旦超限就收缩窗口
                --cnt[nums[l++]];  // 左端元素移出窗口，计数减一，l 右移
            }  // 收缩循环结束
            ans = max(ans, r - l + 1);  // 用当前合法窗口的长度更新答案
        }  // 扩张循环结束
        return ans;  // 返回最长长度
    }  // 方法体结束
};  // 题解类结束