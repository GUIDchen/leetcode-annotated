# 题目：320. 列举单词的全部缩写（Generalized Abbreviation）
# 思路：对后缀做递归枚举，dfs(i) 只考虑「保留 word[i]」或「把 word[i..j-1] 缩写成数字 j-i」两种分支。
# 时间复杂度：O(2^n * n)，答案规模为 2^(n-1) 量级且每个答案要 O(n) 拼接；空间复杂度：O(2^n * n)，递归保存全部中间结果。
class Solution:  # LeetCode 约定的题解类
    def generateAbbreviations(self, word: str) -> List[str]:  # word 是原单词，返回它的全部缩写形式
        def dfs(i: int) -> List[str]:  # dfs(i) 返回后缀 word[i:] 的所有缩写
            if i >= n:  # 下标已越过末尾，后缀为空
                return [""]  # 空后缀只有一种缩写：空串
            ans = [word[i] + s for s in dfs(i + 1)]  # 情形一：先保留 word[i]，再拼上后缀 word[i+1:] 的每种缩写
            for j in range(i + 1, n + 1):  # 情形二：把 word[i..j-1] 缩写成数字 j-i，再递归处理剩下的后缀
                for s in dfs(j + 1):  # 枚举 word[j+1:] 的每种缩写
                    ans.append(str(j - i) + (word[j] if j < n else "") + s)  # 拼出「数字 + 紧随的字母 + 剩余缩写」，j 越界时不加字母
            return ans  # 返回当前后缀的全部缩写

        n = len(word)  # 单词长度，作为递归的终止边界（dfs 调用时它已定义）
        return dfs(0)  # 从整个单词的起点开始求全部缩写
