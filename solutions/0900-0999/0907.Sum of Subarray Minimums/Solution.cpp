// 题目：907. 子数组的最小值之和（Sum of Subarray Minimums）
// 核心思路：单调栈求出每个元素作为最小值时能向左、向右延伸的边界，再用乘法原理统计它贡献了多少个子数组。
// 时间复杂度：O(n)，每个下标最多入栈、出栈各一次；空间复杂度：O(n)，left/right 数组与栈。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解题方法
    int sumSubarrayMins(vector<int>& arr) {  // arr：输入数组；返回所有子数组最小值之和（对 1e9+7 取模）
        int n = arr.size();  // 数组长度
        vector<int> left(n, -1);  // left[i]：i 左边第一个严格小于 arr[i] 的下标，没有则为 -1
        vector<int> right(n, n);  // right[i]：i 右边第一个小于等于 arr[i] 的下标，没有则为 n
        stack<int> stk;  // 单调递增栈，存下标，栈内对应的值从底到顶递增
        for (int i = 0; i < n; ++i) {  // 从左到右扫描，求每个位置的左边界
            while (!stk.empty() && arr[stk.top()] >= arr[i]) {  // 栈顶值不小于当前值，说明它不再是左边界的候选
                stk.pop();  // 弹出，保证栈内值严格递增（相等时保留右边那个，避免重复计数）
            }  // 结束弹栈
            if (!stk.empty()) {  // 栈顶就是左边第一个比当前值小的元素
                left[i] = stk.top();  // 记录左边界下标
            }  // 结束左边界赋值
            stk.push(i);  // 当前下标入栈，继续作为后续元素的候选
        }  // 结束从左扫描
        stk = stack<int>();  // 清空栈，复用给从右向左的扫描
        for (int i = n - 1; i >= 0; --i) {  // 从右到左扫描，求每个位置的右边界
            while (!stk.empty() && arr[stk.top()] > arr[i]) {  // 栈顶值大于当前值，不再可能成为右边界
                stk.pop();  // 弹出，保持栈内值递增
            }  // 结束弹栈
            if (!stk.empty()) {  // 栈顶就是右边第一个小于等于当前值的元素
                right[i] = stk.top();  // 记录右边界下标
            }  // 结束右边界赋值
            stk.push(i);  // 当前下标入栈
        }  // 结束从右扫描
        long long ans = 0;  // 累加结果，用 64 位避免乘法溢出
        const int mod = 1e9 + 7;  // 题目要求的取模常量
        for (int i = 0; i < n; ++i) {  // 统计每个元素对答案的贡献
            ans += 1LL * (i - left[i]) * (right[i] - i) * arr[i] % mod;  // 以 arr[i] 为最小值的子数组有 (i-left[i])×(right[i]-i) 个
            ans %= mod;  // 每步取模，防止累加溢出
        }  // 结束贡献统计
        return ans;  // 返回最小值之和
    }  // 结束 sumSubarrayMins
};  // 结束 Solution 类