# 3830. 移除至多一个元素后的最长交替子数组 / Longest Alternating Subarray After Removing At Most One Element（困难）
# 核心思路：先正向求出 l1/l2（以 i 结尾且最后一步上升/下降的最长交替长度），再反向求出 r1/r2（以 i 开头且第一步上升/下降），最后枚举删除位置 i 把左右两段拼接。
# 复杂度：四趟线性扫描，时间 O(n)，空间 O(n)。
class Solution:  # 求删除至多一个元素后最长的交替（锯齿形）子数组长度
    def longestAlternating(self, nums: List[int]) -> int:  # 返回删除至多一个元素后最长交替子数组的长度（相邻元素大小关系严格交替）
        n = len(nums)  # 数组长度
        l1 = [1] * n  # 以 i 结尾、最后一步上升的最长交替长度，默认 1
        l2 = [1] * n  # 以 i 结尾、最后一步下降的最长交替长度，默认 1
        r1 = [1] * n  # 以 i 开头、第一步上升的最长交替长度，默认 1
        r2 = [1] * n  # 以 i 开头、第一步下降的最长交替长度，默认 1
        ans = 0  # 答案初始为 0，后续两轮扫描会不断更新
        for i in range(1, n):  # 正向扫描：求出以每个位置结尾的最长交替长度
            if nums[i - 1] < nums[i]:  # 最后一步上升
                l1[i] = l2[i - 1] + 1  # 接在以 i-1 结尾、最后一步下降的序列后
            elif nums[i - 1] > nums[i]:  # 最后一步下降
                l2[i] = l1[i - 1] + 1  # 接在以 i-1 结尾、最后一步上升的序列后
            ans = max(ans, l1[i], l2[i])  # 用“不删除元素”的答案更新最优值
        for i in range(n - 2, -1, -1):  # 反向扫描：求出以每个位置开头的最长交替长度
            if nums[i + 1] > nums[i]:  # 第一步上升（i → i+1 递增）
                r1[i] = r2[i + 1] + 1  # 之后必须紧跟下降步，故接 r2[i+1]
            elif nums[i + 1] < nums[i]:  # 第一步下降（i → i+1 递减）
                r2[i] = r1[i + 1] + 1  # 之后必须紧跟上升步，故接 r1[i+1]
        for i in range(1, n - 1):  # 枚举被删除的位置 i（首尾不删，留作哨兵）
            if nums[i - 1] < nums[i + 1]:  # 删除 i 后 nums[i-1] 与 nums[i+1] 是上升关系
                ans = max(ans, l2[i - 1] + r2[i + 1])  # 左侧以下降结尾、右侧以下降开头，拼接后仍严格交替
            elif nums[i - 1] > nums[i + 1]:  # 删除 i 后衔接处是下降关系
                ans = max(ans, l1[i - 1] + r1[i + 1])  # 左侧以上升结尾、右侧以上升开头
        return ans  # 返回最长交替子数组长度
