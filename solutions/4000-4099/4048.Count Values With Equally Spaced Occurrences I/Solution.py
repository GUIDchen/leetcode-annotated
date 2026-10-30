# 题目：4048. 统计等间距出现整数数目 I（Count Values With Equally Spaced Occurrences I）
# 思路：哈希表把「整数 → 出现下标列表」分组，再逐组检查：只有恰好出现 3 次且首尾下标之和等于中间下标两倍（即 pos[0]、pos[1]、pos[2] 等差）的整数才算等间距出现。
# 复杂度：时间复杂度 O(n)，n 为数组长度；空间复杂度 O(n)，哈希表存放所有下标。
class Solution:  # LeetCode 约定的题解类
    def countSpecialIntegers(self, nums: list[int]) -> int:  # nums：输入数组；返回出现 3 次且三个下标等间距的不同整数个数
        g = defaultdict(list)  # g[x]：整数 x 出现的所有下标
        for i, x in enumerate(nums):  # 遍历数组，同时取下标 i 和值 x
            g[x].append(i)  # 把下标追加到该值对应的位置列表
        return sum(  # 统计满足「恰好 3 次且三个下标等间距」的整数个数（布尔值求和）
            len(pos) == 3 and pos[0] + pos[2] == pos[1] * 2 for pos in g.values()  # 条件成立时布尔值为 True，作为 1 累加
        )  # 生成器表达式结束
