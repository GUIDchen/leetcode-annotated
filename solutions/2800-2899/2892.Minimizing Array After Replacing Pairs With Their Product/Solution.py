# 题目：2892. 将相邻元素相乘后得到最小化数组（Minimizing Array After Replacing Pairs With Their Product）
# 思路：贪心——从左往右尽量把相邻元素乘进当前段，乘积仍 ≤ k 就继续合并，否则以当前元素另起一段；一旦出现 0，全部元素可并为 1 段。
# 时间复杂度：O(n)，只需一次遍历；空间复杂度：O(1)，只使用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minArrayLength(self, nums: List[int], k: int) -> int:  # nums：输入数组；k：每一段乘积允许的上限
        ans, y = 1, nums[0]  # ans：当前段数（首元素单独成段，至少 1 段）；y：当前段已合并的乘积
        for x in nums[1:]:  # 从第二个元素开始逐个扫描（切片只读，不改动原数组）
            if x == 0:  # 出现 0 时，无论怎么合并乘积都是 0 ≤ k，可全部并为一段
                return 1  # 最短长度必然是 1
            if x * y <= k:  # 把 x 乘进当前段后仍不超过 k，说明可以继续合并
                y *= x  # 更新当前段乘积
            else:  # 再乘就超过 k，当前段无法再吞并 x
                y = x  # 让 x 作为新一段的起点乘积
                ans += 1  # 段数加一
        return ans  # 遍历结束，ans 就是最少的段数
