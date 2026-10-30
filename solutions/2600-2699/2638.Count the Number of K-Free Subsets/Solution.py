# 题目：2638. 统计 K-Free 子集的总数（Count the Number of K-Free Subsets）
# 思路：按 x % k 分组，不同组之间差不可能为 k，因此可以独立计数后相乘；组内元素升序后做线性 DP：相邻两数差恰为 k 时 f[i] = f[i-1] + f[i-2]，否则 f[i] = 2 * f[i-1]。
# 时间复杂度：O(n log n)，排序为主；空间复杂度：O(n)，字典与每组 DP 数组。
class Solution:  # LeetCode 约定的题解类
    def countTheNumOfKFreeSubsets(self, nums: List[int], k: int) -> int:  # nums 输入数组，k 是不允许同时出现的差值；返回不含差为 k 数对的子集总数
        nums.sort()  # 排序后模 k 同余的元素会按大小依次相邻
        g = defaultdict(list)  # 余数 -> 该余数下的所有元素（升序）
        for x in nums:  # 逐个元素按余数分组
            g[x % k].append(x)  # 模 k 不同的两个数差一定不是 k，可分别独立统计
        ans = 1  # 各组方案数的乘积
        for arr in g.values():  # 逐组做线性 DP
            m = len(arr)  # 该组元素个数
            f = [0] * (m + 1)  # f[i] 表示前 i 个元素的合法子集数
            f[0] = 1  # 空子集算一种方案
            f[1] = 2  # 只有一个元素：选或不选，共 2 种
            for i in range(2, m + 1):  # 从第 2 个元素开始递推
                if arr[i - 1] - arr[i - 2] == k:  # 相邻两数差恰为 k，这两个元素不能同时选
                    f[i] = f[i - 1] + f[i - 2]  # 不选第 i 个 + 选第 i 个且第 i-1 个必不选
                else:  # 相邻两数差不为 k，二者互不冲突
                    f[i] = f[i - 1] * 2  # 第 i 个元素可自由选或不选
            ans *= f[m]  # 乘上该组的方案数
        return ans  # 所有组方案数之积即答案
