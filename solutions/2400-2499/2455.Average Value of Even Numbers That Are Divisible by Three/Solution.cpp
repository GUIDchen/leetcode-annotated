// 题目：2455. 可被三整除的偶数的平均值（Average Value of Even Numbers That Are Divisible by Three）
// 思路：被 2 和 3 同时整除等价于被 6 整除，一次遍历累加并计数，最后用整数除法求平均。
// 时间复杂度：O(n)，遍历数组一遍；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int averageValue(vector<int>& nums) {  // nums：输入数组，返回满足条件的数的平均值
        int s = 0, n = 0;  // s 保存满足条件的数之和，n 保存满足条件的数的个数
        for (int x : nums) {  // 范围 for 依次取出数组中的每个元素
            if (x % 6 == 0) {  // 能被 6 整除即“能被三整除的偶数”
                s += x;  // 累加到总和
                ++n;  // 个数加一
            }
        }
        return n == 0 ? 0 : s / n;  // 没有满足条件的数返回 0，否则返回整数除法（向下取整）的平均值
    }
};