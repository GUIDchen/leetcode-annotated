# 题目：128. 最长连续序列（Longest Consecutive Sequence）
# 思路：把数组放进集合，对每个 x 顺着 x+1、x+2… 一路删除到断点 y，再用字典 d 记下「从 x 起的连续长度 = 断点后已知长度 + y - x」，每个数字只会被删除一次。
# 时间复杂度：O(n)，每个数字至多被 remove 一次；空间复杂度：O(n)，集合与字典。
class Solution:  # LeetCode 约定的题解类
    def longestConsecutive(self, nums: List[int]) -> int:  # nums 是无序整数数组，返回最长连续序列的长度
        s = set(nums)  # 全部数字放进集合，支持 O(1) 判断与删除
        ans = 0  # 当前找到的最长连续序列长度
        d = defaultdict(int)  # 记录以某个数为起点时向后能延伸多长，缺省值为 0
        for x in nums:  # 依次以每个数作为候选起点
            y = x  # y 用来沿 x+1、x+2… 一直向后探查
            while y in s:  # y 还在集合里，说明这一段是连续的
                s.remove(y)  # 删除 y，保证每个数字只处理一次
                y += 1  # y 后移一位，继续检查下一个数
            d[x] = d[y] + y - x  # 断点 y 若已属于更长的序列，就直接接上它记录的长度
            ans = max(ans, d[x])  # 更新全局最长长度
        return ans  # 返回最长连续序列长度
