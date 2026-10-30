// 题目：1856. 子数组最小乘积的最大值（Maximum Subarray Min-Product）
// 思路：用单调栈分别求出每个 nums[i] 左边第一个更小值下标 left[i] 与右边第一个更小值下标 right[i]，得到以 nums[i] 为最小值的最大区间；再用前缀和 O(1) 取出区间和，更新 nums[i] × 区间和。
// 时间复杂度：O(n)，每个下标最多入栈、出栈各一次；空间复杂度：O(n)，left/right 数组与前缀和数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxSumMinProduct(vector<int>& nums) {  // nums：正整数数组，求「最小值 × 子数组和」的最大值
        int n = nums.size();  // n：数组长度
        vector<int> left(n, -1);  // left[i]：i 左边第一个严格小于 nums[i] 的下标，越界用 -1
        vector<int> right(n, n);  // right[i]：i 右边第一个小于等于 nums[i] 的下标，越界用 n
        stack<int> stk;  // 单调栈：存下标，栈内对应元素值自底向上递增
        for (int i = 0; i < n; ++i) {  // 第一趟：从左往右确定每个位置的左边界
            while (!stk.empty() && nums[stk.top()] >= nums[i]) {  // 栈顶元素值不小于当前值，说明它不可能成为当前元素的左边界
                stk.pop();  // 弹出，维持栈的单调递增性
            }  // while 结束，栈顶就是左边第一个更小的元素
            if (!stk.empty()) {  // 栈非空才有左边界可记
                left[i] = stk.top();  // 记录左边界下标
            }  // if 结束
            stk.push(i);  // 当前下标入栈，供后面的元素来找它当边界
        }  // 第一趟结束
        stk = stack<int>();  // 清空栈，供第二趟复用
        for (int i = n - 1; ~i; --i) {  // 第二趟：从右往左确定每个位置的右边界
            while (!stk.empty() && nums[stk.top()] > nums[i]) {  // 这里用严格大于，让相等的值只在左侧被统计一次，避免同一区间重复计算
                stk.pop();  // 弹出不满足单调性的栈顶
            }  // while 结束
            if (!stk.empty()) {  // 栈顶就是右边第一个更小的元素
                right[i] = stk.top();  // 记录右边界下标
            }  // if 结束
            stk.push(i);  // 当前下标入栈
        }  // 第二趟结束
        long long s[n + 1];  // 前缀和：s[i] 表示 nums 前 i 个元素之和
        s[0] = 0;  // 前缀和起点为 0
        for (int i = 0; i < n; ++i) {  // 递推计算前缀和
            s[i + 1] = s[i] + nums[i];  // 累加当前元素
        }  // for 结束
        long long ans = 0;  // 答案用 long long，避免「最小值 × 区间和」溢出 int
        for (int i = 0; i < n; ++i) {  // 枚举每个位置，把它当作区间的最小值
            ans = max(ans, nums[i] * (s[right[i]] - s[left[i] + 1]));  // 区间 (left[i], right[i]) 的元素和乘以 nums[i]，即该区间的最小乘积，更新最大值
        }  // for 结束
        const int mod = 1e9 + 7;  // 取模常数 1e9 + 7
        return ans % mod;  // 按题意对 1e9 + 7 取模后返回
    }  // 方法结束
};  // 类定义结束