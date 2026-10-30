# 题目：740. 删除并获得点数（Delete and Earn）
# 思路：先把相同数值的点数聚合到值域桶 total，问题变成「选数值 i 就不能选 i-1、i+1」，即值域上的打家劫舍 DP。
# 时间复杂度：O(n + V)，V 为最大数值；空间复杂度：O(V)，值域桶数组。
class Solution:  # LeetCode 约定的题解类
    def deleteAndEarn(self, nums: List[int]) -> int:  # nums：给定的整数数组，返回能获得的最大点数
        mx = -inf  # 先求最大值决定桶的大小；-inf 保证任何元素都能更新它
        for num in nums:  # 遍历数组找最大值
            mx = max(mx, num)  # 用当前数与已知最大值比较并更新
        total = [0] * (mx + 1)  # 值域桶：下标即数值，桶里存选中该数值能拿到的总分；mx + 1 保证下标 0..mx 都存在
        for num in nums:  # 再次遍历数组做聚合
            total[num] += num  # 同值的数可以一次全部拿走，因此直接加到对应桶里
        first = total[0]  # DP 初值：只考虑数值 0 时的最优解（first 表示「隔一项」的最优值）
        second = max(total[0], total[1])  # 考虑数值 0、1 时的最优解（second 表示「前一项」的最优值）
        for i in range(2, mx + 1):  # 从数值 2 开始递推到最大值
            cur = max(first + total[i], second)  # 两种决策取大：选 i 则加上隔一项的 first，不选则沿用 second
            first = second  # 滚动：first 前进到上一轮的 second
            second = cur  # 滚动：second 更新为当前最优值
        return second  # 扫完值域后 second 就是答案
