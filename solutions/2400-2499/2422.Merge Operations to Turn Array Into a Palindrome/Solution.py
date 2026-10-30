# 题目：2422. 使用合并操作将数组转换为回文序列（Merge Operations to Turn Array Into a Palindrome）
# 思路：左右双指针分别维护两段的累计和 a、b，哪边小就把下一个元素并进来，直到两端累计和相等；每合并一次计数加一。
# 时间复杂度：O(n)，两指针只向中间移动，每个元素至多被并入一次；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minimumOperations(self, nums: List[int]) -> int:  # nums 是输入数组，返回变成回文所需的最少合并次数
        i, j = 0, len(nums) - 1  # 左指针指向首元素，右指针指向尾元素
        a, b = nums[i], nums[j]  # a、b 分别是左段与右段的累计和（Python 大整数，无需担心溢出）
        ans = 0  # 记录合并操作的次数
        while i < j:  # 两端还没相遇，继续处理
            if a < b:  # 左段累计和偏小，需要从左边并入下一个元素
                i += 1  # 左指针右移一位
                a += nums[i]  # 把新纳入的元素累加到左段和
                ans += 1  # 合并一次，计数加一
            elif b < a:  # 右段累计和偏小，对称地从右边并入
                j -= 1  # 右指针左移一位
                b += nums[j]  # 把新纳入的元素累加到右段和
                ans += 1  # 合并一次，计数加一
            else:  # 两端累计和相等，这一对已经配对成功，两指针同时内移
                i, j = i + 1, j - 1  # 左右指针同时向中间收缩
                a, b = nums[i], nums[j]  # 左右累计和分别重置为新区间的首、尾元素
        return ans  # 返回最少的合并次数
