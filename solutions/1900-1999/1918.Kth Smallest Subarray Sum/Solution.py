# 题目：1918. 第 K 小的子数组和（Kth Smallest Subarray Sum）
# 思路：二分答案。对候选和 s 用滑动窗口统计“和 ≤ s 的子数组个数”，元素全为正数所以窗口可单调收缩；再借 bisect_left 在布尔序列上二分出第一个满足计数 ≥ k 的 s。
# 时间复杂度：O(n log S)，S 为数组总和；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def kthSmallestSubarraySum(self, nums: List[int], k: int) -> int:  # nums 中全为正数；返回所有子数组和中第 k 小的那个值
        def f(s):  # 内部判断函数：f(s) 为真表示“和 ≤ s 的子数组个数”已达到 k
            t = j = 0  # t 是窗口 [j, i] 的元素和，j 是窗口左端点
            cnt = 0  # 已统计到的子数组个数
            for i, x in enumerate(nums):  # 枚举右端点 i，x 为 nums[i]
                t += x  # 把当前元素加入窗口
                while t > s:  # 和超过 s 就收缩左端点（元素为正，收缩只会让和变小）
                    t -= nums[j]  # 移出左端点的值
                    j += 1  # 左端点右移
                cnt += i - j + 1  # 以 i 结尾、和 ≤ s 的子数组有 i-j+1 个
            return cnt >= k  # 数量达到 k，说明 s 这个候选值已经足够大

        l, r = min(nums), sum(nums)  # 答案区间：最小元素（最小子数组和）到整个数组的和
        return l + bisect_left(range(l, r + 1), True, key=f)  # 把 f 当作谓词，在 [l, r] 上二分出第一个为 True 的位置，即第 k 小的和
