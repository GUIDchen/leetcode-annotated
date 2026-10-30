# 题目：2274. 不含特殊楼层的最大连续楼层数（Maximum Consecutive Floors Without Special Floors）
# 思路：排序特殊楼层后，答案只可能出现在三类区间：bottom 到首个特殊楼层、相邻特殊楼层之间、末尾特殊楼层到 top。
# 时间复杂度：O(m log m)，m 为特殊楼层数量（排序开销）；空间复杂度：O(1)，除排序外只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def maxConsecutive(self, bottom: int, top: int, special: List[int]) -> int:  # bottom/top：楼层区间两端；special：特殊楼层列表
        special.sort()  # 原地升序排序，之后才能用相邻差值切分区间
        ans = max(special[0] - bottom, top - special[-1])  # 先算两端的段长：bottom 到首个特殊楼层、末尾特殊楼层到 top
        for x, y in pairwise(special):  # 依次取出相邻的一对特殊楼层 (x, y)
            ans = max(ans, y - x - 1)  # 中间段长度要减 1，因为 x 与 y 本身都是特殊楼层不能计入
        return ans  # 返回不含特殊楼层的最大连续楼层数
