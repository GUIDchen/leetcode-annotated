# 3403. 从盒子中找出字典序最大的字符串 I / Find the Lexicographically Largest String From the Box I
# 核心思路：其余 numFriends - 1 个朋友至少各分 1 个字符，故以 i 开头的段最长只能取 min(n - i, n - numFriends + 1)，枚举 i 取字典序最大者
# 复杂度：时间 O(n^2)（字符串比较），空间 O(n)
class Solution:  # 定义题目解答类
    def answerString(self, word: str, numFriends: int) -> str:  # 方法入口：把 word 切成 numFriends 段，返回其中字典序最大的段
        if numFriends == 1:  # 只有一个朋友时整串就是唯一答案
            return word  # 直接返回原串
        n = len(word)  # 记录串长
        return max(word[i : i + n - (numFriends - 1)] for i in range(n))  # 枚举起点并取长度上限 n - numFriends + 1 的前缀（自动截断到串尾），返回其中字典序最大者
