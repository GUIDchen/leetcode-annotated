# 题目：1256. 加密数字（Encode Number）
# 思路：编码序列就是 1、2、3、… 的二进制去掉最高位：先算 num+1 的二进制串（形如 0b1xxx），再切掉 '0b1' 这三个字符。
# 时间复杂度：O(log num)，只做一次整数转二进制；空间复杂度：O(log num)，用于存放结果字符串。
class Solution:  # LeetCode 约定的题解类
    def encode(self, num: int) -> str:  # num：加密序列中的下标（从 0 开始）；返回它对应的二进制字符串
        return bin(num + 1)[3:]  # bin(num + 1) 形如 '0b1xxx'，[3:] 去掉 '0b1' 恰好连同最高位一起丢弃
