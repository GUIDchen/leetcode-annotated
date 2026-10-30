# 题目：1198. 找出所有行中最小公共元素（Find Smallest Common Element in All Rows）
# 思路：计数器统计每个元素出现在多少行里；最后一行升序扫描，第一个计数达到行数的元素即答案。
# 时间复杂度：O(mn)，每个元素统计一次；空间复杂度：O(C)，C 为不同元素的个数。
class Solution:  # LeetCode 约定的题解类
    def smallestCommonElement(self, mat: List[List[int]]) -> int:  # mat 是每行升序的矩阵，返回所有行共有的最小元素
        cnt = Counter()  # 计数器：键是元素值，值是包含该元素的行数
        for row in mat:  # 逐行遍历矩阵
            for x in row:  # 遍历当前行中的每个元素
                cnt[x] += 1  # x 的出现行数加一
                if cnt[x] == len(mat):  # 计数等于行数，说明每一行都含有 x
                    return x  # 返回 x；行内升序保证它是最小的公共元素
        return -1  # 没有公共元素，按题目约定返回 -1
