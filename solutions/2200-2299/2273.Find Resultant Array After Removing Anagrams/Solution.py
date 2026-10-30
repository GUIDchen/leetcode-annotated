# 题目：2273. 移除字母异位词后的结果数组（Find Resultant Array After Removing Anagrams）
# 思路：保留首个单词，之后只保留「与前一个单词不是字母异位词」的单词；用字母计数判断是否互为字母异位词。
# 时间复杂度：O(L)，L 为所有单词字符总数；空间复杂度：O(L)，用于存放结果列表。
class Solution:  # LeetCode 约定的题解类
    def removeAnagrams(self, words: List[str]) -> List[str]:  # words：输入单词数组；返回删除字母异位词后的数组
        def check(s: str, t: str) -> bool:  # 判断 s 与 t 是否「不是」字母异位词：返回 True 表示 t 需要保留
            if len(s) != len(t):  # 长度不同，不可能是同一组字母的重排
                return True  # 直接判定为不同，需要保留 t
            cnt = Counter(s)  # 统计 s 中每个字母出现的次数
            for c in t:  # 用 t 里的字母逐个抵扣这些计数
                cnt[c] -= 1  # 对应字母的计数减 1
                if cnt[c] < 0:  # 减成负数，说明 t 中该字母出现得比 s 多
                    return True  # 计数对不上，不是字母异位词
            return False  # 所有计数都抵消完，说明二者互为字母异位词，t 应当被删除
        return [words[0]] + [t for s, t in pairwise(words) if check(s, t)]  # 首词必定保留；pairwise 依次给出原数组中相邻的 (s, t)，check 为真才保留 t
