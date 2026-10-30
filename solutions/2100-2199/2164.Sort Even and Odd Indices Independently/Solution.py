# 题目：2164. 对奇偶下标分别排序（Sort Even and Odd Indices Independently）
# 思路：切片取出偶数下标（含 0）与奇数下标两组元素，前者升序、后者降序，再按原位置写回。
# 时间复杂度：O(n log n)，两次排序；空间复杂度：O(n)，两个切片列表。
class Solution:  # LeetCode 约定的题解类
    def sortEvenOdd(self, nums: List[int]) -> List[int]:  # nums：输入数组；原地重排后返回
        a = sorted(nums[::2])  # nums[::2] 取偶数下标元素，sorted 产生新的升序列表 a
        b = sorted(nums[1::2], reverse=True)  # nums[1::2] 取奇数下标元素，reverse=True 得到降序列表 b
        nums[::2] = a  # 把升序的 a 写回所有偶数下标位置
        nums[1::2] = b  # 把降序的 b 写回所有奇数下标位置
        return nums  # 返回重排后的数组
