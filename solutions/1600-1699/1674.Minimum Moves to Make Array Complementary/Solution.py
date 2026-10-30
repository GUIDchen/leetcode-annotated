# 题目：1674. 使数组互补的最少操作次数（Minimum Moves to Make Array Complementary）
# 思路：首尾配对，对每一对 (x ≤ y) 按目标和 t 的区间用差分数组做区间加，最后对差分数组做前缀和取最小值。
# 时间复杂度：O(n + limit)，配对 O(n/2)、前缀和 O(limit)；空间复杂度：O(limit)，差分数组长度为 2·limit + 2。
class Solution:  # LeetCode 约定的题解类
    def minMoves(self, nums: List[int], limit: int) -> int:  # nums：待配对数组；limit：每个元素只能改成 1..limit 的值
        d = [0] * (2 * limit + 2)  # 差分数组，下标是目标和 t，多留两位避免越界
        n = len(nums)  # 数组长度，用于定位对称位置
        for i in range(n // 2):  # 只枚举前半部分，与后半部分首尾配对
            x, y = nums[i], nums[-i - 1]  # 取出对称的两个元素 x = nums[i]、y = nums[-i-1]
            if x > y:  # 保证 x ≤ y，方便后面按区间分类讨论
                x, y = y, x  # 通过元组交换让 x ≤ y
            d[2] += 2  # t ∈ [2, x]：两个数都要改，整体 +2
            d[x + 1] -= 2  # t = x + 1 处扣掉 +2 的区间尾
            d[x + 1] += 1  # t ∈ [x+1, x+y-1]：只需改一个数，区间 +1
            d[x + y] -= 1  # t = x + y 处扣掉 +1 的区间尾（此处 0 次操作）
            d[x + y + 1] += 1  # t ∈ [x+y+1, y+limit]：只需改一个数，区间重新 +1
            d[y + limit + 1] -= 1  # t = y+limit+1 处扣掉 +1 的区间尾
            d[y + limit + 1] += 2  # t ∈ [y+limit+1, 2·limit]：两个数都要改，恢复 +2
        return min(accumulate(d[2:]))  # 对差分数组做前缀和（accumulate 累加），取所有目标和中的最小值
