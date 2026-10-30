# 题目：974. 和可被 K 整除的子数组（Subarray Sums Divisible by K）
# 思路：前缀和模 k 同余的两个位置之间，子数组和必被 k 整除，用计数器统计同余前缀和出现次数。
# 时间复杂度：O(n)，一次遍历；空间复杂度：O(k)，计数器最多存 k 种余数。
class Solution:  # LeetCode 约定的题解类
    def subarraysDivByK(self, nums: List[int], k: int) -> int:  # nums：输入数组；k：除数，返回和能被 k 整除的连续子数组个数
        cnt = Counter({0: 1})  # cnt 记录「前缀和模 k 的余数 → 出现次数」，余数 0 先记 1 次（空前缀）
        ans = s = 0  # ans 计数答案，s 保存当前前缀和模 k 的余数
        for x in nums:  # 逐个元素累计前缀和
            s = (s + x) % k  # Python 的 % 对负数也返回非负余数，所以直接取模即可
            ans += cnt[s]  # 此前出现过 cnt[s] 次相同余数，就能组成 cnt[s] 个合法子数组
            cnt[s] += 1  # 当前余数出现次数加一
        return ans  # 返回统计到的子数组总数
