# 题目：1790. 仅执行一次字符串交换能否使两个字符串相等（Check if One String Swap Can Make Strings Equal）
# 思路：用 zip 同步遍历两串，统计不同位置并记录最近一处的两个字符；超过两处或第二处不交叉相等即失败，最终排除「仅一处不同」。
# 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，仅常数个变量。
class Solution:  # LeetCode 约定的题解类
    def areAlmostEqual(self, s1: str, s2: str) -> bool:  # 返回是否只交换 s1 的一对字符就能让两串相等
        cnt = 0  # 不同位置的个数
        c1 = c2 = None  # 记录最近一处不同位置上的两个字符，初始为 None
        for a, b in zip(s1, s2):  # 同步遍历两串，逐位取出 a、b 做比较
            if a != b:  # 该位置字符不同
                cnt += 1  # 不同位置计数加一
                if cnt > 2 or (cnt == 2 and (a != c2 or b != c1)):  # 超过 2 处，或第 2 处与第 1 处不能交叉配对（a 应等于上一个 b、b 应等于上一个 a），均无解
                    return False  # 无解，直接返回 False
                c1, c2 = a, b  # 记住这一处的两个字符，供下一处交叉校验
        return cnt != 1  # 0 处或 2 处不同可行；仅 1 处不同无法用一次交换修复
