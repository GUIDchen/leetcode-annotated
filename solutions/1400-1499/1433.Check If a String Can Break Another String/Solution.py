# 题目：1433. 检查一个字符串是否可以打破另一个字符串（Check If a String Can Break Another String）
# 思路：两串排序后逐位比较；只要存在一个方向满足逐位不小于即可，因此用两次 all 检查两个方向。
# 时间复杂度：O(n log n)，瓶颈在排序；空间复杂度：O(n)，存放排序后的字符列表。
class Solution:  # LeetCode 约定的题解类
    def checkIfCanBreak(self, s1: str, s2: str) -> bool:  # s1、s2：待比较的两个字符串，长度相同
        cs1 = sorted(s1)  # 排序让同一位上比较「第 i 小」的字符，从而判定是否存在可行重排
        cs2 = sorted(s2)  # 对 s2 做同样的排序
        return all(a >= b for a, b in zip(cs1, cs2)) or all(  # 正向检查：排序后每一位都满足 s1[i] >= s2[i]；all 短路，遇到反例立刻停止
            a <= b for a, b in zip(cs1, cs2)  # 反向检查：换过来要求 s2 每一位都 >= s1 的对应位
        )  # 多行调用的结尾括号
