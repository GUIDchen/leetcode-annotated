# 题目：3351. 好子序列的元素之和（Sum of Good Subsequences）
# 思路：用两个 defaultdict 按值域做 DP，f[v]/g[v] 分别是以值 v 结尾的好子序列元素和与个数，逐个元素从 v-1、v、v+1 并入。
# 时间复杂度：O(n)；空间复杂度：O(max(nums))，字典最多保存值域大小的键。
class Solution:  # LeetCode 约定的题解类
    def sumOfGoodSubsequences(self, nums: List[int]) -> int:  # nums：输入数组
        mod = 10**9 + 7  # 取模常数 1e9 + 7
        f = defaultdict(int)  # f[v]：以值 v 结尾的好子序列元素和，缺省值为 0
        g = defaultdict(int)  # g[v]：以值 v 结尾的好子序列个数，缺省值为 0
        for x in nums:  # 逐个把元素 x 并入 DP
            f[x] += x  # 长度 1 的子序列 [x] 单独成立，元素和加上 x
            g[x] += 1  # 这种只含 x 的子序列个数加一
            f[x] += f[x - 1] + g[x - 1] * x  # 接在所有以 x-1 结尾的序列之后，每个旧序列增加 g[x-1] * x 的和
            g[x] += g[x - 1]  # 对应个数同步累加
            f[x] += f[x + 1] + g[x + 1] * x  # 接在所有以 x+1 结尾的序列之前，增量同样为 g[x+1] * x
            g[x] += g[x + 1]  # 对应个数同步累加
        return sum(f.values()) % mod  # 汇总所有结尾情况；Python 大整数不溢出，中间无需取模，最后统一取模
