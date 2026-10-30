// 题目：136. 只出现一次的数字（Single Number）
// 思路：利用异或的 a ^ a = 0 与 a ^ 0 = a，把所有元素异或起来，成对出现的会抵消，只剩单独的那个。
// 时间复杂度：O(n)，遍历一次；空间复杂度：O(1)，只用常量额外空间。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int singleNumber(vector<int>& nums) {  // 返回唯一出现一次的元素
        int ans = 0;  // 异或累加器，初值 0 不影响结果
        for (int v : nums) {  // 逐个元素累积异或
            ans ^= v;  // 相同元素异或得 0，最终只留下只出现一次的那个
        }
        return ans;  // 返回答案
    }
};