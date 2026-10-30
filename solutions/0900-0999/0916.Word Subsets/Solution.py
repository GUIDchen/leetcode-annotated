# 题目：916. 单词子集（Word Subsets）
# 思路：先把 words2 中每个字母的频次按单词取最大值合并成统一需求，再逐个检查 words1 的单词是否覆盖该需求。
# 时间复杂度：O(L + |words1| * 26)，L 为所有字符总数；空间复杂度：O(26 + 输出空间)。
class Solution:  # LeetCode 约定的题解类
    def wordSubsets(self, words1: List[str], words2: List[str]) -> List[str]:  # words1 是候选单词，words2 是必须被全部覆盖的约束单词
        cnt = Counter()  # cnt[c] 记录所有 words2 中字母 c 出现次数的最大值，即统一需求
        for b in words2:  # 逐个处理约束单词
            t = Counter(b)  # 统计当前约束单词的字母频次
            for c, v in t.items():  # 遍历本单词的每个 (字母, 次数)
                cnt[c] = max(cnt[c], v)  # 多个约束要同时满足，所以需求取最大值
        ans = []  # 收集满足全部约束的候选单词
        for a in words1:  # 逐个检查候选单词
            t = Counter(a)  # 统计候选单词的字母频次
            if all(v <= t[c] for c, v in cnt.items()):  # 对每个需求字母，检查候选单词里的对应数量是否足够
                ans.append(a)  # 全部满足则加入答案
        return ans  # 返回结果列表
