# 题目：2910. 合法分组的最少组数（Minimum Number of Groups to Create a Valid Assignment）
# 核心思路：每组大小为 k 或 k+1，k 的上界是「最小频次」，从大到小枚举 k，第一个能让所有频次都合法拆分的 k 就对应最少组数。
# 时间复杂度：O(n * 最小频次 / k) 量级（枚举 k 再枚举频次）；空间复杂度：O(n)，计数表。
class Solution:  # LeetCode 约定的题解类
    def minGroupsForValidAssignment(self, nums: List[int]) -> int:  # nums 是输入数组，返回合法分组的最少组数
        cnt = Counter(nums)  # 统计每个数值出现的次数
        for k in range(min(cnt.values()), 0, -1):  # 组大小 k 的上界是「最小频次」，从大到小枚举，首次可行即最优
            ans = 0  # 当前 k 下的总组数；保持 0 表示该 k 不可行
            for v in cnt.values():  # 逐个检查每种数值的频次 v
                if v // k < v % k:  # 商小于余数意味着剩下的元素凑不满一组 k，此 k 不可行
                    ans = 0  # 标记不可行
                    break  # 换下一个 k
                ans += (v + k) // (k + 1)  # 频次 v 最少需要 ceil(v/(k+1)) 组，(v+k)//(k+1) 正是它的整数写法
            if ans:  # 非 0 说明所有频次都能合法拆分
                return ans  # k 从大到小枚举，第一次可行就是最少组数
