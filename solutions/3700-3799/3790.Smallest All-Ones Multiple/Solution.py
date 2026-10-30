# 3790. 最小全 1 倍数 / Smallest All-Ones Multiple
# 核心思路：全 1 数必为奇数，偶数 k 无解；用余数递推 (x*10+1)%k 逐位扩展，首次余数为 0 时的位数即答案。
# 复杂度：时间 O(k)，空间 O(1)。
class Solution:  # 定义 LeetCode 题解类
    def minAllOneMultiple(self, k: int) -> int:  # 返回最小全 1 倍数的位数，不存在则返回 -1
        if k % 2 == 0:  # 全 1 数是奇数，偶数 k 不可能整除它
            return -1  # 无解，直接返回 -1
        x = 1 % k  # 当前全 1 数（1 位）对 k 取模
        ans = 1  # 当前全 1 数的位数
        for _ in range(k):  # 余数最多 k 种，最多再扩展 k 次必然出现循环
            x = (x * 10 + 1) % k  # 末尾追加一个 1 并对 k 取模
            ans += 1  # 位数加一
            if x == 0:  # 余数为 0，说明已能被 k 整除
                return ans  # 返回当前位数即为最小位数
        return -1  # 枚举完毕仍未找到，返回 -1
