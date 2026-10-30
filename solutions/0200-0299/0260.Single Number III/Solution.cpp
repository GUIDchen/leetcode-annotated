// 题目：260. 只出现一次的数字 III（Single Number III）
// 思路：位运算分组。先把所有数异或得到 a^b，取其中最低位的 1 作为区分位，把数组分成两组分别异或，即可分别得到 a 与 b。
// 时间复杂度：O(n)，两次线性扫描；空间复杂度：O(1)，只用常数个变量。

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> singleNumber(vector<int>& nums) {  // nums：只有两个数出现一次，其余数都出现两次
        long long xs = 0;  // 用 long long 存异或和，避免对 INT_MIN 取负时溢出
        for (int& x : nums) {  // 第一遍：把所有元素异或起来
            xs ^= x;  // 成对的数互相抵消，最后剩下 a ^ b
        }
        int lb = xs & -xs;  // 取最低位的 1 作为区分位：a 与 b 在这一位上必然不同
        int a = 0;  // 用来累计其中一组内所有数的异或和
        for (int& x : nums) {  // 第二遍：按区分位把数组分成两组
            if (x & lb) {  // 只处理该位为 1 的那一组
                a ^= x;  // 组内成对的数抵消，最后剩下就是 a
            }
        }
        int b = xs ^ a;  // 由 a ^ b 与 a 反推出 b
        return {a, b};  // 返回两个只出现一次的数
    }  // 结束方法
};  // 结束类