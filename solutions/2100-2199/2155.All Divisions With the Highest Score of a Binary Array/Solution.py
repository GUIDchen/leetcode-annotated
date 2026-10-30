# 题目：2155. 分组得分最高的所有下标（All Divisions With the Highest Score of a Binary Array）
# 思路：一次遍历维护分割点左侧 0 的个数 l0 与右侧 1 的个数 r1，得分 l0 + r1 取最大值，并记录所有并列下标。
# 时间复杂度：O(n)，每个元素只被移动一次；空间复杂度：O(1)（不计返回数组），只用了几个计数器。
class Solution:  # LeetCode 约定的题解类
    def maxScoreIndices(self, nums: List[int]) -> List[int]:  # nums：只含 0/1 的数组；返回得分最高的所有分割下标
        l0, r1 = 0, sum(nums)  # l0：左侧 0 的个数；r1：右侧 1 的个数（初始为整个数组 1 的总数）
        mx = r1  # 下标 0 的得分就是 r1，先把它当作当前最高分
        ans = [0]  # 记录所有取得最高分的分割点，初始只有 0
        for i, x in enumerate(nums, 1):  # i 从 1 枚举到 n，表示分割点位置
            l0 += x ^ 1  # x 为 0 时 x^1 = 1，左侧 0 的个数加一；x 为 1 时加 0
            r1 -= x  # 该元素离开右侧，若它是 1 则右侧 1 的个数减一
            t = l0 + r1  # 当前分割点的得分
            if mx == t:  # 与当前最高分相同
                ans.append(i)  # 并列最高分，追加该下标
            elif mx < t:  # 出现更高的得分
                mx = t  # 更新最高分
                ans = [i]  # 之前的下标全部淘汰，只留下当前下标
        return ans  # 返回所有取得最高分的分割下标
