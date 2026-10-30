# 题目：1503. 所有蚂蚁掉下来前的最后一刻（Last Moment Before All Ants Fall Out of a Plank）
# 思路：相遇掉头等价于互相穿过继续走，于是只需比较最靠左的右行蚂蚁与最靠右的左行蚂蚁的落地时间。
# 时间复杂度：O(L + R)，两个列表各扫一遍；空间复杂度：O(1)，只用一个变量累加答案。
class Solution:  # LeetCode 约定的题解类
    def getLastMoment(self, n: int, left: List[int], right: List[int]) -> int:  # n：木板右端点（坐标为 0..n）；left：向左走的蚂蚁位置；right：向右走的蚂蚁位置
        ans = 0  # 记录最晚落地时刻，初值 0
        for x in left:  # 遍历向左走的蚂蚁
            ans = max(ans, x)  # 位置 x 的蚂蚁需要 x 时间走到 0 端
        for x in right:  # 遍历向右走的蚂蚁
            ans = max(ans, n - x)  # 位置 x 的蚂蚁需要 n - x 时间走到 n 端
        return ans  # 两类最大时间中的较大者即为全部落地的时刻
