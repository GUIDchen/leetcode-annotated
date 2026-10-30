# 3878. 统计好子数组（Count Good Subarrays）
# 核心思路：用单调栈分别求出每个位置 i 左侧第一个「按位包含 nums[i] 的值」的下标 l[i] 和右侧第一个满足条件的位置 r[i]，则以 i 为「唯一代表」的好子数组数量为 (i - l[i]) * (r[i] - i)，累加即为答案。
# 复杂度：时间复杂度 O(n)，空间复杂度 O(n)。
class Solution:  # 题解类
    def countGoodSubarrays(self, nums: list[int]) -> int:  # 返回所有好子数组的数量
        n = len(nums)  # 数组长度
        l = [-1] * n  # l[i]：左侧第一个满足条件的位置，不存在时为 -1
        stk = []  # 单调栈，保存下标
        for i, x in enumerate(nums):  # 从左往右扫描
            while stk and nums[stk[-1]] < x and (nums[stk[-1]] | x) == x:  # 栈顶更小且其二进制位被 x 完全包含时弹出
                stk.pop()  # 栈顶被 x 支配，不可能再作为边界
            l[i] = stk[-1] if stk else -1  # 栈顶即左侧最近的支配点
            stk.append(i)  # 当前下标入栈
        r = [n] * n  # r[i]：右侧第一个满足条件的位置，不存在时为 n
        stk = []  # 清空栈，复用为从右往左的单调栈
        for i in range(n - 1, -1, -1):  # 从右往左扫描
            while stk and (nums[stk[-1]] | nums[i]) == nums[i]:  # 栈顶的二进制位被 nums[i] 完全包含时弹出
                stk.pop()  # 栈顶被 nums[i] 支配，不可能再作为边界
            r[i] = stk[-1] if stk else n  # 栈顶即右侧最近的支配点
            stk.append(i)  # 当前下标入栈
        return sum((i - l[i]) * (r[i] - i) for i in range(n))  # 左端点 i-l[i] 种 × 右端点 r[i]-i 种，逐位累加
