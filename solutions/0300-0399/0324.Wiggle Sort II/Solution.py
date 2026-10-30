# 题目：324. 摆动排序 II（Wiggle Sort II）
# 思路：先排序，再把「较小一半」从后往前填偶数下标、「较大一半」从后往前填奇数下标，使相邻元素严格交替。
# 时间复杂度：O(n log n)，主要是排序；空间复杂度：O(n)，额外保存排序后的副本。
class Solution:  # LeetCode 约定的题解类
    def wiggleSort(self, nums: List[int]) -> None:  # nums 是待摆动排序的数组，要求原地修改，函数不返回值
        # 题目要求的说明文档串：原地修改，不需要返回值（下面三行属于字符串本身，不能加行尾注释）
        """
        Do not return anything, modify nums in-place instead.
        """
        arr = sorted(nums)  # 先复制一份并排序，后面按大小两半取数
        n = len(arr)  # 有序数组的长度
        i, j = (n - 1) >> 1, n - 1  # i 指向较小一半的末尾，j 指向较大一半的末尾
        for k in range(n):  # 按下标依次填充结果
            if k % 2 == 0:  # 偶数下标放较小的一半
                nums[k] = arr[i]  # 取较小一半的当前最大值
                i -= 1  # 让 i 左移一位
            else:  # 奇数下标放较大的一半
                nums[k] = arr[j]  # 取较大一半的当前最大值
                j -= 1  # 让 j 左移一位
