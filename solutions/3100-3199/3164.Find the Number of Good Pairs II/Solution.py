# 题目：3164. 优质数对的总数 II（Find the Number of Good Pairs II）
# 思路：枚举数对会 O(n·m) 超时，改为「枚举倍数」：先把 nums1 中 k 的倍数除以 k 计数，再对 nums2 的每个取值 x 枚举其倍数累加配对数。
# 时间复杂度：O(n + m + mx·log mx)，mx 为 x/k 的最大值；空间复杂度：O(n + m)，两个 Counter 的规模。
class Solution:  # LeetCode 约定的题解类
    def numberOfPairs(self, nums1: List[int], nums2: List[int], k: int) -> int:  # 返回优质数对个数，Python 整数不会溢出，无需关心类型宽度
        cnt1 = Counter(x // k for x in nums1 if x % k == 0)  # 只保留 k 的倍数，并归一化成 x // k 后计数，便于后面按倍数查找
        if not cnt1:  # 没有任何可用元素时，答案必然是 0
            return 0  # 提前返回，省掉后面的枚举
        cnt2 = Counter(nums2)  # 统计 nums2 中每个取值的出现次数
        ans = 0  # 答案累加器
        mx = max(cnt1)  # cnt1 中的最大值，作为倍数枚举的上界
        for x, v in cnt2.items():  # 按 nums2 的不同取值 x 分组，同值元素配对情况相同
            s = sum(cnt1[y] for y in range(x, mx + 1, x))  # range(x, mx + 1, x) 枚举 x 的所有倍数，累加它们在 cnt1 中的次数
            ans += s * v  # 再乘以取值 x 的出现次数，整批计入答案
        return ans  # 返回优质数对总数
