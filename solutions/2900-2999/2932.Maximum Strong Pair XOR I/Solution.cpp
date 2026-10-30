// 题目：2932. 找出强数对的最大异或值 I（Maximum Strong Pair XOR I）
// 思路：n 很小，直接双重循环枚举所有有序数对 (x, y)，用 |x - y| <= min(x, y) 判定强数对，取异或最大值。
// 时间复杂度：O(n^2)，两层循环枚举所有数对；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumStrongPairXor(vector<int>& nums) {  // nums：输入数组
        int ans = 0;  // 记录目前遇到的最大异或值，初值为 0（异或结果非负）
        for (int x : nums) {  // 枚举数对中的第一个数 x
            for (int y : nums) {  // 枚举数对中的第二个数 y，允许 x == y，即数对可以取同一个元素
                if (abs(x - y) <= min(x, y)) {  // 强数对判定条件：两数之差不超过两者中的较小值
                    ans = max(ans, x ^ y);  // 是强数对，就用它的异或值尝试更新答案
                }
            }
        }
        return ans;  // 返回最大异或值
    }
};  // 类定义结束