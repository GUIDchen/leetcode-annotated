// 题目：1950. 所有子数组最小值中的最大值（Maximum of Minimum Values in All Subarrays）
// 思路：单调栈求每个元素左右第一个严格更小值的下标，得到以它为最小值的最大窗口长度，再按长度取最大值并做后缀最大值。
// 时间复杂度：O(n)，两次单调栈加一次线性扫描；空间复杂度：O(n)，左右边界数组与栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> findMaximums(vector<int>& nums) {  // nums：输入数组
        int n = nums.size();  // 记录数组长度
        vector<int> left(n, -1);  // left[i]：i 左边第一个严格更小元素的下标，默认 -1
        vector<int> right(n, n);  // right[i]：i 右边第一个严格更小元素的下标，默认 n
        stack<int> stk;  // 单调递增栈，存下标，对应元素值严格递增
        for (int i = 0; i < n; ++i) {  // 从左往右求 left
            while (!stk.empty() && nums[stk.top()] >= nums[i]) {  // 栈顶值不小于当前值，不能当作左边界
                stk.pop();  // 弹出，保持栈内元素严格递增
            }
            if (!stk.empty()) {  // 栈顶就是左边第一个更小值
                left[i] = stk.top();  // 记下左边界下标
            }
            stk.push(i);  // 当前下标入栈，作为后面元素的候选左边界
        }
        stk = stack<int>();  // 清空栈，复用于从右往左的扫描
        for (int i = n - 1; i >= 0; --i) {  // 从右往左求 right
            while (!stk.empty() && nums[stk.top()] >= nums[i]) {  // 同样维护严格递增栈
                stk.pop();  // 弹出不满足严格更小的元素
            }
            if (!stk.empty()) {  // 栈顶就是右边第一个更小值
                right[i] = stk.top();  // 记下右边界下标
            }
            stk.push(i);  // 当前下标入栈
        }
        vector<int> ans(n);  // ans[k-1] 表示长度为 k 的子数组其最小值的最大可能值
        for (int i = 0; i < n; ++i) {  // 逐个元素作为区间最小值来考察
            int m = right[i] - left[i] - 1;  // 以 nums[i] 为最小值时能覆盖的最大窗口长度
            ans[m - 1] = max(ans[m - 1], nums[i]);  // 该长度下取更大的最小值
        }
        for (int i = n - 2; i >= 0; --i) {  // 从后往前做后缀最大值
            ans[i] = max(ans[i], ans[i + 1]);  // 更短的子数组总能从更长窗口里取到，故答案单调不降
        }
        return ans;  // 返回每个长度对应的最大最小值
    }
};  // LeetCode 题解类结束