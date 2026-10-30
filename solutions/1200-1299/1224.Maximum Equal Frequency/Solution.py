# 题目：1224. 最大相等频率（Maximum Equal Frequency）
# 思路：边扫边维护 cnt（每值出现次数）与 ccnt（频率 → 数字个数），用三个条件判断删掉一个元素后是否所有数频率相等：全为 1、最大频率只多一次、存在一个孤立的一次数。
# 时间复杂度：O(n)，Counter 均摊 O(1)；空间复杂度：O(n)，两个计数器的元素个数。
class Solution:  # LeetCode 约定的题解类
    def maxEqualFreq(self, nums: List[int]) -> int:  # nums：输入数组；返回删除一个元素后所有数频率相等的最长前缀长度
        cnt = Counter()  # cnt[v]：值 v 目前为止出现的次数
        ccnt = Counter()  # ccnt[c]：出现次数恰好为 c 的不同值有几个（频率的频率）
        ans = mx = 0  # ans：最大合法前缀长度；mx：出现过的最大频率
        for i, v in enumerate(nums, 1):  # i 是前缀长度（从 1 开始），v 是刚加入的这个数
            if v in cnt:  # 该数之前出现过，说明它原来在频率 cnt[v] 这一组
                ccnt[cnt[v]] -= 1  # 先把原来那一组的计数减 1
            cnt[v] += 1  # 该数出现次数加 1
            mx = max(mx, cnt[v])  # 维护最大频率；频率只增不减，取 max 即可
            ccnt[cnt[v]] += 1  # 新频率这一组的计数加 1
            if mx == 1:  # 情况一：最大频率为 1，说明每个数都只出现一次
                ans = i  # 删掉任意一个数后剩下全相等，整个前缀合法
            elif ccnt[mx] * mx + ccnt[mx - 1] * (mx - 1) == i and ccnt[mx] == 1:  # 情况二：最大频率那组只有一个数且只多出一次，删掉多出的那次即可
                ans = i  # 「最大频率组 + 次大频率组」正好拼成前缀长度，说明可以相等
            elif ccnt[mx] * mx + 1 == i and ccnt[1] == 1:  # 情况三：存在一个只出现 1 次的孤立数，删掉它其余频率相等
                ans = i  # 孤立数删掉后总数正好减 1，当前前缀合法
        return ans  # 返回最大合法前缀长度
