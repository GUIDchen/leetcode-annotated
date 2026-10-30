// 题目：3289. 数字小镇中的捣蛋鬼（The Two Sneaky Numbers of Digitville）
// 思路：数组长度是 n+2、元素都在 [0,n) 且恰有两个数各出现两次，用计数数组统计频次，频次为 2 的就是答案。
// 时间复杂度：O(n)，只遍历一遍数组；空间复杂度：O(n)，计数数组大小固定为 100。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> getSneakyNumbers(vector<int>& nums) {  // nums：长度 n+2、恰有两个数重复出现的数组
        vector<int> ans;  // 收集两个重复出现的数
        int cnt[100]{};  // 计数数组；{} 保证全部元素初始化为 0
        for (int x : nums) {  // 遍历每个元素
            if (++cnt[x] == 2) {  // 先自增再判断：计数变成 2 说明这是第二次遇到该数
                ans.push_back(x);  // 把这个重复的数收进答案
            }  // if 结束
        }  // for 结束
        return ans;  // 返回两个重复的数（顺序不影响判题）
    }  // getSneakyNumbers 结束
};  // Solution 类结束
