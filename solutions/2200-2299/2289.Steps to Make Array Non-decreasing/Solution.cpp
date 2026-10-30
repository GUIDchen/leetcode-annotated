// 题目：2289. 使数组按非递减顺序排列（Steps to Make Array Non-decreasing）
// 核心思路：从右往左扫并用单调栈存下标，dp[i] 表示削平 nums[i] 右侧严格更小元素所需的轮数；每弹出一个更小的栈顶就更新 max(dp[i]+1, dp[top])，最终答案是所有 dp 的最大值。
// 时间复杂度：O(n)，每个下标最多入栈、出栈各一次；空间复杂度：O(n)，栈和 dp 数组各占 O(n)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int totalSteps(vector<int>& nums) {  // nums：输入数组；返回使整个数组非递减所需的最少轮数
        stack<int> stk;  // 单调栈：从右往左保存候选下标，栈内对应数值保持单调递减
        int ans = 0, n = nums.size();  // ans 记录全局最大轮数；n 是数组长度
        vector<int> dp(n);  // dp[i]：把 nums[i] 及其右侧削成非递减所需的轮数，先全部初始化为 0
        for (int i = n - 1; i >= 0; --i) {  // 从右往左遍历，保证处理 nums[i] 时它右侧的 dp 值已经算好
            while (!stk.empty() && nums[i] > nums[stk.top()]) {  // 栈顶元素严格小于 nums[i]，说明它终将在某一轮被 nums[i] 删掉
                dp[i] = max(dp[i] + 1, dp[stk.top()]);  // 每吸收一个右侧元素自身就要多等 1 轮，但也不能早于该元素被削平的 dp[top] 轮，故取两者较大值
                ans = max(ans, dp[i]);  // 任意元素的轮数都可能成为最大值，所以每次更新答案
                stk.pop();  // 该下标已结算完毕，弹出以免后续重复计算
            }
            stk.push(i);  // 当前下标入栈，等待更左侧、更大的元素来结算它
        }
        return ans;  // 所有元素轮数的最大值，就是整个数组变非递减所需的轮数
    }
};  // 结束 Solution 类定义