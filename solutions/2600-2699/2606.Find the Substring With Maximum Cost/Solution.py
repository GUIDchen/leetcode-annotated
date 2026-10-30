# 题目：2606. 找到最大开销的子字符串（Find the Substring With Maximum Cost）
# 思路：把字符映射成权值后转为最大子段和；用前缀和减去历史最小前缀和，在线维护最大开销。
# 时间复杂度：O(|s| + |chars|)；空间复杂度：O(|chars|)，权值字典。
class Solution:  # LeetCode 约定的题解类
    def maximumCostSubstring(self, s: str, chars: str, vals: List[int]) -> int:  # s：原字符串；chars/vals：被重新指定权值的字符；返回最大开销子串的开销
        d = {c: v for c, v in zip(chars, vals)}  # 权值字典：只记录被重新指定过的字符
        ans = tot = mi = 0  # ans：最大开销；tot：当前前缀和；mi：历史最小前缀和
        for c in s:  # 逐个字符扫描
            v = d.get(c, ord(c) - ord('a') + 1)  # d.get 取覆盖权值，取不到时用默认权值 ord(c)-ord('a')+1
            tot += v  # 累加前缀和
            ans = max(ans, tot - mi)  # 以当前字符结尾的最大子串开销 = 当前前缀和 - 历史最小前缀和
            mi = min(mi, tot)  # 更新最小前缀和（放在 ans 之后，保证子串非空）
        return ans  # 返回最大开销；全为负时保持 0（允许空子串）
