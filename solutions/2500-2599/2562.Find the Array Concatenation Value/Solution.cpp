// 题目：2562. 找出数组的串联值（Find the Array Concatenation Value）
// 核心思路：双指针从两端向中间，把 nums[j] 转成字符串接到 nums[i] 的字符串后面，再用 stoi 转回整数累加；正中间元素单独加上。
// 时间复杂度：O(n log M)，每个元素只被拼接一次；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long findTheArrayConcVal(vector<int>& nums) {  // nums：输入数组
        long long ans = 0;  // 串联值总和，可能超出 int，用 long long
        int i = 0, j = nums.size() - 1;  // i 为左指针，j 为右指针
        for (; i < j; ++i, --j) {  // 左右两指针同时向中间收缩
            ans += stoi(to_string(nums[i]) + to_string(nums[j]));  // 两个数字先转字符串再首尾相接，stoi 把结果转回整数
        }
        if (i == j) {  // 数组长度为奇数时，正中间还剩一个元素
            ans += nums[i];  // 中间元素直接累加
        }
        return ans;  // 返回最终串联值
    }
};