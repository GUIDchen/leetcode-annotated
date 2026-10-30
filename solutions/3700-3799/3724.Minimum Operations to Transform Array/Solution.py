# 3724. Minimum Operations to Transform Array（转换数组的最少操作次数）
# 核心思路：以 nums2 的末尾元素 nums2[-1] 为参照，逐对把 [y, x] 的差值累加为代价；若没有任何一对区间覆盖 nums2[-1]，再补上把它调到最近端点的最小距离。
# 复杂度：时间 O(n)，空间 O(1)。

class Solution:
    def minOperations(self, nums1: List[int], nums2: List[int]) -> int:  # 返回把 nums1 前 n 个元素变成 nums2 对应元素所需的最少操作次数
        ans = 1  # ans 记为 1，作为并入 nums2 末尾元素这一次操作的固定基数
        ok = False  # ok 表示是否已有一对区间覆盖了 nums2[-1]
        d = inf  # d 记录把 nums2[-1] 调到区间端点的最小距离，初值为无穷大
        for x, y in zip(nums1, nums2):  # 逐个位置处理 nums1 与 nums2 的对应元素
            if x < y:  # 保证 x >= y，便于用区间 [y, x] 表示这一对
                x, y = y, x  # 交换两数，使 x 成为较大者
            ans += x - y  # 把区间 [y, x] 抹平需要 x-y 次操作，直接累加进答案
            d = min(d, abs(x - nums2[-1]), abs(y - nums2[-1]))  # 不搬动 nums2[-1] 时，把它调到该区间端点所需的最小距离
            ok = ok or y <= nums2[-1] <= x  # 若 nums2[-1] 已落在 [y, x] 内，说明这一对可以顺带覆盖它
        if not ok:  # 没有任何一对覆盖 nums2[-1]
            ans += d  # 额外付出最小距离 d，把 nums2[-1] 调整到最近端点
        return ans  # 返回最少操作次数
