// 题目：3190. 使所有元素都可以被 3 整除的最少操作数（Find Minimum Operations to Make All Elements Divisible by Three）
// 思路：已经能被 3 整除的元素不用动；其余元素各做一次 +1 或 -1 即可，所以答案就是「不能被 3 整除的元素个数」。
// 时间复杂度：O(n)，只需遍历数组一次；空间复杂度：O(1)，只用一个计数器。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumOperations(vector<int>& nums) {  // nums：输入的整数数组，返回最少操作次数
        int ans = 0;  // 计数器：记录最少操作次数，初始为 0
        for (int x : nums) {  // 范围 for 循环，依次取出每个元素 x
            ans += x % 3 != 0 ? 1 : 0;  // 余数非 0 说明该元素需要一次操作，累加进答案；否则加 0
        }
        return ans;  // 返回累计得到的最少操作次数
    }
};
