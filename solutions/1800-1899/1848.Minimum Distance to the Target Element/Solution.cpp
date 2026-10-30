// 题目：1848. 到目标元素的最小距离（Minimum Distance to the Target Element）
// 思路：一次遍历，凡遇到等于 target 的元素，就用 |i - start| 更新最小距离；ans 初值取 n 作为上界。
// 时间复杂度：O(n)，只扫描一遍数组；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int getMinDistance(vector<int>& nums, int target, int start) {  // nums：输入数组；target：目标值；start：起始下标
        int n = nums.size();  // 数组长度，同时也是距离的上界（下标差最大为 n-1）
        int ans = n;  // 先把答案置为一定不会更小的值，方便后面取 min
        for (int i = 0; i < n; ++i) {  // 从左到右扫描每个元素
            if (nums[i] == target) {  // 只有值等于 target 的元素才会成为候选答案
                ans = min(ans, abs(i - start));  // 用当前下标与 start 的距离去更新最小值
            }  // 结束 if
        }  // 结束 for
        return ans;  // 返回最小距离
    }  // 结束 getMinDistance
};  // 结束 Solution 类