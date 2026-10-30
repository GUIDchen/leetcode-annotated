// 题目：3353. 最小总操作数（Minimum Total Operations）
// 思路：一次操作可以给一段区间同时加同一个数，把相邻且相等的元素并成一组最省，答案就是相邻不相等的对数。
// 时间复杂度：O(n)，遍历一遍数组；空间复杂度：O(1)，只用了一个计数器。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minOperations(vector<int>& nums) {  // nums：输入数组
        int ans = 0;  // ans：最少操作数，等价于相邻不相等的对数
        for (int i = 1; i < nums.size(); ++i) {  // 从下标 1 开始，逐个与左邻元素比较
            ans += nums[i] != nums[i - 1];  // 不相等比较的结果是 bool，隐式转成 0/1 后累加
        }  // 结束循环
        return ans;  // 返回最少操作数
    }  // 结束题解方法
};  // 结束题解类
