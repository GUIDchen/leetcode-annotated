# 题目：3780. 能被 3 整除的三元组最大和（Maximum Sum of Three Numbers Divisible by Three）
# 核心思路：先排序，再按模 3 的余数分成三个桶；枚举前两个数的余数 a、b，第三个余数由 (a+b+c)%3==0 唯一确定，取三个桶中的最大值求和，凑不出时返回 0。
# 复杂度：时间 O(n log n)（排序主导，枚举只有 3×3 种组合）；空间 O(n)，用于三个余数桶。
class Solution:  # LeetCode 约定的题解类
    def maximumSum(self, nums: List[int]) -> int:  # 从 nums 中选恰好三个数使其和能被 3 整除，返回最大可能的和
        nums.sort()  # 升序排序，每个余数桶的末尾即该余数下的最大值
        g = [[] for _ in range(3)]  # 三个桶，分别收集模 3 余 0、1、2 的数
        for x in nums:  # 按余数把每个数归类
            g[x % 3].append(x)  # 把 x 追加到余数为 x % 3 的桶里
        ans = 0  # 答案初值 0：凑不出三元组时返回 0
        for a in range(3):  # 枚举第一个数的余数 a
            if g[a]:  # 第一个桶非空的判断
                x = g[a].pop()  # 取出 a 类里最大的数 x
                for b in range(3):  # 枚举第二个数的余数 b
                    if g[b]:  # 第二个桶非空的判断
                        y = g[b].pop()  # 取出 b 类里当前最大的数 y
                        c = (3 - (a + b) % 3) % 3  # 由 (a + b + c) % 3 == 0 反解出第三个余数 c
                        if g[c]:  # 第三个桶非空的判断
                            z = g[c][-1]  # 取 c 类最大值 z（只读，不弹出）
                            ans = max(ans, x + y + z)  # 三者之和更新答案
                        g[b].append(y)  # 回滚：把 y 放回 b 桶
                g[a].append(x)  # 回滚：把 x 放回 a 桶
        return ans  # 返回最大和
