# 题目：2499. 让数组不相等的最小总代价（Minimum Total Cost to Make Arrays Unequal）
# 思路：冲突位置（a==b）先用代价 i 收进交换池；若某值在冲突中超过半数，再从非冲突位置里挑代价最小、且两端都不等于该值的位置稀释，仍不够则无解。
# 时间复杂度：O(n)，两遍线性扫描；空间复杂度：O(n)，哈希计数。
class Solution:  # LeetCode 约定的题解类
    def minimumTotalCost(self, nums1: List[int], nums2: List[int]) -> int:  # nums1、nums2 等长，返回让对应位置全不相等的最小总代价
        ans = same = 0  # ans 累计总代价，same 统计冲突位置的个数
        cnt = Counter()  # 哈希计数：记录每个值在冲突位置中出现的次数
        for i, (a, b) in enumerate(zip(nums1, nums2)):  # 逐位配对遍历，同时拿到下标 i 和两个元素 a、b
            if a == b:  # 该位置冲突：两个元素相等
                same += 1  # 冲突个数加一
                ans += i  # 与下标 i 交换代价最小，先把这个代价计入
                cnt[a] += 1  # 该值在冲突中的出现次数加一

        m = lead = 0  # m 是仍需额外抵消的多余冲突数，lead 是出现次数过多的那个值
        for k, v in cnt.items():  # 遍历冲突值的计数
            if v * 2 > same:  # 出现次数超过冲突总数的一半，超出部分无法内部两两配对
                m = v * 2 - same  # 记录超出半数之外还需要的外部位置数
                lead = k  # 记录这个多数值
                break  # 至多只有一个值超过半数，找到即跳出
        for i, (a, b) in enumerate(zip(nums1, nums2)):  # 再从非冲突位置中挑代价最小的位置来稀释多数冲突
            if m and a != b and a != lead and b != lead:  # 该位置不冲突，且两元素都不等于 lead，交换后才消掉一个多数冲突
                ans += i  # 支付下标代价 i
                m -= 1  # 还需要的外部位置数减一
        return -1 if m else ans  # m 仍大于 0 说明无解返回 -1，否则返回最小总代价
