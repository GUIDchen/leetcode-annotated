# 题目：644. 子数组最大平均数 II（Maximum Average Subarray II）
# 核心思路：二分答案 v，把每个元素减去 v 后判断是否存在长度 ≥ k 且和 ≥ 0 的子数组；判断时用滚动窗口和 s 与「可裁前缀和的最小值 mi」在 O(n) 内完成。
# 时间复杂度：O(n log((max-min)/eps))；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def findMaxAverage(self, nums: List[int], k: int) -> float:  # nums：输入数组；k：子数组长度的下界
        def check(v: float) -> bool:  # 判断是否存在长度 ≥ k、平均值 ≥ v 的子数组
            s = sum(nums[:k]) - k * v  # 前 k 个元素减 v 后的和，即把「平均值 ≥ v」化为「和 ≥ 0」
            if s >= 0:  # 前 k 个元素就满足条件
                return True  # 存在合法子数组
            t = mi = 0  # t：可随时裁掉的前缀和；mi：t 的最小值
            for i in range(k, len(nums)):  # 窗口右端右移
                s += nums[i] - v  # 窗口和加上新右端
                t += nums[i - k] - v  # 把被移出窗口的那个元素累进前缀和
                mi = min(mi, t)  # 维护前缀和的最小值
                if s >= mi:  # 去掉最小值那段前缀后仍非负，说明存在更长且达标的子数组
                    return True  # 存在合法子数组
            return False  # 不存在平均值 ≥ v 的合法子数组

        eps = 1e-5  # 二分精度
        l, r = min(nums), max(nums)  # 答案区间：数组最小值到最大值
        while r - l >= eps:  # 二分直到区间足够小
            mid = (l + r) / 2  # 取区间中点
            if check(mid):  # 中点可行，答案在右半边
                l = mid  # 抬高下界
            else:  # 中点不可行，答案在左半边
                r = mid  # 压低上界
        return l  # 返回收敛后的下界，即最大平均数
