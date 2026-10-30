// 题目：1611. 使整数变为 0 的最少操作次数（Minimum One Bit Operations to Make Integers Zero）
// 思路：该操作本质是格雷码的相邻转换，最少次数等于 n 与其所有右移版本按位异或的累积，即 ans = n ^ (n>>1) ^ (n>>2) ^ …。
// 时间复杂度：O(log n)，每一位处理一次；空间复杂度：O(1)，只用常数个变量。
class Solution {  // 题解类
public:  // 对外接口
    int minimumOneBitOperations(int n) {  // 输入 n，返回把它变成 0 所需的最少操作次数
        int ans = 0;  // 答案累加器
        for (; n > 0; n >>= 1) {  // 从低位向高位逐步处理，每轮把 n 右移一位
            ans ^= n;  // 把当前 n 异或进答案：答案等于 n、n>>1、n>>2… 的异或和（格雷码逆变换）
        }  // for 循环结束
        return ans;  // 返回最少操作次数
    }
};