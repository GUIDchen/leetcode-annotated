# 题目：1317. 将整数转换为两个无零整数的和（Convert Integer to the Sum of Two No-Zero Integers）
# 思路：从 1 开始枚举第一个加数 a，令 b = n - a，检查两者十进制写法都不含 0 即返回。
# 时间复杂度：O(n) 级别的枚举，实际很快命中；空间复杂度：O(1)，只用常数字符串。
class Solution:  # LeetCode 约定的题解类
    def getNoZeroIntegers(self, n: int) -> List[int]:  # 把 n 拆成两个各位都不含 0 的正整数之和
        for a in count(1):  # 用 itertools.count 从 1 开始无限递增地枚举第一个加数
            b = n - a  # 第二个加数由 a 唯一确定
            if "0" not in f"{a}{b}":  # f-string 拼接两个数后判断字符串里是否出现字符 0
                return [a, b]  # 两个加数都不含 0，即为答案
