# 题目：2475. 数组中不等三元组的数目（Number of Unequal Triplets in Array）
# 思路：三重循环枚举下标 i<j<k，只要三个位置的数值两两互不相等，就为答案贡献 1，最后返回计数。
# 时间复杂度：O(n^3)，三层循环；空间复杂度：O(1)，只用了常数级计数变量。
class Solution:  # LeetCode 约定的题解类
    def unequalTriplets(self, nums: List[int]) -> int:  # nums 是输入数组，返回满足条件的三元组个数
        n = len(nums)  # 数组长度，作为三层循环的统一上界
        ans = 0  # 答案计数器，初始为 0
        for i in range(n):  # 枚举第一个下标 i
            for j in range(i + 1, n):  # 枚举第二个下标 j，保证 j > i 以避免重复计数
                for k in range(j + 1, n):  # 枚举第三个下标 k，保证 k > j，这样每组下标只被枚举一次
                    ans += (  # 跨行累加，括号内是本轮的布尔判断结果
                        nums[i] != nums[j] and nums[j] != nums[k] and nums[i] != nums[k]  # 三个数两两不等：布尔值 True 会被当成 1 累加到 ans 上
                    )  # 累加语句结束
        return ans  # 返回满足条件的三元组总数
