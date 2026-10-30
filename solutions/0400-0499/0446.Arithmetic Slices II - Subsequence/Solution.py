# 题目：446. 等差数列划分 II - 子序列（Arithmetic Slices II - Subsequence）
# 思路：动态规划，f[i][d] 表示以 nums[i] 结尾、公差为 d 的等差子序列个数（含长度为 2 的）；枚举 j < i，把 f[j][d] 累加进答案，并把这份计数以公差 d 延续到 i。
# 复杂度：时间复杂度 O(n^2)，枚举所有 (j, i) 数对；空间复杂度 O(n^2)，每个下标一张哈希表、最多 O(n) 个公差。
class Solution:  # 题解类：统计等差子序列个数（长度至少 3）
    def numberOfArithmeticSlices(self, nums: List[int]) -> int:  # nums 是输入数组，返回所有等差子序列的数量
        f = [defaultdict(int) for _ in nums]  # f[i][d]：以 nums[i] 结尾、公差为 d 的等差子序列个数（含长度 2 的）
        ans = 0  # 答案：长度至少 3 的等差子序列个数
        for i, x in enumerate(nums):  # 枚举子序列的最后一个元素
            for j, y in enumerate(nums[:i]):  # 枚举它前面的倒数第二个元素
                d = x - y  # 公差
                ans += f[j][d]  # 以 j 结尾、公差 d 的序列接上 x 后长度都 >= 3，全部计入答案
                f[i][d] += f[j][d] + 1  # 以 i 结尾、公差 d 的序列数：沿用转来的计数，再加新形成的长度 2 序列 (j, i)
        return ans  # 返回答案
