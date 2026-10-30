// 题目：1018. 可被 5 整除的二进制前缀（Binary Prefix Divisible By 5）
// 思路：从左到右滚动维护前缀值对 5 的余数：x = (x << 1 | v) % 5，余数为 0 就说明该前缀能被 5 整除。
// 时间复杂度：O(n)，一趟遍历；空间复杂度：O(n)，用于存放每个前缀的判断结果。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<bool> prefixesDivBy5(vector<int>& nums) {  // nums：由 0 和 1 组成的数组
        vector<bool> ans;  // 逐个前缀的判断结果
        int x = 0;  // 当前前缀值对 5 取模后的余数
        for (int v : nums) {  // 依次把每个比特接到前缀的末尾
            x = (x << 1 | v) % 5;  // 左移一位并加上新比特（等价于原值乘 2 加 v），同时取模防止溢出
            ans.push_back(x == 0);  // 余数为 0 说明这个前缀能被 5 整除，记录 true，否则记录 false
        }
        return ans;  // 返回所有前缀的判断结果
    }
};