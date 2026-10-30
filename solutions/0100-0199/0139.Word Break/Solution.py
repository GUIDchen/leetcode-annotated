# 题目：139. 单词拆分（Word Break）
# 思路：动态规划，f[i] 表示前缀 s[:i] 能否被字典完整拆分，只要存在切分点 j 使 f[j] 与 s[j:i] 同时成立即可。
# 时间复杂度：O(n^2) 次切片与成员判断（切片另计 O(n)）；空间复杂度：O(n)，列表 f。
class Solution:  # LeetCode 约定的题解类
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:  # s：待拆分字符串；wordDict：可用单词表；返回能否完整拆分
        words = set(wordDict)  # 转成集合，让子串是否属于字典的判断接近 O(1)
        n = len(s)  # n：字符串长度，也是 DP 的规模
        f = [True] + [False] * n  # f[i] 表示前缀 s[:i] 能否拆分；f[0]=True 是空串的边界
        for i in range(1, n + 1):  # 按前缀长度 i 从小到大递推
            f[i] = any(f[j] and s[j:i] in words for j in range(i))  # 只要某个切分点 j 满足前半段可拆且 s[j:i] 是单词，f[i] 就成立
        return f[n]  # 整串是否可拆分即答案
