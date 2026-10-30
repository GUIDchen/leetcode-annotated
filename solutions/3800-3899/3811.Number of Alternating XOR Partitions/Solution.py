# 3811. Number of Alternating XOR Partitions | 交替按位异或分割的数目
# 核心思路：前缀异或 + 哈希计数 DP，cnt1/cnt2 以前缀异或为键累计“最后一段为 target1/target2”的方案数；当前前缀的方案数等于 cnt2[pre^target1] 与 cnt1[pre^target2] 之和。
# 复杂度：时间 O(n)；空间 O(n)。
class Solution:  # 定义题解类
    def alternatingXOR(self, nums: List[int], target1: int, target2: int) -> int:  # 返回把 nums 划分成若干段、使各段异或值交替等于 target1、target2 的方案数
        cnt1 = defaultdict(int)  # cnt1：按前缀异或值累计“最后一段是 target1”的方案数
        cnt2 = defaultdict(int)  # cnt2：按前缀异或值累计“最后一段是 target2”的方案数
        cnt2[0] = 1  # 空前缀视为“最后一段以 target2 结尾”的合法初态，保证第一段可以是 target1
        ans = pre = 0  # pre 为当前前缀异或，ans 为当前前缀的划分数
        mod = 10**9 + 7  # 取模常量
        for x in nums:  # 逐个元素推进前缀异或
            pre ^= x  # 把当前元素累加进前缀异或
            a = cnt2[pre ^ target1]  # 上一段是 target2、当前段异或为 target1 的方案数
            b = cnt1[pre ^ target2]  # 上一段是 target1、当前段异或为 target2 的方案数
            ans = (a + b) % mod  # 当前前缀的方案数 = 这两种交替衔接方式之和
            cnt1[pre] = (cnt1[pre] + a) % mod  # 把“以 target1 结尾”的方案累加到前缀异或 pre 上
            cnt2[pre] = (cnt2[pre] + b) % mod  # 把“以 target2 结尾”的方案累加到前缀异或 pre 上
        return ans  # 返回整个数组的划分数
