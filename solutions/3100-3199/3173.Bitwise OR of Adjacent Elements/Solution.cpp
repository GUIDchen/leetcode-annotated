// 题目：3173. 相邻元素的按位或（Bitwise OR of Adjacent Elements）
// 思路：结果数组长度为 n-1，第 i 项就是 nums[i] | nums[i+1]，从左到右遍历一次逐项填入即可。
// 时间复杂度：O(n)，只遍历一次；空间复杂度：O(n)，答案数组（不计返回值则 O(1)）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> orArray(vector<int>& nums) {  // nums 是输入数组，返回每个相邻元素对的按位或组成的新数组
        int n = nums.size();  // 数组长度
        vector<int> ans(n - 1);  // 相邻对的数量是 n-1，因此结果数组长度也是 n-1
        for (int i = 0; i < n - 1; ++i) {  // 枚举每一个相邻下标对 (i, i+1)
            ans[i] = nums[i] | nums[i + 1];  // 第 i 项等于 nums[i] 与 nums[i+1] 的按位或
        }
        return ans;  // 返回长度为 n-1 的结果数组
    }
};