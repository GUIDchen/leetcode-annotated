# 题目：1985. 找出数组中的第 K 大整数（Find the Kth Largest Integer in the Array）
# 思路：用堆取出最大的 k 个元素（按 int 值排序，省去手写字符串比较），其中第 k 个就是答案。
# 时间复杂度：O(n log k)；空间复杂度：O(k)，堆中只保留 k 个元素。
class Solution:  # LeetCode 约定的题解类
    def kthLargestNumber(self, nums: List[str], k: int) -> str:  # 返回第 k 大的数字（以字符串形式给出）
        return nlargest(k, nums, key=lambda x: int(x))[k - 1]  # nlargest 返回按 int 值降序的前 k 个元素，取下标 k-1 即第 k 大
