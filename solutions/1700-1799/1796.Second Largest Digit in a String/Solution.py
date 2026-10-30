# 题目：1796. 字符串中第二大的数字（Second Largest Digit in a String）
# 思路：一次遍历，a、b 分别维护最大与严格次大的数字，遇到数字按大小关系更新。
# 时间复杂度：O(n)；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def secondHighest(self, s: str) -> int:  # s：输入字符串，返回第二大的数字，不存在则返回 -1
        a = b = -1  # 链式赋值：a 为最大数字，b 为第二大数字，-1 表示未出现
        for c in s:  # 遍历字符串的每个字符
            if c.isdigit():  # 只处理数字字符
                v = int(c)  # 字符转成整数
                if v > a:  # 出现了新的最大值
                    a, b = v, a  # 同时赋值：a 取新值，b 取旧的最大值
                elif b < v < a:  # 链式比较：严格小于最大值且大于当前第二大
                    b = v  # 更新第二大数字
        return b  # 返回第二大数字
