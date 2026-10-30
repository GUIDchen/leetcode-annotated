# 题目：1708. 长度为 K 的最大子数组（Largest Subarray Length K）
# 思路：元素互不相同，长度相同的子数组字典序只由首元素决定；首元素只能取前 n-k+1 个位置，找出其中最大值下标，再从该下标连续截取 k 个元素。
# 时间复杂度：O(n)，切片与求最大值各一次线性扫描；空间复杂度：O(k)，保存返回的子数组。
class Solution:  # LeetCode 约定的题解类
    def largestSubarray(self, nums: List[int], k: int) -> List[int]:  # nums：元素互不相同的输入数组；k：子数组长度
        i = nums.index(max(nums[: len(nums) - k + 1]))  # 首元素只能落在前 n-k+1 个位置内，先取这一段的最大值，再定位它的下标
        return nums[i : i + k]  # 从该下标开始连续截取 k 个元素，即为字典序最大的子数组
