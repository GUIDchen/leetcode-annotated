# 3662. Filter Characters by Frequency（3662. 按频率筛选字符）🔒
# 核心思路：先用 Counter 统计字符出现次数，再按原顺序保留出现次数小于 k 的字符。
# 复杂度：时间 O(n)，空间 O(不同字符个数)。
class Solution:  # 定义题解类
    def filterCharacters(self, s: str, k: int) -> str:  # 保留 s 中出现次数小于 k 的字符，返回过滤后的字符串
        cnt = Counter(s)  # 统计每个字符的出现次数
        ans = []  # 保存过滤后的字符
        for c in s:  # 按原顺序遍历字符串
            if cnt[c] < k:  # 频次小于 k 的字符需要保留
                ans.append(c)  # 追加到结果列表
        return "".join(ans)  # 拼接成字符串返回
