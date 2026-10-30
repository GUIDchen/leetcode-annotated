# 题目：1497. 检查数组对是否可以被 k 整除（Check If Array Pairs Are Divisible by k）
# 思路：统计每个余数出现的次数；余数 0 的个数必须为偶数，且每个余数 i 的个数必须等于余数 k-i 的个数。
# 时间复杂度：O(n + k)；空间复杂度：O(k)。
class Solution:  # LeetCode 约定的题解类
    def canArrange(self, arr: List[int], k: int) -> bool:  # 判断能否两两配对使每对之和都能被 k 整除
        cnt = Counter(x % k for x in arr)  # Counter 统计每个余数的出现次数（Python 的 % 结果非负，无需额外修正）
        return cnt[0] % 2 == 0 and all(cnt[i] == cnt[k - i] for i in range(1, k))  # 余数 0 需两两自配故个数为偶数；其余余数 i 必须与 k-i 数量相同
