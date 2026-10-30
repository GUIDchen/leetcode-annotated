// 题目：3192. 使二进制数组全部等于 1 的最少操作次数 II（Minimum Operations to Make Binary Array Elements Equal to One II）
// 思路：每次操作翻转的是从下标 i 到末尾的整个后缀，于是只需维护后缀翻转的累积标记 v，逐个元素判断当前真实值是否为 0。
// 时间复杂度：O(n)，一次遍历数组；空间复杂度：O(1)，只用 ans 与后缀翻转标记 v 两个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minOperations(vector<int>& nums) {  // nums：0/1 数组，返回最少操作次数
        int ans = 0, v = 0;  // ans 记录操作次数；v 是当前已累积的后缀翻转标记（0 表示没翻，1 表示翻过）
        for (int x : nums) {  // 顺序遍历每个元素
            x ^= v;  // 把之前执行过的后缀翻转作用到当前元素上，得到它的真实值
            if (x == 0) {  // 真实值为 0，必须以当前位置为起点再翻转一次后缀
                v ^= 1;  // 后缀翻转标记取反，表示从这里开始所有元素状态都被翻转过
                ++ans;  // 操作次数加一，此位置随之变成 1
            }
        }
        return ans;  // 返回使整个数组变成 1 的最少操作次数
    }
};