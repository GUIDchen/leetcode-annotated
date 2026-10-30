# 题目：2599. 使前缀和数组非负（Make the Prefix Sum Non-negative）
# 思路：边扫边累加前缀和，前缀和变负时把见过的负数最小值（小根堆堆顶）挪到数组末尾，相当于从当前前缀和中「减掉」它。
# 时间复杂度：O(n log n)，每个负数最多进出堆一次；空间复杂度：O(n)，最坏把所有负数都存进堆。
class Solution:  # LeetCode 约定的题解类
    def makePrefSumNonNegative(self, nums: List[int]) -> int:  # nums：原数组；返回使所有前缀和都非负所需的最少移动次数
        h = []  # 小根堆存放已遇到的负数，堆顶最小（绝对值最大），优先挪走它最划算
        ans = s = 0  # ans 记移动次数，s 记当前前缀和
        for x in nums:  # 按原顺序遍历，前缀和必须按这个顺序保持非负
            s += x  # 把当前元素计入前缀和
            if x < 0:  # 只有负数才可能拖累前缀和，先攒进堆里
                heappush(h, x)  # 压入小根堆，供后面需要时挪走
            while s < 0:  # 前缀和已经为负，必须挪走一些负数才能修复
                s -= heappop(h)  # 弹出最小负数并把它从当前前缀和中剔除（s -= 负数即加上其绝对值）
                ans += 1  # 移动次数加一
        return ans  # 数组遍历结束，返回最少移动次数
