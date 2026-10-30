# 题目：2939. 最大异或乘积（Maximum Xor Product）
# 思路：n 位以上的高位无法改变；低 n 位逐位看，两边相同就同时置 1，不同就把这一位补给当前较小的数，使两数尽量接近。
# 时间复杂度：O(n)，逐位处理 n 个二进制位；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def maximumXorProduct(self, a: int, b: int, n: int) -> int:  # a、b：初始的两个数；n：可以改动的低位个数
        mod = 10**9 + 7  # mod：结果需要对 1e9+7 取模
        ax, bx = (a >> n) << n, (b >> n) << n  # 先把低 n 位清零、保留高位：高位是固定的基数
        for i in range(n - 1, -1, -1):  # 从高到低枚举低 n 位
            x = a >> i & 1  # 取出 a 在第 i 位的原始比特
            y = b >> i & 1  # 取出 b 在第 i 位的原始比特
            if x == y:  # 原始两位相同：两边可以同时得到 1
                ax |= 1 << i  # 给 ax 的第 i 位置 1
                bx |= 1 << i  # 给 bx 的第 i 位置 1，两边同时变大
            elif ax > bx:  # 原始两位不同且 ax 更大：把这一位补给更小的 bx
                bx |= 1 << i  # bx 第 i 位置 1，让较小的它追上来
            else:  # 其余情况即 ax <= bx，把这一位补给 ax
                ax |= 1 << i  # ax 第 i 位置 1，让较小的它追上来
        return ax * bx % mod  # Python 大整数不会溢出，最后直接相乘取模
