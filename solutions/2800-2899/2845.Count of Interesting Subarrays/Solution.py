# 题目：2845. 统计趣味子数组的数目（Count of Interesting Subarrays）
# 思路：把「模 modulo 等于 k」的元素映射成 1、其余映射成 0，趣味条件等价于子数组和在模 modulo 下等于 k；用前缀和 + 计数器统计。
# 时间复杂度：O(n)，一遍扫描；空间复杂度：O(min(n, modulo))，计数器最多保存 modulo 种余数。
class Solution:  # LeetCode 约定的题解类
    def countInterestingSubarrays(self, nums: List[int], modulo: int, k: int) -> int:  # nums：原数组；modulo：取模值；k：目标余数
        arr = [int(x % modulo == k) for x in nums]  # 0/1 数组：元素模 modulo 等于 k 记 1，否则记 0
        cnt = Counter()  # 计数器：记录前缀和模 modulo 各个余数出现的次数
        cnt[0] = 1  # 空前缀的余数视为 0，先记一次
        ans = s = 0  # ans 统计答案，s 维护当前前缀和
        for x in arr:  # 从左到右扫描 0/1 数组
            s += x  # 更新前缀和
            ans += cnt[(s - k) % modulo]  # 之前余数为 (s - k) mod modulo 的前缀，其后的部分都构成趣味子数组
            cnt[s % modulo] += 1  # 当前前缀和的余数也计入计数器
        return ans  # 返回满足条件的子数组总数
