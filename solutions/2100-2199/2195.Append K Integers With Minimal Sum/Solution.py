# 题目：2195. 向数组中追加 K 个整数（Append K Integers With Minimal Sum）
# 思路：在数组中补两个哨兵（0 与 2*10^9）后排序，逐段考察相邻数之间的空缺，优先取每段最小的数，用等差数列公式累加。
# 时间复杂度：O(n log n)，排序为主；空间复杂度：O(1)，只在原列表上扩展两个元素。
class Solution:  # LeetCode 约定的题解类
    def minimalKSum(self, nums: List[int], k: int) -> int:  # nums：已有数组；k：还要追加的个数
        nums.extend([0, 2 * 10**9])  # 左哨兵 0 与右哨兵 2*10^9，保证首尾都有足够多的空缺
        nums.sort()  # 排序后相邻元素的差才是连续的空缺区间
        ans = 0  # 已追加数字的总和
        for a, b in pairwise(nums):  # pairwise 依次给出相邻的一对数 (a, b)
            m = max(0, min(k, b - a - 1))  # 本段 (a, b) 之间可取的个数，且不超过剩余需要的 k
            ans += (a + 1 + a + m) * m // 2  # 取本段最小的 m 个数求和：首项 a+1，末项 a+m
            k -= m  # 扣掉已追加的个数
        return ans  # 返回最小总和；k 用完时 m 恒为 0，多余区间不再影响结果
