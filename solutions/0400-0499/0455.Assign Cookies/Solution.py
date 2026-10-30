# 题目：455. 分发饼干（Assign Cookies）
# 思路：两边都升序排序，双指针让最小的饼干去满足最容易满足的孩子；饼干不够就跳过，够就同时后移。
# 时间复杂度：O(m log m + n log n)（两次排序）；空间复杂度：O(1)（不计排序自身开销）。
class Solution:  # LeetCode 约定的题解类
    def findContentChildren(self, g: List[int], s: List[int]) -> int:  # g 是每个孩子的胃口，s 是每块饼干的尺寸，返回最多能满足的孩子数
        g.sort()  # 胃口升序排序，优先满足最容易满足的孩子
        s.sort()  # 饼干尺寸升序排序，保证分配的单调性
        j = 0  # j 是当前待分配的饼干下标
        for i, x in enumerate(g):  # 按胃口从小到大依次尝试满足每个孩子（i 是孩子下标，x 是胃口）
            while j < len(s) and s[j] < g[i]:  # 跳过所有尺寸不够的饼干
                j += 1  # 这块饼干太小，换下一块更大的
            if j >= len(s):  # 饼干已经用完，无法再满足更多孩子
                return i  # 只能满足前 i 个孩子（下标 0..i-1）
            j += 1  # 用掉当前这块饼干去满足第 i 个孩子
        return len(g)  # 所有孩子都被满足，答案是孩子总数
