# 题目：3706. Maximum Distance Between Unequal Words in Array II（3706. 不同单词间的最大距离 II 🔒）
# 核心思路：最大距离只会出现在“与首词不同”或“与尾词不同”的配对中，一次遍历每个下标，分别与首词、尾词比较并更新最大距离即可。
# 复杂度：时间 O(n)，空间 O(1)。
class Solution:  # LeetCode 约定的题解类
    def maxDistance(self, words: List[str]) -> int:  # 返回两个不同单词之间的最大下标距离
        n = len(words)  # 单词总数
        ans = 0  # 记录当前最大距离
        for i in range(n):  # 从左到右枚举右端点下标 i
            if words[i] != words[0]:  # 与首词不同，就能和下标 0 配对
                ans = max(ans, i + 1)  # 距离为 i - 0 + 1 = i + 1
            if words[i] != words[-1]:  # 与尾词不同，就能和下标 n - 1 配对
                ans = max(ans, n - i)  # 距离为 (n - 1) - i + 1 = n - i
        return ans  # 返回最大距离
