# 题目：1248. 统计「优美子数组」（Count Number of Nice Subarrays）
# 思路：前缀和 + 计数 —— 把元素换成 0/1（奇数记 1），用 Counter 统计每种奇数个数出现的次数，枚举右端点时累加 cnt[t-k]。
# 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(n)，即计数表的规模。
class Solution:  # LeetCode 约定的题解类
    def numberOfSubarrays(self, nums: List[int], k: int) -> int:  # 统计恰好包含 k 个奇数的连续子数组个数
        cnt = Counter({0: 1})  # 前缀奇数个数 → 出现次数；0 个奇数的空前缀先记一次
        ans = t = 0  # ans：答案；t：当前前缀中的奇数个数
        for v in nums:  # 从左往右扫描
            t += v & 1  # 奇数最低位是 1，用它把奇数个数累加进 t
            ans += cnt[t - k]  # 与「奇数个数为 t-k」的所有前缀都能配对成合法子数组
            cnt[t] += 1  # 把当前前缀的奇数个数计入计数表
        return ans  # 返回子数组总数
