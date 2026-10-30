// 题目：89. 格雷编码（Gray Code）
// 思路：格雷码第 i 项等于 i ^ (i >> 1)。这个公式保证相邻两项只差一个二进制位，且首项为 0。
// 时间复杂度：O(2^n)，需要生成 2^n 个结果；空间复杂度：O(1)（不计返回数组）。

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> grayCode(int n) {  // n：格雷码的二进制位数
        vector<int> ans;  // 存放长度为 2^n 的格雷码序列
        for (int i = 0; i < 1 << n; ++i) {  // 枚举 0 .. 2^n - 1；1 << n 就是序列长度
            ans.push_back(i ^ (i >> 1));  // 直接套公式：i 异或它右移一位的结果
        }
        return ans;  // 返回生成的格雷码序列
    }
};