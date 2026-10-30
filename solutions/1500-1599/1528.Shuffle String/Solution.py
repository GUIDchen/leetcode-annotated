# 题目：1528. 重新排列字符串（Shuffle String）
# 思路：先按长度建好空位列表，再用 zip 同时遍历字符与其目标下标，直接把字符放到目标位置，最后拼回字符串。
# 时间复杂度：O(n)，每个字符只处理一次；空间复杂度：O(n)，需要长度为 n 的列表暂存结果。
class Solution:  # LeetCode 约定的题解类
    def restoreString(self, s: str, indices: List[int]) -> str:  # s 是原字符串，indices 记录每个字符要去的目标下标
        ans = [None] * len(s)  # 先分配长度 n 的列表，每个位置稍后填入对应字符
        for c, j in zip(s, indices):  # zip 同时取出字符 c 和它的目标下标 j
            ans[j] = c  # 把字符 c 直接写到目标位置 j 上
        return "".join(ans)  # 把列表拼回一个完整字符串并返回
