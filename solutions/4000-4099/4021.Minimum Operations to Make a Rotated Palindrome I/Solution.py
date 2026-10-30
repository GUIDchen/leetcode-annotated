# 题目：4021. 得到旋转回文字符串的最少操作次数 I（Minimum Operations to Make a Rotated Palindrome I）
# 思路：枚举左旋次数 k（旋 n 次回到原串，只需 0..n-1），先计入旋转代价 k；旋转后用双指针检查每一对对称字符，改成相同字母的代价为 min(|x-y|, 26-|x-y|)（可正向递增，也可绕过 z→a 反向靠近），累加后取所有 k 的最小值。
# 时间复杂度：O(n²)，n 种旋转 × 每次 O(n) 对称检查；空间复杂度：O(1)，只用常数个指针与累加变量。
class Solution:  # LeetCode 约定的题解类
    def minOperations(self, s: str) -> int:  # s：小写字母串；返回用「字符递增」与「左旋」得到回文串的最少操作次数
        n = len(s)  # 字符串长度 n，最多考虑 n 种旋转
        ans = inf  # 最少操作次数，先置为无穷大
        for k in range(n):  # 枚举左旋次数 k（旋 n 次回到原串）
            t = k  # 旋转本身花费 k 次操作，先计入总代价
            i, j = 0, n - 1  # 双指针：i 从头、j 从尾向中间靠拢
            while i < j:  # 逐对检查回文对称位置
                x = ord(s[(i + k) % n]) - ord('a')  # 左旋 k 次后，位置 i 上是原下标 (i + k) % n 的字符
                y = ord(s[(j + k) % n]) - ord('a')  # 对称位置 j 上是原下标 (j + k) % n 的字符
                d = abs(x - y)  # 两个字符在字母表中的序号差
                t += min(d, 26 - d)  # 正向递增与绕过 z→a 反向靠近，取较小的代价
                i, j = i + 1, j - 1  # 双指针同时向中间收缩
            ans = min(ans, t)  # 用这次旋转方案的代价更新最优解
        return ans  # 返回所有旋转方案中最少的操作次数
