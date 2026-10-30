// 题目：3105. 最长的严格递增或递减子数组（Longest Strictly Increasing or Strictly Decreasing Subarray）
// 思路：分别扫两遍，一遍统计以当前位置结尾的严格递增连续段长度 t，一遍统计严格递减的连续段长度，过程中用 ans 记录最大值。
// 时间复杂度：O(n)，两遍线性扫描；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int longestMonotonicSubarray(vector<int>& nums) {  // nums：输入数组；返回最长严格递增或严格递减子数组长度
        int ans = 1;  // 答案至少为 1，单个元素既可算递增也可算递减
        for (int i = 1, t = 1; i < nums.size(); ++i) {  // 第一遍：统计严格递增的连续段长度 t
            if (nums[i - 1] < nums[i]) {  // 相邻元素严格递增
                ans = max(ans, ++t);  // 段长先加一，再用它更新答案
            } else {  // 递增关系中断
                t = 1;  // 段长重置为 1，从当前元素重新开始计数
            }
        }
        for (int i = 1, t = 1; i < nums.size(); ++i) {  // 第二遍：统计严格递减的连续段长度 t
            if (nums[i - 1] > nums[i]) {  // 相邻元素严格递减
                ans = max(ans, ++t);  // 段长先加一，再用它更新答案
            } else {  // 递减关系中断
                t = 1;  // 段长重置为 1
            }
        }
        return ans;  // 返回两种方向中较大的那个长度
    }
};