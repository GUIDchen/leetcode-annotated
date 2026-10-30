# 题目：1552. 两球之间的磁力（Magnetic Force Between Two Balls）
# 思路：先排序，再对"最小磁力"二分答案：间距 f 越大越难放满 m 个球，check 单调，因此可二分出最大的可行 f。
# 时间复杂度：O(n log n + n log(maxPos))（排序 + 每次 check 线性扫描）；空间复杂度：O(1)（原地排序，只用常数变量）。
class Solution:  # LeetCode 约定的题解类
    def maxDistance(self, position: List[int], m: int) -> int:  # position：篮子位置；m：需要放入的球数
        def check(f: int) -> bool:  # 判断间距 f 是否"放不满" m 个球（为二分准备单调的 False/True 序列）
            prev = -inf  # 上一个球的位置，初始设为负无穷，保证第一个位置一定能放球
            cnt = 0  # 已放置的球数
            for curr in position:  # 从左到右扫描每个位置（调用前已排序，贪心成立）
                if curr - prev >= f:  # 与上一个球的距离达到 f，这个位置就可以再放一个球
                    prev = curr  # 更新上一个球的位置
                    cnt += 1  # 放置球数加一
            return cnt < m  # 放不满 m 个说明间距 f 不可行，返回 True 作为二分的分界

        position.sort()  # 升序排序，贪心放置需要位置有序
        l, r = 1, position[-1]  # 二分区间：最小磁力至少为 1，最大不超过最远两端点距离
        return bisect_left(range(l, r + 1), True, key=check)  # 找到第一个 check 为 True 的下标，即答案区间的右端（Python 3.10+ 的 key 参数）
