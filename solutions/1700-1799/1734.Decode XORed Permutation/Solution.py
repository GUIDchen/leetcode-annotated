# 题目：1734. 解码异或后的排列（Decode XORed Permutation）
# 思路：encoded[i] = perm[i] ^ perm[i+1]。偶数下标项异或得 a，1..n 全异或得 b，则 perm[-1] = a ^ b，再从后往前逐项反推。
# 时间复杂度：O(n)，三次线性遍历；空间复杂度：O(n)，结果数组。
class Solution:  # LeetCode 约定的题解类
    def decode(self, encoded: List[int]) -> List[int]:  # encoded 长度为 n-1，由原排列相邻两项异或而来
        n = len(encoded) + 1  # 原排列的长度 n
        a = b = 0  # a 累积偶数下标项，b 累积 1..n 的异或
        for i in range(0, n - 1, 2):  # 步长为 2，走遍 0, 2, 4, ...
            a ^= encoded[i]  # 得到 perm[0] ^ perm[2] ^ ...
        for i in range(1, n + 1):  # 遍历 1..n
            b ^= i  # b 等于 perm 全部元素的异或
        perm = [0] * n  # 预先占位的结果数组
        perm[-1] = a ^ b  # 其余项两两抵消后只剩 perm[-1]
        for i in range(n - 2, -1, -1):  # 从倒数第二项开始往前推
            perm[i] = encoded[i] ^ perm[i + 1]  # 由 perm[i] ^ perm[i+1] = encoded[i] 解出 perm[i]
        return perm  # 返回还原好的排列
