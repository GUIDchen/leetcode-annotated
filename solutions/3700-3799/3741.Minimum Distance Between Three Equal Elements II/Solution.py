# 题目：3741. 三个相等元素之间的最小距离 II（Minimum Distance Between Three Equal Elements II）
# 核心思路：与版本 I 相同——用哈希表把每个取值出现过的下标按顺序收集起来；同一取值中三个下标的两两距离之和为 2*(最大下标-最小下标)，所以只需枚举同一下标列表里相邻的三个位置，取 2*(ls[h+2]-ls[h]) 的最小值。
# 复杂度：时间 O(n)，建表一次扫描，之后每个下标至多被枚举一次；空间 O(n)，哈希表存下所有下标。
class Solution:  # LeetCode 约定的题解类
    def minimumDistance(self, nums: List[int]) -> int:  # nums：整数数组；返回三个相等元素之间的最小距离，凑不出三个则为 -1
        g = defaultdict(list)  # 每个取值对应一个下标列表，列表天然递增
        for i, x in enumerate(nums):  # 一遍扫描建立分组
            g[x].append(i)  # 把当前下标加入该取值的列表
        ans = inf  # 记录最小距离，初值为无穷
        for ls in g.values():  # 遍历每个取值对应的下标列表
            for h in range(len(ls) - 2):  # 枚举同一取值中三个连续下标里的第一个
                i, k = ls[h], ls[h + 2]  # 第一个下标与第三个下标（跳过中间那个，三者相邻才最优）
                ans = min(ans, (k - i) * 2)  # 两两距离之和等于最远跨度乘 2，取最小
        return -1 if ans == inf else ans  # 从未更新过说明某个取值不足三个，返回 -1
