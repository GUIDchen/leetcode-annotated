# 题目：330. 按要求补齐数组（Patching Array）
# 思路：贪心维护已能覆盖的区间 [1, x-1]；若 nums[i] <= x 就并入使范围扩到 x+nums[i]，否则必须补一个 x 让范围翻倍。
# 时间复杂度：O(n + log n)，主循环中补数次数是 O(log n) 级；空间复杂度：O(1)，只用常数个变量。
class Solution:    # LeetCode 约定的题解类
    def minPatches(self, nums: List[int], n: int) -> int:    # nums：已排序的正整数数组；n：要覆盖的目标上界，返回最少需要补充的个数
        x = 1    # x 表示「当前已经能凑出 [1, x-1] 内的所有和」
        ans = i = 0    # ans 记录补数个数，i 是指向 nums 的指针
        while x <= n:    # 只要覆盖范围还没到 n 就继续
            if i < len(nums) and nums[i] <= x:    # 下一个数落在可覆盖范围内，直接并入不会产生缺口
                x += nums[i]    # 覆盖范围扩大成 [1, x+nums[i]-1]
                i += 1    # 用掉这个已有的数，指针后移
            else:    # 否则说明 [x, nums[i]) 之间存在缺口，必须先补数
                ans += 1    # 补一个数，答案加一
                x <<= 1    # 补 x 本身最优：覆盖范围直接翻倍成 [1, 2x-1]
        return ans    # 返回最少补充个数
