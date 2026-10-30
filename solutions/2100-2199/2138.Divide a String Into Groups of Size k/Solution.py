# 题目：2138. 将字符串拆分为若干长度为 k 的组（Divide a String Into Groups of Size k）
# 思路：以步长 k 从 0 开始切片，每段不足 k 个字符时用 ljust 右补 fill 字符。
# 时间复杂度：O(n)，每个字符只被取用一次；空间复杂度：O(n)，结果列表共存放 n 个字符。
class Solution:  # LeetCode 约定的题解类
    def divideString(self, s: str, k: int, fill: str) -> List[str]:  # s：原字符串；k：每组长度；fill：末组不足时使用的填充字符
        return [s[i : i + k].ljust(k, fill) for i in range(0, len(s), k)]  # 按步长 k 枚举每段起点并切片；ljust 把不足 k 长度的末段用 fill 补齐（长度恰好为 k 时不变）
