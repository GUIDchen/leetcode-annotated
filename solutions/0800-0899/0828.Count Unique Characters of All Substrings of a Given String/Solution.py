# 题目：828. 统计子串中的唯一字符（Count Unique Characters of All Substrings of a Given String）
# 思路：按字符算贡献。字符的每一处出现位置 v[i] 能被多少个“仅含它一次”的子串算到，就是 (v[i]-v[i-1])*(v[i+1]-v[i])，左右补哨兵后累加。
# 时间复杂度：O(n)，每个位置只扫一次；空间复杂度：O(n)，保存每个字符的出现下标。
class Solution:  # LeetCode 约定的题解类
    def uniqueLetterString(self, s: str) -> int:  # s 是只含大写字母的字符串，返回所有子串的唯一字符数之和
        d = defaultdict(list)  # defaultdict(list)：d[c] 存字符 c 的所有下标，键不存在时自动创建空列表
        for i, c in enumerate(s):  # 遍历字符串，同时拿到下标 i 与字符 c
            d[c].append(i)  # 把下标追加到该字符的位置表
        ans = 0  # 答案累加器
        for v in d.values():  # 只遍历实际出现过的字符；没出现的字符贡献必然为 0，无需处理（等价于 C++ 遍历 26 个字母）
            v = [-1] + v + [len(s)]  # 左右各补一个哨兵 -1 与 n，代表“边界之外”的位置
            for i in range(1, len(v) - 1):  # 跳过两个哨兵，枚举该字符的每个真实出现位置
                ans += (v[i] - v[i - 1]) * (v[i + 1] - v[i])  # 左端点有 v[i]-v[i-1] 种选法、右端点有 v[i+1]-v[i] 种选法，相乘即这一步的贡献
        return ans  # 返回所有子串的唯一字符数之和
