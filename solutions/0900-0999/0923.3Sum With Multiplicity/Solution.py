# 题目：923. 三数之和的多种可能（3Sum With Multiplicity）
# 思路：用 Counter 统计全量频次；枚举中间下标 j 时先扣掉自身，使 cnt 只代表后缀，再枚举 i<j 查补数 c 的存在个数。
# 时间复杂度：O(n^2)，双重枚举；空间复杂度：O(V)，V 为不同取值的个数。
class Solution:  # LeetCode 约定的题解类
    def threeSumMulti(self, arr: List[int], target: int) -> int:  # arr：原数组；target：三数之和的目标值
        mod = 10**9 + 7  # 结果需要对 1e9+7 取模
        cnt = Counter(arr)  # 用计数器统计整个数组里每个值出现的次数
        ans = 0  # 累计满足条件的下标三元组个数
        for j, b in enumerate(arr):  # 枚举中间下标 j 及其值 b
            cnt[b] -= 1  # 先扣掉 b 自身，使 cnt 只代表下标 > j 的后缀
            for a in arr[:j]:  # 枚举 i < j 位置上的数 a（切片只取前缀，保证下标有序）
                c = target - a - b  # 由 a+b+c=target 反解第三个数 c
                ans = (ans + cnt[c]) % mod  # 后缀中所有等于 c 的个数都能形成合法三元组（缺失键由 Counter 返回 0）
        return ans  # 返回取模后的方案总数
