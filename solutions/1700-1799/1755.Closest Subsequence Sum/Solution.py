# 题目：1755. 最接近目标值的子序列和（Closest Subsequence Sum）
# 思路：折半枚举——左右两半各自递归枚举全部子集和并用 set 去重，再排序右半，对每个左半和用二分查找最接近 goal - l 的值。
# 时间复杂度：O(2^(n/2) · log 2^(n/2))，枚举子集 O(2^(n/2))、每个左半和一次二分；空间复杂度：O(2^(n/2))，存两半子集和。
class Solution:  # LeetCode 约定的题解类
    def minAbsDifference(self, nums: List[int], goal: int) -> int:  # nums 是输入数组，goal 是目标值
        n = len(nums)  # 数组长度
        left = set()  # 左半子集和，用 set 自动去重，减少后续枚举量
        right = set()  # 右半子集和，同样用 set 去重

        self.getSubSeqSum(0, 0, nums[: n // 2], left)  # 递归枚举前一半 nums[0 : n//2] 的子集和
        self.getSubSeqSum(0, 0, nums[n // 2 :], right)  # 递归枚举后一半 nums[n//2 : n] 的子集和

        result = inf  # 记录目前最小的 |子集和 - goal|，inf 是正无穷
        right = sorted(right)  # 右半子集和排序，才能用二分查找
        rl = len(right)  # 右半子集和的个数，后面判断下标是否越界要用

        for l in left:  # 枚举左半的每一个子集和 l
            remaining = goal - l  # 右半需要凑出的理想值：加上 l 后正好等于 goal
            idx = bisect_left(right, remaining)  # 二分找到第一个 >= remaining 的位置

            if idx < rl:  # 存在 >= remaining 的最小右半和，用它更新答案
                result = min(result, abs(remaining - right[idx]))  # 计算偏差并取较小值

            if idx > 0:  # 同时检查 idx 左边、即 < remaining 的最大右半和，它也可能更接近
                result = min(result, abs(remaining - right[idx - 1]))  # 计算偏差并取较小值

        return result  # 返回最小绝对差

    def getSubSeqSum(self, i: int, curr: int, arr: List[int], result: Set[int]):  # 从下标 i 递归枚举 arr 的子集和，curr 是当前和
        if i == len(arr):  # arr 中所有元素都决定完了，得到一个完整子集和
            result.add(curr)  # 把当前子集和收进集合（set 自动去重）
            return  # 递归出口

        self.getSubSeqSum(i + 1, curr, arr, result)  # 分支一：不选 arr[i]，和保持 curr
        self.getSubSeqSum(i + 1, curr + arr[i], arr, result)  # 分支二：选 arr[i]，和加上它
