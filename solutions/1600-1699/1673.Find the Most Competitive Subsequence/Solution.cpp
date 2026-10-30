// 题目：1673. 找出最具竞争力的子序列（Find the Most Competitive Subsequence）
// 思路：单调递增栈。扫描时若栈顶比当前元素大、且删掉栈顶后仍能凑够 k 个，就弹栈，从而让字典序更小。
// 时间复杂度：O(n)，每个元素最多入栈、出栈各一次；空间复杂度：O(k)，栈最多保存 k 个元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> mostCompetitive(vector<int>& nums, int k) {  // nums：原数组；k：需要保留的子序列长度
        vector<int> stk;  // 单调栈，栈内元素始终递增，最终保存选出的子序列
        int n = nums.size();  // 记录数组长度，判断「还能不能再删」时要用
        for (int i = 0; i < n; ++i) {  // 从左到右扫描每个元素
            while (stk.size() && stk.back() > nums[i] && stk.size() + n - i > k) {  // 栈顶更大就弹掉；stk.size() + n - i > k 保证剩余元素还够凑满 k 个
                stk.pop_back();  // 弹出较大的栈顶，换成更小的当前元素，使字典序更小
            }  // while 结束：栈顶不再比当前元素大，或已经不能再删
            if (stk.size() < k) {  // 栈还没满 k 个时才需要放入当前元素
                stk.push_back(nums[i]);  // 把当前元素压入栈中
            }  // if 结束
        }  // 扫描结束，栈里就是长度为 k 的最小字典序子序列
        return stk;  // 返回结果
    }  // 方法结束
};  // 类定义结束