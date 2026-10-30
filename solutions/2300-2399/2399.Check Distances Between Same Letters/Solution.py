# 题目：2399. 检查相同字母间的距离（Check Distances Between Same Letters）
# 思路：字典记录每个字母首次出现的位置（从 1 开始编号），再次出现时校验中间字符数是否等于 distance。
# 时间复杂度：O(n)，只遍历字符串一次；空间复杂度：O(1)，字典最多 26 个键。
class Solution:  # LeetCode 约定的题解类
    def checkDistances(self, s: str, distance: List[int]) -> bool:  # s：待检查字符串；distance：每个字母规定的间隔
        d = defaultdict(int)  # 默认值为 0 的字典，0 表示该字母还没出现过
        for i, c in enumerate(map(ord, s), 1):  # 先把字符转成 ASCII 码，再用 1 起始编号枚举
            j = c - ord("a")  # 减去 'a' 的码值，得到 0..25 的字母序号
            if d[j] and i - d[j] - 1 != distance[j]:  # 该字母出现过，且两次下标差减 1（中间字符数）不等于规定距离
                return False  # 距离不符，立即返回 False
            d[j] = i  # 记录该字母的位置（1 起始编号，天然区分“未出现”的 0）
        return True  # 遍历完没有冲突，返回 True
