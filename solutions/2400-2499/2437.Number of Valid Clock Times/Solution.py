# 题目：2437. 有效时间的数目（Number of Valid Clock Times）
# 思路：枚举全部 24×60 个时间点，格式化成 "HH:MM" 后用 all() 逐位比对，'?' 当作通配符，再对匹配结果求和。
# 时间复杂度：O(24 * 60 * 5)，枚举量固定故为常数级；空间复杂度：O(1)，每个候选时间只生成一个临时字符串。
class Solution:  # LeetCode 约定的题解类
    def countTime(self, time: str) -> int:  # time：形如 "??:??" 的模式串，'?' 可以匹配任意数字
        def check(s: str, t: str) -> bool:  # 内层函数：判断候选时间串 s 是否能匹配模式串 t
            return all(a == b or b == '?' for a, b in zip(s, t))  # 逐位比对：字符相等或模式位为 '?' 即通过，全部通过才返回 True

        return sum(  # 对 0..23 时、0..59 分的全部组合计数
            check(f'{h:02d}:{m:02d}', time) for h in range(24) for m in range(60)  # 生成器表达式：每个候选时间先格式化再交给 check
        )  # sum 收尾：返回匹配模式串的时间个数
