# 题目：1023. 驼峰式匹配（Camelcase Matching）
# 思路：双指针贪心匹配——pattern 中的字符在查询串里必须按顺序出现，查询串中多出来的小写字母可以跳过，但大写字母不能跳过。
# 时间复杂度：O(m * |queries|)，m 为单个查询串长度；空间复杂度：O(1)，只用两个指针（不计输出数组）。
class Solution:  # LeetCode 约定的题解类
    def camelMatch(self, queries: List[str], pattern: str) -> List[bool]:  # queries：待检查的字符串列表；pattern：目标驼峰模式；返回每个查询串是否匹配
        def check(s, t):  # 内部判定函数：s 为查询串，t 为模式串
            m, n = len(s), len(t)  # m 是查询串长度，n 是模式串长度
            i = j = 0  # i 遍历 s，j 遍历 t，二者同时从 0 开始
            while j < n:  # 以模式串为准逐个匹配
                while i < m and s[i] != t[j] and s[i].islower():  # 跳过 s 中多余的小写字母，它们可以被忽略
                    i += 1  # 前移 s 的指针
                if i == m or s[i] != t[j]:  # s 已结束，或当前字符与模式要求不符（大写字母不能跳过）
                    return False  # 这个查询串匹配失败
                i, j = i + 1, j + 1  # 这一位匹配成功，两个指针一起后移
            while i < m and s[i].islower():  # 模式串匹配完后，s 尾部若还有字符，必须全部是小写
                i += 1  # 继续跳过尾部小写字母
            return i == m  # 只有 i 到达末尾，才说明没有多余的大写字母

        # 对每个查询串套用上面的判定逻辑，按原顺序收集结果
        return [check(q, pattern) for q in queries]  # 列表推导式：逐个查询串调用 check
