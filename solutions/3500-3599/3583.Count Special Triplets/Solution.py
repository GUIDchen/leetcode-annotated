# 3583. 统计特殊三元组（Count Special Triplets）
# 核心思路：先统计全数组频次作为右侧表，再枚举中间元素 x，用左右两张频次表统计 2x 的个数并累乘取模。
# 复杂度：时间复杂度 O(n)，空间复杂度 O(n)，其中 n 为数组长度。
class Solution:  # 定义题解类
    def specialTriplets(self, nums: List[int]) -> int:  # 统计满足条件的三元组个数
        left = Counter()  # 左、右两侧的频次表
        right = Counter(nums)  # 初始化时整个数组都算在右侧
        ans = 0  # 记录答案
        mod = 10**9 + 7  # 取模常量
        for x in nums:  # 枚举作为中间元素的值 x
            right[x] -= 1  # 当前元素从右侧移出
            ans = (ans + left[x * 2] * right[x * 2] % mod) % mod  # 左侧 2x 个数乘以右侧 2x 个数，累加后取模
            left[x] += 1  # 当前元素加入左侧
        return ans  # 返回答案
