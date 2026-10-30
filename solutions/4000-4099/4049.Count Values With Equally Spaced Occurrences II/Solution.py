# 题目：4049. 统计等间距出现整数数目 II（Count Values With Equally Spaced Occurrences II）
# 思路：哈希表把「整数 → 出现下标列表」分组，再逐组检查：出现次数不足 3 次直接跳过，否则以第一段间隔为基准，验证所有相邻下标之差是否都相等，全部相等才算等间距出现。
# 复杂度：时间复杂度 O(n)，n 为数组长度（每个下标只被检查常数次）；空间复杂度 O(n)，哈希表存放所有下标。
class Solution:  # LeetCode 约定的题解类
    def countSpecialIntegers(self, nums: list[int]) -> int:  # nums：输入数组；返回所有出现位置等间距（至少 3 次）的不同整数个数
        g = defaultdict(list)  # g[x]：整数 x 出现的所有下标
        for i, x in enumerate(nums):  # 遍历数组，同时取下标和值
            g[x].append(i)  # 把下标追加到该值对应的位置列表
        ans = 0  # 满足条件的整数个数
        for pos in g.values():  # 遍历每个值的位置列表
            if len(pos) < 3:  # 出现次数不足 3 次，不可能等间距
                continue  # 直接跳过这一组
            d = pos[1] - pos[0]  # 以第一段间隔作为基准间隔
            if all(j - i == d for i, j in pairwise(pos)):  # 相邻下标两两作差，全部等于 d 才算等间距
                ans += 1  # 计数加一
        return ans  # 返回满足条件的整数个数
