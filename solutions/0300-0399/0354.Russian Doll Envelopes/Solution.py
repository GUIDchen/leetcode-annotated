# 题目：354. 俄罗斯套娃信封问题（Russian Doll Envelopes）
# 思路：按宽度升序、同宽高度降序排序，转成高度序列的最长严格递增子序列，用贪心加二分（d 数组）求解。
# 时间复杂度：O(n log n)，排序加 n 次二分；空间复杂度：O(n)，d 数组最多存 n 个高度。
class Solution:  # LeetCode 约定的题解类
    def maxEnvelopes(self, envelopes: List[List[int]]) -> int:  # envelopes 每项为 [宽, 高]，返回最多能嵌套的信封层数
        envelopes.sort(key=lambda x: (x[0], -x[1]))  # 宽度升序、同宽高度降序，保证同宽信封不会相互嵌套
        d = [envelopes[0][1]]  # d 保存最长严格递增子序列在每个长度下的最小末尾值（题目保证至少一个信封）
        for _, h in envelopes[1:]:  # 从第二个信封开始，只关心高度
            if h > d[-1]:  # 比当前末尾大，答案长度可以直接加一
                d.append(h)  # 把该高度接到末尾
            else:  # 否则替换 d 中第一个大于等于 h 的位置
                idx = bisect_left(d, h)  # 二分查找第一个大于等于 h 的下标
                d[idx] = h  # 换成更小的末尾值，后面更容易接上
        return len(d)  # d 的长度就是最多可嵌套的层数
