# 题目：2216. 美化数组的最少删除数（Minimum Deletions to Make Array Beautiful）
# 思路：贪心。用双指针方式模拟配对：相邻相等就删掉左边一个（只走一步），相邻不等就保留这对（走两步）。
# 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minDeletion(self, nums: List[int]) -> int:  # nums 是输入数组，返回值是最少删除次数
        n = len(nums)  # 原数组长度
        i = ans = 0  # i 是当前待配对下标，ans 是已删除个数
        while i < n - 1:  # 还需要至少两个元素才能组成一对
            if nums[i] == nums[i + 1]:  # 相邻相等，这一对会违反规则
                ans += 1  # 删除左边那个，计数加一
                i += 1  # 只前进一步，让下一对继续比较（靠下标推移模拟删除）
            else:  # 相邻不等，这一对可以保留
                i += 2  # 跳过这两个元素，处理下一对
        ans += (n - ans) % 2  # 剩余长度为奇数就再删一个，使总长度为偶数
        return ans  # 返回最少删除次数
