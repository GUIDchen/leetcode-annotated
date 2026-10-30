# 题目：2023. 连接后等于目标字符串的字符串对（Number of Pairs of Strings With Concatenation Equal to Target）
# 思路：用生成器表达式枚举全部有序下标对 (i, j)，筛选下标不同且 nums[i] + nums[j] == target 的组合，再用 sum 统计 True 的个数。
# 时间复杂度：O(n^2 * L)，L 为字符串拼接比较的长度；空间复杂度：O(L)，拼接产生的临时字符串。
class Solution:  # LeetCode 约定的题解类
    def numOfPairs(self, nums: List[str], target: str) -> int:  # nums：候选字符串数组；target：目标字符串
        n = len(nums)  # 数组长度，供两层下标枚举使用
        return sum(  # sum 把每个 True 当作 1 累加，得到合法有序对个数
            i != j and nums[i] + nums[j] == target for i in range(n) for j in range(n)  # 下标不同且拼接结果等于目标串的每一个配对
        )  # 生成器表达式结束
