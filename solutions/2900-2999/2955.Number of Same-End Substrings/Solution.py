# 题目：2955. 同端子串的数量（Number of Same-End Substrings）
# 思路：只给出现过的字母建前缀计数数组；回答询问时取区间内每个字母的出现次数 x，贡献 x 个单字符子串加 C(x,2) 个更长子串。
# 时间复杂度：O((n + q) * 26)，每次询问只扫出现过的字母；空间复杂度：O(26n)，前缀计数数组。
class Solution:  # LeetCode 约定的题解类
    def sameEndSubstringCount(self, s: str, queries: List[List[int]]) -> List[int]:  # s 是字符串，queries 是 [l, r] 询问列表；返回每个询问的答案
        n = len(s)  # 字符串长度
        cs = set(s)  # 集合去重：只给出现过的字母建表，省空间
        cnt = {c: [0] * (n + 1) for c in cs}  # 每个字母单独一条长度为 n+1 的前缀计数数组
        for i, a in enumerate(s, 1):  # 从 1 开始编号，便于用 i-1 取前一位
            for c in cs:  # 对每个出现过的字母同步推进前缀计数
                cnt[c][i] = cnt[c][i - 1]  # 先继承前一位的前缀计数
            cnt[a][i] += 1  # 当前字符对应的字母计数加一
        ans = []  # 存放每个询问的答案
        for l, r in queries:  # 逐个处理询问区间
            t = r - l + 1  # 长度为 1 的子串都满足首尾相同，先计入
            for c in cs:  # 对每个出现过的字母统计区间出现次数
                x = cnt[c][r + 1] - cnt[c][l]  # 前缀和相减得到字母 c 在 [l, r] 内的出现次数
                t += x * (x - 1) // 2  # 任选两个位置作为首尾，共 C(x, 2) 个更长子串
            ans.append(t)  # 记录该询问的答案
        return ans  # 返回全部询问的答案
