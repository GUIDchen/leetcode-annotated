# 题目：2557. 从一个范围内选择最多整数 II（Maximum Number of Integers to Choose From a Range II）
# 思路：加上虚拟边界 0 与 n+1 后排序去重，相邻禁用值之间是一段连续可选区间；每段二分出剩余预算内最多能选几个（取最小的若干个数），再扣掉对应的等差数列和。
# 时间复杂度：O(b log b + b log n)，b 为禁用值个数；空间复杂度：O(b)，排序去重后的列表。
class Solution:  # LeetCode 约定的题解类
    def maxCount(self, banned: List[int], n: int, maxSum: int) -> int:  # banned 是禁用数字，n 是范围上界，maxSum 是所选数字之和的上限
        banned.extend([0, n + 1])  # 补上虚拟左右边界，把整个范围切成若干段连续可选区间
        ban = sorted(set(banned))  # 排序并去重，相邻两个禁用值之间就是没有被禁用的数字
        ans = 0  # ans 记录已经选了多少个数字
        for i, j in pairwise(ban):  # 依次取出相邻的禁用值 i 与 j，可选区间是 i+1 .. j-1
            left, right = 0, j - i - 1  # 二分答案的上下界：0 个到区间长度个
            while left < right:  # 二分找这段区间内最多能选几个数
                mid = (left + right + 1) >> 1  # 取上中位数，保证 left 能不断逼近答案
                if (i + 1 + i + mid) * mid // 2 <= maxSum:  # 从 i+1 加到 i+mid 的等差数列和不超过预算
                    left = mid  # mid 可行，尝试选更多
                else:  # 和已经超预算
                    right = mid - 1  # mid 不可行，往小处继续找
            ans += left  # 累加这段选中的个数
            maxSum -= (i + 1 + i + left) * left // 2  # 从预算里扣掉这段实际消耗的和
            if maxSum <= 0:  # 预算已经用完
                break  # 后面的区间只会更贵，提前结束
        return ans  # 返回最多能选的整数个数
