# 题目：2429. 最小异或（Minimize XOR）
# 核心思路：x 的二进制 1 个数必须等于 num2 的 1 个数；先贪心复制 num1 的高位 1，名额没用完再从最低位补 num1 的 0 位。
# 时间复杂度：O(log num1)，最多扫描 31 个二进制位；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minimizeXor(self, num1: int, num2: int) -> int:  # num1 是基准数，num2 决定答案中 1 的个数
        cnt = num2.bit_count()  # 统计 num2 二进制中 1 的个数，这也就是答案必须有的 1 的个数
        x = 0  # x 用来逐步构造答案
        for i in range(30, -1, -1):  # 从最高位 30 开始向下扫描
            if num1 >> i & 1 and cnt:  # num1 当前位是 1 且还有名额，就把它复制到 x
                x |= 1 << i  # 该位对齐为 1，使异或结果这一位为 0
                cnt -= 1  # 消耗一个名额
        for i in range(30):  # 名额有剩余时，从最低位开始补位
            if num1 >> i & 1 ^ 1 and cnt:  # num1 这一位是 0 且还有名额，才把它置 1
                x |= 1 << i  # 低位对异或和的贡献最小，所以优先补低位
                cnt -= 1  # 再消耗一个名额
        return x  # 返回构造出的最小值
