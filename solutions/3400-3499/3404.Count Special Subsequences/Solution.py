# 3404. 统计特殊子序列的数目 / Count Special Subsequences
# 核心思路：条件 nums[p]*nums[r] == nums[q]*nums[s] 等价于约分后 nums[p]/nums[q] == nums[s]/nums[r]；先统计所有合法 (r, s) 的约分键，再按 q 从左到右扫，用表中计数回答 p 的询问并增量删去已失效的 (r, s)
# 复杂度：时间 O(n^2)，空间 O(n^2)
class Solution:  # 定义题目解答类
    def numberOfSubsequences(self, nums: List[int]) -> int:  # 方法入口：统计 p、q、r、s 相邻至少隔 1 个数且 nums[p]*nums[r] == nums[q]*nums[s] 的四元组个数
        n = len(nums)  # 数组长度
        cnt = defaultdict(int)  # 哈希表：键为约分后的 nums[s] / nums[r]，值为该比例出现的次数
        for r in range(4, n - 2):  # 先枚举所有合法的 (r, s) 组合，把它们记录进哈希表
            c = nums[r]  # c 为 nums[r]
            for s in range(r + 2, n):  # 要求 s - r > 1，故 s 从 r + 2 开始
                d = nums[s]  # d 为 nums[s]
                g = gcd(c, d)  # 求最大公约数用于约分
                cnt[(d // g, c // g)] += 1  # 把约分后的 (nums[s], nums[r]) 作为键计数
        ans = 0  # 统计答案
        for q in range(2, n - 4):  # 枚举 q，同时把已经用不到的 (r, s) 组合逐个删除
            b = nums[q]  # b 为 nums[q]
            for p in range(q - 1):  # 枚举 p，范围保证 q - p > 1 的间隔条件
                a = nums[p]  # a 为 nums[p]
                g = gcd(a, b)  # 约分得到 a/b
                ans += cnt[(a // g, b // g)]  # 约分后的 a/b 与表中的 d/c 相等即满足等式，累加计数
            c = nums[q + 2]  # c 为 nums[q + 2]，即本轮要删除的最小 r 对应的值
            for s in range(q + 4, n):  # 枚举与之配对的 s
                d = nums[s]  # d 为 nums[s]
                g = gcd(c, d)  # 求最大公约数用于约分
                cnt[(d // g, c // g)] -= 1  # 该 (r, s) 之后不会再被任何 q 使用，计数减一
        return ans  # 返回答案
