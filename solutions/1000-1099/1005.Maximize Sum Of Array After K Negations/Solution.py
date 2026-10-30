# 题目：1005. K 次取反后最大化的数组和（Maximize Sum Of Array After K Negations）
# 核心思路：先尽量把负数取反成正数，剩余次数用偶数次抵消或牺牲最小正数
# 复杂度：时间 O(n + 100)（值域仅 201 个桶）；空间 O(1)
class Solution:  # LeetCode 约定的题解类
    def largestSumAfterKNegations(self, nums: List[int], k: int) -> int:  # nums：整数数组；k：必须恰好执行 k 次「把某个数取反」
        cnt = Counter(nums)  # 计数表：键是数值，值是该数值出现的次数
        for x in range(-100, 0):  # 负数按绝对值从大到小枚举（-100 递增到 -1）
            if cnt[x]:  # 该负数确实存在才处理
                m = min(cnt[x], k)  # 最多取反 min(出现次数, 剩余次数) 个
                cnt[x] -= m  # 这些负数被取反，计数减少
                cnt[-x] += m  # 对应的相反数（正数）计数增加
                k -= m  # 消耗掉用掉的取反次数
                if k == 0:  # 次数用尽就可以提前结束
                    break  # 跳出负数循环
        if k & 1 and cnt[0] == 0:  # 还剩奇数次取反且没有 0 可翻，只能牺牲最小的正数
            for x in range(1, 101):  # 从小到大找最小的正数
                if cnt[x]:  # 找到存在的正数
                    cnt[x] -= 1  # 取反后它不再是正数
                    cnt[-x] += 1  # 它的相反数（负数）计数增加
                    break  # 只需取反一次，跳出循环
        return sum(x * v for x, v in cnt.items())  # 遍历计数表，把「数值 × 出现次数」累加成数组和
