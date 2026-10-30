// 题目：1438. 绝对差不超过限制的最长连续子数组（Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit）
// 思路：滑动窗口配合有序 multiset，窗口内最大值减最小值超过 limit 时收缩左边界，窗口长度即候选答案。
// 时间复杂度：O(n log n)，每次插入删除 O(log n)；空间复杂度：O(n)，窗口最多存 n 个元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int longestSubarray(vector<int>& nums, int limit) {  // nums 是输入数组，limit 是窗口内允许的最大绝对差
        multiset<int> s;  // 有序可重集合，维护窗口全部元素，便于 O(log n) 取到最大值与最小值
        int ans = 0, j = 0;  // ans 记录最长长度，j 是窗口左端点
        for (int i = 0; i < nums.size(); ++i) {  // 右端点 i 从 0 开始逐个右移
            s.insert(nums[i]);  // 新元素进入窗口
            while (*s.rbegin() - *s.begin() > limit) {  // rbegin 是最大值、begin 是最小值，差值超限说明窗口不合法
                s.erase(s.find(nums[j++]));  // erase 只删掉一个等于 nums[j] 的实例（find 定位迭代器），随后左端点右移
            }  // 用当前窗口长度 i-j+1 更新答案
            ans = max(ans, i - j + 1);
        }
        return ans;  // 返回最长合法子数组的长度
    }
};