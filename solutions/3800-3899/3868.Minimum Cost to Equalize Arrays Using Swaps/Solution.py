# 3868. 通过交换使数组相等的最小花费 / Minimum Cost to Equalize Arrays Using Swaps
# 核心思路：同数组内交换免费，故只有多重集合有意义；用 nums2 的计数逐个抵消 nums1 的元素，剩下的差异元素必须跨数组交换，每两个差异（一对）花 1 次交换，任一计数为奇数则无解。
# 复杂度：时间复杂度 O(n)，空间复杂度 O(n)（哈希表存储各值的计数）。
class Solution:  # LeetCode 题解类
    def minCost(self, nums1: list[int], nums2: list[int]) -> int:  # 返回使两数组相同的最小花费，无解返回 -1
        cnt2 = Counter(nums2)  # nums2 各值的剩余计数
        cnt1 = Counter()  # nums1 中未被抵消的差异元素计数
        for x in nums1:  # 用 nums2 的计数逐个抵消 nums1
            if cnt2[x]:  # nums2 里还有相同的值可以配对
                cnt2[x] -= 1  # 消费一个，该位置无需交换
            else:  # nums2 里已无相同值
                cnt1[x] += 1  # 记入 nums1 的差异元素
        ans = 0  # 累计最小花费（跨数组交换次数）
        for v in cnt1.values():  # 遍历 nums1 的差异计数
            if v % 2 == 1:  # 该值的差异个数为奇数
                return -1  # 奇数个元素无法两两配对，方案不存在
            ans += v // 2  # 每两个差异元素做一次跨数组交换，花费加 v//2
        for v in cnt2.values():  # 遍历 nums2 的剩余计数（与 cnt1 镜像）
            if v % 2 == 1:  # 该值剩余个数为奇数
                return -1  # 同样无法两两配对，方案不存在
        return ans  # 返回最小花费
