# 题目：2835. 使子序列的和等于目标的最少操作次数（Minimum Operations to Form Subsequence With Target Sum）
# 思路：先用总和判断是否可行，再把每个数按二进制拆成 2 的幂块并统计每层的块数；然后自低向高满足 target 的每个 1 位，该层没有块时就从更高层把一个块逐层劈半下来，每劈一次计一次操作，累计次数即答案。
# 时间复杂度：O(32n)，每个元素拆 32 位，之后按位推进只做常数级扫描；空间复杂度：O(1)，只用长度 32 的计数器数组。
class Solution:  # LeetCode 约定的题解类
    def minOperations(self, nums: List[int], target: int) -> int:  # nums：可操作的正整数数组；target：要凑出的目标和
        s = sum(nums)  # 先求出所有元素的总和
        if s < target:  # 总和小于目标值
            return -1  # 无论如何都凑不出 target，直接返回 -1
        cnt = [0] * 32  # cnt[i] 表示当前可用的「2 的 i 次幂」块的数量
        for x in nums:  # 遍历每个数
            for i in range(32):  # 逐位检查它的二进制表示
                if x >> i & 1:  # 该位为 1
                    cnt[i] += 1  # 说明它能贡献一块大小为 2^i 的块
        i = j = 0  # i：当前要满足的 target 位下标；j：当前可用的最低位块所在层
        ans = 0  # 累计的操作次数
        while 1:  # 逐位满足 target
            while i < 32 and (target >> i & 1) == 0:  # 跳过 target 中为 0 的位
                i += 1
            if i == 32:  # 32 位全部处理完，target 已凑齐
                break  # 跳出循环，返回答案
            while j < i:  # 把低于第 i 位的小块两两合并成更大的块
                cnt[j + 1] += cnt[j] // 2  # 两块 2^j 合成一块 2^(j+1)，向上进位
                cnt[j] %= 2  # 进位后本层只剩 0 或 1 块
                j += 1
            while cnt[j] == 0:  # 当前层没有块，需要从更高层劈下来
                cnt[j] = 1  # 劈一次会在此层留下一个 2^j 的块
                j += 1  # 继续往更高层找可劈的块
            ans += j - i  # 把 2^j 一路劈到 2^i 需要 j-i 次操作
            cnt[j] -= 1  # 用掉这一块
            j = i  # 从第 i 层继续往后推进
            i += 1
        return ans  # 返回最少操作次数
