# 题目：2202. K 次操作后最大化顶端元素（Maximize the Topmost Element After K Moves）
# 思路：k 次操作后顶端只可能是前 k-1 个元素的最大值（删掉再放回），或下标 k 的元素（连续删掉前 k 个）。
# 时间复杂度：O(min(k, n))，只切前 k-1 个元素求最大值；空间复杂度：O(k) 的切片开销，其余为 O(1)。
class Solution:  # LeetCode 约定的题解类
    def maximumTop(self, nums: List[int], k: int) -> int:  # nums：从栈底到栈顶的数组；k：操作次数
        if k == 0:  # 不操作时顶端就是第一个元素
            return nums[0]  # 直接返回 nums[0]
        n = len(nums)  # 元素个数
        if n == 1:  # 只有一个元素时，操作在「弹出」与「放回」之间交替
            if k % 2:  # 奇数次操作会把唯一元素弹掉，栈变空
                return -1  # 栈空时按题意返回 -1
            return nums[0]  # 偶数次操作后元素回到栈顶
        ans = max(nums[: k - 1], default=-1)  # 前 k-1 个元素都能被删掉再放回栈顶，取其最大值；切片为空时用 default=-1 兜底
        if k < n:  # 若 k 小于 n，也可以删掉前 k 个元素，让下标 k 的元素成为栈顶
            ans = max(ans, nums[k])  # 在「删了再放回」和「连删到 nums[k]」两种可能中取较大者
        return ans  # 返回最终可能的最大顶端值
