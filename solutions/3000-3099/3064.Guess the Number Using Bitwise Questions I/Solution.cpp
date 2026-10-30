// 题目：3064. 使用按位查询猜测数字 I（Guess the Number Using Bitwise Questions I）
// 思路：逐位构造答案；每次只让查询掩码保留第 i 位，API 返回非零说明隐藏数字该位为 1。
// 时间复杂度：O(32)=O(1)，最多查询 32 次；空间复杂度：O(1)，仅一个答案变量。
/**
 * Definition of commonSetBits API.
 * int commonSetBits(int num);
 */

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findNumber() {  // 无需入参，返回猜出的隐藏数字
        int n = 0;  // 答案从 0 开始逐位拼装
        for (int i = 0; i < 32; ++i) {  // 依次检查第 0 位到第 31 位，覆盖 32 位整数
            if (commonSetBits(1 << i)) {  // 掩码只有第 i 位为 1，查询结果非零即代表隐藏数字该位是 1
                n |= 1 << i;  // 把答案的第 i 位置 1，其余位保持不变
            }  // 该位判断结束
        }  // 32 位全部试探完毕
        return n;  // 返回拼装完成的数字
    }  // 方法结束
};  // 类定义结束