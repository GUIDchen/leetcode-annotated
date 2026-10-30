# 题目：3097. 或值至少为 K 的最短子数组 II（Shortest Subarray With OR at Least K II）
# 思路：滑动窗口配合 32 位计数数组，右端扩张、条件满足时收缩左端，用每一位的出现次数动态维护窗口的按位或值。
# 时间复杂度：O(32n)，左右指针各最多移动 n 次且每次移动都要检查 32 位；空间复杂度：O(32)，即常数级计数数组。
class Solution:  # LeetCode 约定的题解类
    def minimumSubarrayLength(self, nums: List[int], k: int) -> int:  # nums：输入数组；k：要求的按位或下界；返回满足条件的最短子数组长度
        n = len(nums)  # 数组长度，用于初始化哨兵值和判断答案是否存在
        cnt = [0] * 32  # cnt[h] 记录第 h 个二进制位在当前窗口内出现的次数，全部初始化为 0
        ans = n + 1  # 答案先取比任何合法长度都大的哨兵值，方便后面取 min
        s = i = 0  # s 是窗口内元素的按位或，i 是窗口左端点
        for j, x in enumerate(nums):  # 枚举窗口右端点 j 以及对应元素 x
            s |= x  # 右端元素并入窗口，直接按位或进 s
            for h in range(32):  # 逐位统计新元素 x 的贡献
                if x >> h & 1:  # 取 x 的第 h 位，判断是否为 1
                    cnt[h] += 1  # 该位在窗口内出现次数加一
            while s >= k and i <= j:  # 窗口或值已达标且窗口非空，就收缩左端尝试更短
                ans = min(ans, j - i + 1)  # 当前窗口长度合法，更新最短长度
                y = nums[i]  # 取出即将移出窗口的左端元素
                for h in range(32):  # 逐位撤销 y 对窗口的贡献
                    if y >> h & 1:  # 只有 y 的第 h 位为 1 才需要撤销
                        cnt[h] -= 1  # 该位在窗口内出现次数减一
                        if cnt[h] == 0:  # 该位归零说明窗口或值的这一位消失
                            s ^= 1 << h  # 用异或把 s 的第 h 位清 0
                i += 1  # 左端右移一位，窗口变短后继续判断
        return -1 if ans > n else ans  # 哨兵未被更新说明无解返回 -1，否则返回最短长度
