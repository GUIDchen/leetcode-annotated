# 题目：167. 两数之和 II - 输入有序数组（Two Sum II - Input Array Is Sorted）
# 核心思路：利用数组有序，枚举第一个数，在它右侧用 bisect_left 二分查找补数 target - numbers[i]，命中即返回 1 基下标。
# 时间复杂度：O(n log n)，每个位置一次二分；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def twoSum(self, numbers: List[int], target: int) -> List[int]:  # numbers 升序排列，返回两个数的 1 基下标
        n = len(numbers)  # 数组长度，用于判断二分结果是否越界
        for i in range(n - 1):  # 枚举较小的那个数的下标，右侧至少留一个空位
            x = target - numbers[i]  # 需要的另一个数（补数）
            j = bisect_left(numbers, x, lo=i + 1)  # 在 i 右侧的区间里二分查找 x 的第一个位置
            if j < n and numbers[j] == x:  # 命中且确实等于 x 才算找到
                return [i + 1, j + 1]  # 题目要求返回 1 基下标
