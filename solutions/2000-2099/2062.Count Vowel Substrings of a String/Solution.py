# 题目：2062. 统计字符串中的元音子字符串（Count Vowel Substrings of a String）
# 思路：枚举子串左端点 i，再向右扩展右端点；遇到非元音立即中断，用集合去重后判断是否集齐 5 个元音。
# 时间复杂度：O(n^2)，每个左端点最多向右扩 n 步；空间复杂度：O(1)，集合最多只存 5 个字符。
class Solution:  # LeetCode 约定的题解类
    def countVowelSubstrings(self, word: str) -> int:  # word：只含英文小写字母的字符串
        s = set("aeiou")  # 五个元音组成的集合，用于快速判断
        ans, n = 0, len(word)  # ans 统计子串个数，n 是字符串长度
        for i in range(n):  # 枚举子串的左端点 i
            t = set()  # 当前这段子串里出现过的元音集合
            for c in word[i:]:  # 从 i 开始向右逐个取字符作为右端点
                if c not in s:  # 遇到非元音
                    break  # 更长的子串也不可能全是元音，中断内层循环
                t.add(c)  # 把当前元音加入集合（重复元音自动去重）
                ans += len(t) == 5  # 五种元音齐全时，这个子串才算符合条件
        return ans  # 返回符合条件的子串总数
