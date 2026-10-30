# 题目：41. 缺失的第一个正数（First Missing Positive）
# 思路：原地哈希——把每个落在 [1, n] 内的数换到下标 v-1 上；再从头扫一遍，第一个 nums[i] != i+1 的位置对应答案 i+1，全部对得上则答案是 n+1。
# 时间复杂度：O(n)，每个数最多被交换常数次；空间复杂度：O(1)，只用了几个临时变量。
class Solution:  # LeetCode 约定的题解类
    def firstMissingPositive(self, nums: List[int]) -> int:  # nums 是整数数组；返回其中缺失的最小正整数
        n = len(nums)  # n 既是数组长度，也是答案上界：长度 n 最多容纳 1..n，所以答案必在 1..n+1
        for i in range(n):  # 第一趟：逐格处理，把 [1, n] 内的数换到它该在的下标上
            while 1 <= nums[i] <= n and nums[i] != nums[nums[i] - 1]:  # 链式比较：当前数合法且不在自己位置上就继续换；用 while 是因为换进来的新值可能还要挪
                j = nums[i] - 1  # 目标下标：数值 v 应放在 v-1 处
                nums[i], nums[j] = nums[j], nums[i]  # 元组解包完成交换：把 nums[i] 的值送到 j，同时把原 nums[j] 取回 i
        for i in range(n):  # 第二趟：寻找第一个位不配值的位置
            if nums[i] != i + 1:  # 位置 i 上本应是 i+1，不相等说明 i+1 缺失
                return i + 1  # 第一个不匹配处就是缺失的最小正整数
        return n + 1  # 1..n 全都到位，缺失的最小正整数只能是 n+1
