# 题目：2423. 删除字符使频率相同（Remove Letter To Equalize Frequency）
# 思路：用 Counter 统计每个字符的频率，枚举试着把某个字符的频率减一，再看剩下的非零频率是否只有一种。
# 时间复杂度：O(k × k + n)，k 为不同字符数（最多 26），统计一次后最多做 k 次遍历；空间复杂度：O(k)，即 O(1)。
class Solution:  # LeetCode 约定的题解类
    def equalFrequency(self, word: str) -> bool:  # word 是输入字符串，判断删掉一个字符后频率能否全部相同
        cnt = Counter(word)  # 统计每个字符的出现次数，得到「字符 → 频率」的映射
        for c in cnt.keys():  # 枚举作为「被删除字符」的候选
            cnt[c] -= 1  # 试删一个该字符，频率减一（减到 0 也保留在字典里）
            if len(set(v for v in cnt.values() if v)) == 1:  # 只看还存在的字符（频率非 0），若频率种类只有一种则全部相同
                return True  # 找到可行方案，立即返回 True
            cnt[c] += 1  # 恢复现场：把频率加回去，继续尝试下一个字符
        return False  # 所有字符都试过仍无法相等，返回 False
