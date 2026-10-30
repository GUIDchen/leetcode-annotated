# 题目：1664. 生成平衡数组的方案数（Ways to Make a Fair Array）
# 思路：先求原数组奇偶下标和，再用前缀和边遍历边推算删除某元素后左右两段的新奇偶和是否相等。
# 时间复杂度：O(n)，一次求和加一次遍历；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def waysToMakeFair(self, nums: List[int]) -> int:  # nums 是输入数组，返回删除一个元素后数组平衡的方案数
        s1, s2 = sum(nums[::2]), sum(nums[1::2])  # 切片 [::2] 取偶数下标、[1::2] 取奇数下标，分别求和
        ans = t1 = t2 = 0  # ans 方案数；t1/t2 是删除位置左侧的偶/奇下标和前缀
        for i, v in enumerate(nums):  # 枚举每个可能被删除的下标 i 与元素值 v
            ans += i % 2 == 0 and t2 + s1 - t1 - v == t1 + s2 - t2  # i 为偶数：删后左侧不变、右侧奇偶互换，判断两侧新偶数下标和是否相等
            ans += i % 2 == 1 and t2 + s1 - t1 == t1 + s2 - t2 - v  # i 为奇数：同样推算，只是被删的 v 从右侧奇数侧扣除
            t1 += v if i % 2 == 0 else 0  # 把 v 累加进左侧偶数下标和（仅当 i 为偶数）
            t2 += v if i % 2 == 1 else 0  # 把 v 累加进左侧奇数下标和（仅当 i 为奇数）
        return ans  # 返回满足条件的方案数
