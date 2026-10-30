# 题目：189. 轮转数组（Rotate Array）
# 思路：三次翻转。整体翻转一次，再把前 k 段和后 n-k 段分别翻转，效果等同于整体右移 k 位。
# 时间复杂度：O(n)，每个元素被翻转常数次；空间复杂度：O(1)，原地交换不使用额外数组。
class Solution:  # LeetCode 约定的题解类
    def rotate(self, nums: List[int], k: int) -> None:  # nums 是待轮转数组，k 是右移位数，要求原地修改
        def reverse(i: int, j: int):  # 内层函数：原地翻转 nums[i..j]（闭区间）
            while i < j:  # 双指针相向而行，相遇即停
                nums[i], nums[j] = nums[j], nums[i]  # 同时交换左右两个元素
                i, j = i + 1, j - 1  # 左指针右移、右指针左移

        n = len(nums)  # 数组长度
        k %= n  # k 可能大于 n，取模得到真实偏移量，同时防止切片下标越界
        reverse(0, n - 1)  # 第一次翻转：整个数组逆序
        reverse(0, k - 1)  # 第二次翻转：前 k 个元素（原数组的后 k 个）恢复正序
        reverse(k, n - 1)  # 第三次翻转：剩余 n-k 个元素恢复正序
