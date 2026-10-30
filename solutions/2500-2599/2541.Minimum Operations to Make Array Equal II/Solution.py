# 题目：2541. 使数组中所有元素相等的最小操作数 II（Minimum Operations to Make Array Equal II）
# 思路：每次操作让一个位置 +k、另一个位置 -k，统计每对差值需要增加/减少的「k 的份数」，两边份数相等即可行。
# 时间复杂度：O(n)，一趟线性扫描；空间复杂度：O(1)，只用了两个累加变量。
class Solution:  # LeetCode 约定的题解类
    def minOperations(self, nums1: List[int], nums2: List[int], k: int) -> int:  # 返回最少操作次数；无解时返回 -1（List 由判题环境隐式提供，不补 import）
        a = b = 0  # 链式赋值：a 累计「需要增加」的份数，b 累计「需要减少」的份数
        for x, y in zip(nums1, nums2):  # 把两个数组按位配对遍历，x 来自 nums1，y 来自 nums2
            if x == y:  # 这一位已经相等，不需要任何操作
                continue  # 跳过本位置，直接处理下一位
            if k == 0 or (x - y) % k:  # k 为 0 时无法改变任何值；余数非 0 表示差值不是 k 的整数倍，同样无解
                return -1  # 无解，直接返回 -1
            t = (x - y) // k  # 向下取整除法得到「k 的份数」：正数表示要减少，负数表示要增加（此时差值已被前一步保证整除）
            if t < 0:  # t 为负说明 nums1 这一位偏小，需要被增加
                a += -t  # 把「需要增加」的份数累加到 a
            else:  # 否则 nums1 这一位偏大，需要被减少
                b += t  # 把「需要减少」的份数累加到 b
        return a if a == b else -1  # 每次操作一加一减，只有两个方向份数相等才能配平；否则无解
