# 3917. Count Indices With Opposite Parity | 统计下标的相反奇偶性得分（简单）
# 核心思路：先统计全体元素中偶数和奇数各有多少个；再从左往右扫描，每走到下标 i 就把 nums[i] 从计数中移出，此时计数表恰好只包含 i 右侧的元素，取与 nums[i] 奇偶性相反的那一类的个数，即为 ans[i]。
# 复杂度：时间 O(n)，两趟线性扫描；空间 O(n)，答案数组（额外计数只用 O(1)）。
class Solution:  # 定义题解类
    def countOppositeParity(self, nums: list[int]) -> list[int]:  # 返回每个下标右侧、与其元素奇偶性相反的元素个数
        cnt = [0, 0]  # cnt[0] 存偶数个数，cnt[1] 存奇数个数
        for x in nums:  # 第一遍：统计全体元素的奇偶个数
            cnt[x & 1] += 1  # 按最低位归档：x & 1 为 0 记偶数，为 1 记奇数
        ans = [0] * len(nums)  # 答案数组，长度与输入相同
        for i, x in enumerate(nums):  # 第二遍：从左往右逐个“移出”当前元素并查询
            cnt[x & 1] -= 1  # 把下标 i 的元素本身移出计数，于是 cnt 只表示 i 右侧的元素
            ans[i] = cnt[x & 1 ^ 1]  # 取奇偶性相反的那一类（& 的优先级高于 ^）的剩余个数
        return ans  # 返回每个下标对应的答案
