# 题目：1054. 距离相等的条形码（Distant Barcodes）
# 思路：用 Counter 统计频次并按「频次降序、数值升序」排序，前一半填偶数下标、其余填奇数下标，相同条码被隔开一位。
# 时间复杂度：O(n log n)，排序为主；空间复杂度：O(n)，计数表与答案数组。
class Solution:  # LeetCode 约定的题解类
    def rearrangeBarcodes(self, barcodes: List[int]) -> List[int]:  # barcodes 是输入的条码数组，返回重排后的数组
        cnt = Counter(barcodes)  # 统计每个条码出现的次数
        barcodes.sort(key=lambda x: (-cnt[x], x))  # 出现次数多的排前面；次数相同则数值小的排前面，保证结果确定
        n = len(barcodes)  # 条码总个数
        ans = [0] * len(barcodes)  # 预分配答案数组，长度与输入相同
        ans[::2] = barcodes[: (n + 1) // 2]  # 前一半（含正中间那个）依次放到偶数下标 0、2、4……
        ans[1::2] = barcodes[(n + 1) // 2 :]  # 其余元素依次放到奇数下标 1、3、5……
        return ans  # 偶数位与奇数位交错，相同条码不会相邻
