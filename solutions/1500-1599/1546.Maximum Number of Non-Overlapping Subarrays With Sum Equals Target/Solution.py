# 题目：1546. 和为目标值且不重叠的非空子数组的最大数目（Maximum Number of Non-Overlapping Subarrays With Sum Equals Target）
# 思路：贪心，从当前起点向后累加前缀和，一旦发现 s - target 出现过就立即截下一段并跳出，越早截断留给后面的空间越大。
# 时间复杂度：O(n)，每个下标只被内层循环推进一次；空间复杂度：O(n)，哈希集合存前缀和。
class Solution:
    def maxNonOverlapping(self, nums: List[int], target: int) -> int:  # nums：输入数组；target：目标子数组和
        ans = 0  # ans 记录能截出的子数组个数
        i, n = 0, len(nums)  # i 是当前尚未使用的起始下标，n 是数组长度
        while i < n:  # 只要还有元素可以开始新的一段
            s = 0  # s 是从 i 开始这一段内的局部前缀和
            vis = {0}  # 本段出现过的前缀和集合，0 表示空前缀
            while i < n:  # 从 i 向后累加，寻找和为 target 的一段
                s += nums[i]  # 累加当前元素
                if s - target in vis:  # s - target 出现过，说明中间那一段的和正好等于 target
                    ans += 1  # 找到一个合法子数组，答案加 1
                    break  # 立刻结束本段，保证与后面的子数组互不重叠
                i += 1  # 这一段还没凑出 target，继续右移
                vis.add(s)  # 记下这个前缀和，供后面的位置判断
            i += 1  # 本段结束，从下一个位置开始新的一段
        return ans  # 返回最多能截出的子数组数目
