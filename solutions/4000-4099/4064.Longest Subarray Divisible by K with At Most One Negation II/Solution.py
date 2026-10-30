# 4064. 至多一次取反能被 K 整除的最长子数组 II  Longest Subarray Divisible by K with At Most One Negation II
# 核心思路：先算出前缀和余数，再按首次出现位置给余数排序；用双指针把已就绪的起点批量并入 best 数组，线性时间得到答案。
# 复杂度：时间 O(n + k log k)，空间 O(n + k)。

class Solution:
    def longestSubarray(self, nums: list[int], k: int) -> int:  # 返回至多取反一个元素后，和能被 k 整除的最长子数组长度
        n = len(nums)  # 数组长度
        p = [0] * (n + 1)  # p[i] 表示前 i 个元素之和模 k
        for i in range(n):  # 递推计算每个前缀和余数
            p[i + 1] = (p[i] + nums[i]) % k  # 由上一个前缀和余数递推

        first = [-1] * k  # first[q] 记录余数 q 首次出现的下标，-1 表示未出现
        for i in range(n + 1):  # 遍历全部 n+1 个前缀位置
            if first[p[i]] == -1:  # 余数 p[i] 尚未被记录
                first[p[i]] = i  # 记下它的最早下标

        order = [q for q in range(k) if first[q] != -1]  # 收集所有真正出现过的余数
        order.sort(key=lambda q: first[q])  # 按首次出现下标升序排序

        pos = [0] * k  # pos[a] 记录余数 a 对应的 order 处理进度
        best = [x if x != -1 else n + 1 for x in first]  # best[t] 记录能凑出余数 t 的最早起点，n+1 表示不可用

        ans = 0  # 记录最长子数组长度
        for i, x in enumerate(nums):  # 枚举右端点 i
            a = x % k  # 当前元素对 k 取余（Python 结果非负）
            while pos[a] < len(order) and first[order[pos[a]]] <= i:  # 把所有已可用的起点并入 best
                q = order[pos[a]]  # 取出当前起点余数
                pos[a] += 1  # 处理进度后移
                t = (q + 2 * a) % k  # 取反 x 后需要匹配的新余数
                best[t] = min(best[t], first[q])  # 用更早的起点更新 best

            s = p[i + 1]  # 以 i 结尾的前缀和余数
            if best[s] != n + 1:  # 存在可匹配的起点
                ans = max(ans, i + 1 - best[s])  # 用区间长度更新答案

        return ans  # 返回最终最大长度
