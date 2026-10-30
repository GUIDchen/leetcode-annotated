# 题目：2943. 最大化网格图中正方形空洞的面积（Maximize Area of Square Hole in Grid）
# 思路：分别把两个方向可移除的杆编号排序，求最长的一段连续整数长度；连续 k 根杆能撑开的空洞边长为 k+1，两个方向取较小边再平方即得面积。
# 时间复杂度：O(h log h + v log v)，来自两次排序；空间复杂度：O(1)，只用了常数个额外变量（排序原地进行）。
class Solution:  # LeetCode 约定的题解类
    def maximizeSquareHoleArea(  # 定义题解方法，返回能得到的最大正方形空洞面积
        self, n: int, m: int, hBars: List[int], vBars: List[int]  # self 是实例；n、m 是网格行数与列数；hBars、vBars 是允许移除的横杆/竖杆编号
    ) -> int:
        def f(nums: List[int]) -> int:  # 内部函数：求某一方向的杆集合能撑开的最大空洞边长
            nums.sort()  # 先排序，编号连续的杆才会相邻出现
            ans = cnt = 1  # ans 记录历史最长的连续段长度，cnt 是当前连续段长度
            for i in range(1, len(nums)):  # 从第二个元素开始，逐对比较相邻的杆编号
                if nums[i] == nums[i - 1] + 1:  # 相邻两数正好相差 1，连续段可以继续延长
                    cnt += 1  # 当前连续段长度加一
                    ans = max(ans, cnt)  # 用更长的连续段更新历史最长
                else:  # 否则连续段在这里被断开
                    cnt = 1  # 当前连续段长度重置为 1
            return ans + 1  # 连续 k 根杆对应边长 k + 1 的空洞

        return min(f(hBars), f(vBars)) ** 2  # 正方形边长受两个方向中较短边限制，平方即得面积
