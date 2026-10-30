# 题目：870. 优势洗牌（Advantage Shuffle）
# 思路：把 nums2 连下标按值升序排序、nums1 也升序；双指针贪心——能用最小的数赢下 nums2 当前最小值就赢，赢不了就把这个最小的数送去和 nums2 的最大值配对。
# 时间复杂度：O(n log n)，瓶颈是两次排序；空间复杂度：O(n)，辅助列表 t 与答案数组。
class Solution:  # LeetCode 约定的题解类
    def advantageCount(self, nums1: List[int], nums2: List[int]) -> List[int]:  # nums1 可重排、nums2 固定，要求让 nums1[i] > nums2[i] 成立的位置尽量多
        nums1.sort()  # 原地升序排序 nums1，便于用「最小的能赢的数」去配对
        t = sorted((v, i) for i, v in enumerate(nums2))  # 把 (nums2 的值, 原始下标) 按值排序，保留下标用于回填答案
        n = len(nums2)  # n 是数组长度
        ans = [0] * n  # 答案按 nums2 的原始下标填写，先按 n 开好空间
        i, j = 0, n - 1  # i 指向 t 中最小的待配对值，j 指向最大的待配对值
        for v in nums1:  # 按升序依次取出 nums1 的每个值
            if v <= t[i][0]:  # 当前最小值连 nums2 目前最小的值都赢不了，就让它去「送死」
                ans[t[j][1]] = v  # 配对给 nums2 中最大的值，答案填在它的原始下标处
                j -= 1  # 右端指针左移，该最大值的位置已用完
            else:  # 否则当前值能赢下 nums2 最小的值
                ans[t[i][1]] = v  # 用它拿下这个位置，答案填在最小值的原始下标处
                i += 1  # 左端指针右移，该最小值的位置已用完
        return ans  # 返回构造好的答案，答案下标与 nums2 一一对应
