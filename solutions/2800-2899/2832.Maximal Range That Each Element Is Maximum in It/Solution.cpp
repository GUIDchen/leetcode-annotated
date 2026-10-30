// 题目：2832. 每个元素为最大值的最大范围（Maximal Range That Each Element Is Maximum in It）
// 思路：单调栈。对每个下标分别求「左边最近的严格大于它的位置」left[i] 与「右边最近的严格大于它的位置」right[i]，两者之间的区间内所有值都不超过 nums[i]，长度即 right[i]-left[i]-1；因为相等元素可以同处一个区间，弹栈时用 <= 把相等值也弹掉。
// 时间复杂度：O(n)，每个下标最多入栈、出栈各一次；空间复杂度：O(n)，两个边界数组与单调栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> maximumLengthOfRanges(vector<int>& nums) {  // nums：输入数组，返回每个位置对应的最大区间长度
        int n = nums.size();  // 数组长度，后面反复使用
        vector<int> left(n, -1);  // left[i]：i 左边最近的数值严格大于 nums[i] 的下标，不存在时保持 -1
        vector<int> right(n, n);  // right[i]：i 右边最近的数值严格大于 nums[i] 的下标，不存在时保持 n
        stack<int> stk;  // 单调栈，从栈底到栈顶保存的下标对应的值单调递减
        for (int i = 0; i < n; ++i) {  // 从左到右扫描，求每个位置的左边界
            while (!stk.empty() && nums[stk.top()] <= nums[i]) {  // 栈顶值不比 nums[i] 大，就不可能成为 i 的严格上界
                stk.pop();  // 弹出这些下标（它们对后续元素也不再有用）
            }
            if (!stk.empty()) {  // 弹完后栈顶就是左边最近的严格更大元素
                left[i] = stk.top();  // 记录左边界下标
            }
            stk.push(i);  // 把当前下标入栈，保持栈内数值递减
        }
        stk = stack<int>();  // 清空栈，准备从右往左再扫一遍
        for (int i = n - 1; ~i; --i) {  // 从右到左扫描，求每个位置的右边界；~i 等价于 i >= 0
            while (!stk.empty() && nums[stk.top()] <= nums[i]) {  // 同理，弹出所有不大于 nums[i] 的栈顶
                stk.pop();  // 它们不构成严格更大的右边界
            }
            if (!stk.empty()) {  // 剩下的栈顶就是右边最近的严格更大元素
                right[i] = stk.top();  // 记录右边界下标
            }
            stk.push(i);  // 当前下标入栈，继续维持单调性
        }
        vector<int> ans(n);  // 存放每个位置的答案
        for (int i = 0; i < n; ++i) {  // 逐个位置计算区间长度
            ans[i] = right[i] - left[i] - 1;  // 开区间 (left[i], right[i]) 内的元素个数就是最大区间长度
        }
        return ans;  // 返回结果数组
    }
};