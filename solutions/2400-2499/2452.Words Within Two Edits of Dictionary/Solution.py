# 题目：2452. 距离字典两次编辑以内的单词（Words Within Two Edits of Dictionary）
# 思路：对每个查询词，依次与字典词逐位比较，用 zip 配对后统计相同位置上不同字符的个数；只要存在不同数小于 3 的字典词，就收录该查询词。
# 时间复杂度：O(q * d * L)，q、d 分别为查询词与字典词的个数，L 为单词长度；空间复杂度：O(1)，除答案数组外只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def twoEditWords(self, queries: List[str], dictionary: List[str]) -> List[str]:  # queries：待检查的查询词；dictionary：字典词
        ans = []  # 保存满足条件的查询词
        for s in queries:  # 逐个处理每个查询词
            for t in dictionary:  # 让当前查询词与每个字典词进行比较
                if sum(a != b for a, b in zip(s, t)) < 3:  # zip 按位配对，sum 统计不同字符个数，小于 3 说明至多替换两次
                    ans.append(s)  # 收录当前查询词
                    break  # 已找到可行字典词，无需再比较后面的字典词
        return ans  # 返回所有两次编辑以内可变成某个字典词的查询词
