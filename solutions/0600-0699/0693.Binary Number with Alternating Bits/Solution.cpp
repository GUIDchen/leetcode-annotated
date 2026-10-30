// 题目：693. 交替位二进制数（Binary Number with Alternating Bits）
// 思路：从最低位开始逐位取出二进制位，与上一位比较，一旦相同就说明不交替；反复右移直到 n 为 0。
// 时间复杂度：O(log n)，即二进制位数；空间复杂度：O(1)，只用两个变量。
class Solution {
public:
    bool hasAlternatingBits(int n) {  // n 是待判断的正整数，判断其二进制相邻位是否总是交替
        int prev = -1;  // prev 记录上一位的值，取 -1 作为哨兵，保证最低位首次比较一定不相等
        while (n) {  // n 还没被取完就继续处理
            int curr = n & 1;  // 取出当前最低位（n & 1）
            if (prev == curr) return false;  // 与上一位相同则说明出现连续相同位，立即返回 false
            prev = curr;  // 更新 prev，为下一位比较做准备
            n >>= 1;  // 右移一位，处理更高位
        }
        return true;  // 所有位都交替，返回 true
    }
};