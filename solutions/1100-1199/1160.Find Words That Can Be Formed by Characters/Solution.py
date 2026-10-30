# 题目：1160. 拼写单词（Find Words That Can Be Formed by Characters）
# 思路：先统计 chars 各字母的可用次数，再逐词统计用量，任一字母超量则该词不可拼出。
# 时间复杂度：O(L)，L 为 chars 与所有单词的总长度；空间复杂度：O(1)（固定 26 个字母）。
class Solution:  # LeetCode 约定的题解类
    def countCharacters(self, words: List[str], chars: str) -> int:  # words 是候选单词列表，chars 是可用字符集合
        cnt = Counter(chars)  # 统计 chars 中每个字母的可用次数
        ans = 0  # 可拼出单词的总长度
        for w in words:  # 逐个检查每个单词
            wc = Counter(w)  # 统计当前单词里每个字母的用量
            if all(cnt[c] >= v for c, v in wc.items()):  # 每个字母的用量都不超过可用数量
                ans += len(w)  # 该单词可拼出，累加其长度
        return ans  # 返回总长度
