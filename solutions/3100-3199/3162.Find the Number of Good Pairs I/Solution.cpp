// 题目：3162. 优质数对的总数 I（Find the Number of Good Pairs I）
// 思路：暴力枚举所有数对 (x, y)，判断 x 是否为 y * k 的倍数，是则计数加一。
// 时间复杂度：O(n * m)，n、m 分别是两个数组的长度；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numberOfPairs(vector<int>& nums1, vector<int>& nums2, int k) {  // nums1、nums2 是输入数组，k 是题目给定的倍数
        int ans = 0;  // 答案累加器：记录优质数对的个数
        for (int x : nums1) {  // 枚举 nums1 中的每个元素 x
            for (int y : nums2) {  // 枚举 nums2 中的每个元素 y
                if (x % (y * k) == 0) {  // 优质数对的定义：x 能被 y * k 整除；数据范围下 y * k 不会溢出 int
                    ++ans;  // 满足条件，计数加一
                }  // if 语句结束
            }  // 内层循环结束
        }  // 外层循环结束
        return ans;  // 返回优质数对总数
    }  // 方法结束
};  // 类定义结束