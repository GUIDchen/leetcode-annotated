# 3907. 统计具有相反奇偶性的较小元素 🔒（Count Smaller Elements With Opposite Parity）
# 思路：从右往左扫描，用奇偶两棵树状数组分别维护已经出现过的值（离散化后），对每个元素查询另一奇偶树中小于它的元素个数。
# 复杂度：时间复杂度 O(n log n)，空间复杂度 O(n)。
class Solution:  # LeetCode 约定的题解类
    def countSmallerOppositeParity(self, nums: list[int]) -> list[int]:  # 对每个元素统计其右侧更小且奇偶性相反的元素个数
        n = len(nums)  # 数组长度
        ans = [0] * n  # 答案数组
        sl = [SortedList(), SortedList()]  # 奇偶各一个有序容器，sl[0] 存偶数、sl[1] 存奇数
        for i in range(n - 1, -1, -1):  # 从右往左扫描，保证容器里都是右侧元素
            ans[i] = sl[nums[i] & 1 ^ 1].bisect_left(nums[i])  # 查询另一奇偶容器中严格小于 nums[i] 的元素个数
            sl[nums[i] & 1].add(nums[i])  # 把当前值插入对应奇偶的有序容器
        return ans  # 返回结果
