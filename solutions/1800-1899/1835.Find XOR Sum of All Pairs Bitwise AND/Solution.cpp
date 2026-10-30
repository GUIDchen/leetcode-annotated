// 题目：1835. 所有数对按位与结果的异或和（Find XOR Sum of All Pairs Bitwise AND）
// 思路：按位与对异或满足分配律，(a1&b1)^(a1&b2)^...=(a1^a2^...)&(b1^b2^...)，故答案等于两数组各自异或和再做按位与。
// 时间复杂度：O(n + m)，两数组各扫描一遍；空间复杂度：O(1)，只使用两个整型变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int getXORSum(vector<int>& arr1, vector<int>& arr2) {  // arr1、arr2 为两个输入数组，返回所有跨数组数对按位与结果的异或和
        int a = accumulate(arr1.begin(), arr1.end(), 0, bit_xor<int>());  // accumulate 以 0 为初值、用 bit_xor 作运算，求出 arr1 全部元素的异或和
        int b = accumulate(arr2.begin(), arr2.end(), 0, bit_xor<int>());  // 同理求出 arr2 全部元素的异或和
        return a & b;  // 两部分的异或和相与，即所求的异或和
    }  // 方法结束
};  // 类定义结束