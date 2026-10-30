// 题目：1793. 好子数组的最大分数（Maximum Score of a Good Subarray）
// 思路：两遍单调栈分别求出每个下标左侧第一个严格更小、右侧第一个小于等于它的位置，得到以 nums[i] 为最小值的最大区间；只保留覆盖下标 k 的区间，用「最小值 × 区间长度」更新答案。
// 时间复杂度：O(n)，每个下标最多进栈、出栈各一次；空间复杂度：O(n)，left/right 数组与单调栈。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解法接口
    int maximumScore(vector<int>& nums, int k) {  // nums：分数数组；k：好子数组必须包含的下标
        int n = nums.size();  // 数组长度，后面多次使用
        vector<int> left(n, -1);  // left[i]：i 左边第一个严格小于 nums[i] 的下标，没有则为 -1
        vector<int> right(n, n);  // right[i]：i 右边第一个小于等于 nums[i] 的下标，没有则为 n
        stack<int> stk;  // 单调栈：存下标，栈内下标对应的值从栈底到栈顶递增
        for (int i = 0; i < n; ++i) {  // 从左往右扫一遍，求每个位置的 left
            int v = nums[i];  // 当前元素值，先取出来避免反复访问数组
            while (!stk.empty() && nums[stk.top()] >= v) {  // 栈顶值不小于 v 时它不可能是 v 左侧第一个更小值
                stk.pop();  // 把这些偏高的下标弹出
            }  // while 结束
            if (!stk.empty()) {  // 弹完后栈顶就是左侧第一个更小值
                left[i] = stk.top();  // 记录左边界
            }  // if 结束
            stk.push(i);  // 当前下标入栈，供后面更大的元素查询
        }  // 第一遍扫描结束
        stk = stack<int>();  // 清空栈，准备从右往左再扫一遍
        for (int i = n - 1; i >= 0; --i) {  // 倒序遍历求每个位置的 right
            int v = nums[i];  // 当前元素值
            while (!stk.empty() && nums[stk.top()] > v) {  // 这里用「大于」，与左侧的「大于等于」配合，保证等值元素只归属一侧而不重复计算
                stk.pop();  // 弹出比 v 更大的下标
            }  // while 结束
            if (!stk.empty()) {  // 栈顶即右侧第一个小于等于 v 的下标
                right[i] = stk.top();  // 记录右边界
            }  // if 结束
            stk.push(i);  // 下标入栈，继续向左扩展
        }  // 第二遍扫描结束
        int ans = 0;  // 答案；分数非负，初值取 0 即可
        for (int i = 0; i < n; ++i) {  // 枚举区间最小值所在位置
            if (left[i] + 1 <= k && k <= right[i] - 1) {  // 开区间 (left[i], right[i]) 必须覆盖 k，才满足「好子数组」要求
                ans = max(ans, nums[i] * (right[i] - left[i] - 1));  // 以 nums[i] 为最小值的最大区间长度 × 最小值，取最大值
            }  // if 结束
        }  // 枚举结束
        return ans;  // 返回最大分数
    }  // 方法结束
};  // 类定义结束