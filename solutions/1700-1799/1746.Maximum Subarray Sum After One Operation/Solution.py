# 题目：1746. 经过一次操作后的最大子数组和（Maximum Subarray Sum After One Operation）
# 核心思路：用 f 表示「以当前元素结尾、还没用过平方操作」的最大和，g 表示「已经用过平方操作」的最大和，逐个元素滚动更新并取两者较大值。
# 时间复杂度：O(n)，只遍历数组一次；空间复杂度：O(1)，只使用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def maxSumAfterOperation(self, nums: List[int]) -> int:  # nums 是输入数组，返回最多平方一个元素后的最大子数组和
        f = g = 0  # 两个状态都从 0 开始，相当于允许区间从当前位置重新开始，空前缀的和记 0
        ans = -inf  # 答案初始化为负无穷，保证第一次比较就能取到真实值
        for x in nums:  # 逐个元素扩展，枚举以 x 结尾的区间
            ff = max(f, 0) + x  # 未使用平方操作：负前缀直接丢弃，从 x 重新开始
            gg = max(max(f, 0) + x * x, g + x)  # 使用平方操作：要么刚把 x 平方，要么此前已经用过平方操作再直接接上 x
            f, g = ff, gg  # 元组同时赋值，先把两个新值都算好再一起替换，避免互相覆盖
            ans = max(ans, f, g)  # 两种状态取最大，刷新全局答案
        return ans  # 返回全局最大值
