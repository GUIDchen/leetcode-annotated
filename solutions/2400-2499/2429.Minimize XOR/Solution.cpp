// 题目：2429. 最小异或（Minimize XOR）
// 核心思路：x 的二进制 1 个数必须等于 num2 的 1 个数；先贪心复制 num1 的高位 1，名额没用完再从最低位补 num1 的 0 位。
// 时间复杂度：O(log num1)，最多扫描 31 个二进制位；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimizeXor(int num1, int num2) {  // num1 是基准数，num2 决定答案 x 中 1 的个数
        int cnt = __builtin_popcount(num2);  // cnt 等于 num2 二进制中 1 的个数，也就是 x 必须拥有的 1 的个数
        int x = 0;  // x 用来逐步构造答案
        for (int i = 30; ~i && cnt; --i) {  // 从最高位 30 开始向下扫描；cnt 一旦用尽就提前结束
            if (num1 >> i & 1) {  // num1 这一位是 1，就把它复制到 x 上，使异或结果该位为 0
                x |= 1 << i;  // 把 x 的第 i 位置 1
                --cnt;  // 消耗一个 1 的名额
            }  // if 分支结束
        }  // 高位扫描循环结束
        for (int i = 0; cnt; ++i) {  // 名额还有剩余时，从最低位开始补位
            if (num1 >> i & 1 ^ 1) {  // 只挑 num1 这一位为 0 的位置置 1，避免与 num1 高位重复
                x |= 1 << i;  // 把 x 的第 i 位置 1；低位对异或和的贡献最小
                --cnt;  // 再消耗一个名额
            }  // if 分支结束
        }  // 名额补完，循环结束
        return x;  // 返回构造出的最小值
    }  // minimizeXor 方法结束
};  // Solution 类定义结束