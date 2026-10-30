# 题目：2044. 统计按位或能得到最大值的子集数目（Count Number of Maximum Bitwise-OR Subsets）
# 思路：整个数组的按位或就是任意子集能达到的最大值 mx；再用「选/不选」的递归枚举所有子集，统计或值等于 mx 的个数。
# 时间复杂度：O(2^n)，共 2^n 个子集；空间复杂度：O(n)，递归深度为元素个数。
class Solution:  # LeetCode 约定的题解类
    def countMaxOrSubsets(self, nums: List[int]) -> int:  # nums 是输入数组，返回按位或等于最大值的子集个数
        def dfs(i, t):  # 内层递归函数：i 是当前考虑的下标，t 是已选元素的按位或
            nonlocal ans, mx  # 声明 ans 与 mx 来自外层函数，这里要修改它们
            if i == len(nums):  # 所有元素都决定完了，到达叶子
                if t == mx:  # 当前子集的按位或等于最大值
                    ans += 1  # 这个子集计入答案
                return  # 叶子处理完就回溯
            dfs(i + 1, t)  # 不选 nums[i]，或值不变
            dfs(i + 1, t | nums[i])  # 选 nums[i]，把它的位并入或值

        ans = 0  # 初始化计数器
        mx = reduce(lambda x, y: x | y, nums)  # 用 reduce 把整个数组或起来，得到所有子集能取到的最大或值
        dfs(0, 0)  # 从下标 0、或值 0 开始枚举全部子集
        return ans  # 返回统计结果
