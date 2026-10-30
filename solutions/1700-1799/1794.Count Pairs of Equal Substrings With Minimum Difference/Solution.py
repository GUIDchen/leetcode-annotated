# 题目：1794. 统计距离最小的子串对个数（Count Pairs of Equal Substrings With Minimum Difference）
# 思路：相同子串对的距离只取决于首字符的起点，于是为 secondString 建「字符 → 最后出现下标」表，再扫 firstString 求最小距离并统计并列个数。
# 时间复杂度：O(n + m)；空间复杂度：O(1)，哈希表最多 26 个键。
class Solution:  # 题解类
    def countQuadruples(self, firstString: str, secondString: str) -> int:  # 两个字符串，返回距离最小的子串对个数
        last = {c: i for i, c in enumerate(secondString)}  # 字典推导：字符 → 它在 secondString 中最后出现的下标（后面的覆盖前面的）
        ans, mi = 0, inf  # ans 记方案数；mi 记最小距离，初值正无穷
        for i, c in enumerate(firstString):  # 枚举 firstString 中作为起点的字符
            if c in last:  # 该字符在第二个串里出现过才可能成对
                t = i - last[c]  # 距离：first 中的下标减去 second 中的最后下标
                if mi > t:  # 找到更小的距离
                    mi = t  # 更新最小距离
                    ans = 1  # 重新开始计数
                elif mi == t:  # 距离并列最小
                    ans += 1  # 方案数加一
        return ans  # 返回方案个数
