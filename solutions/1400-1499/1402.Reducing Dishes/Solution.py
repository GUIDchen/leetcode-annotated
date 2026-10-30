# 题目：1402. 做菜顺序（Reducing Dishes）
# 思路：满意度降序排序后贪心取前缀，s 是已选菜品满意度之和；每轮把 s 累加进答案，一旦 s <= 0 就停（再加菜只会更差）。
# 时间复杂度：O(n log n)，排序主导；空间复杂度：O(1)，只用了常数个额外变量。
class Solution:  # LeetCode 约定的题解类
    def maxSatisfaction(self, satisfaction: List[int]) -> int:  # satisfaction 为每道菜的满意度
        satisfaction.sort(reverse=True)  # 原地降序排序，让满意度高的菜排在前面
        ans = s = 0  # 链式赋值：ans 为答案，s 为已选菜品满意度之和，均初始化为 0
        for x in satisfaction:  # 从满意度最高开始逐个加入
            s += x  # 加入当前菜，更新总和
            if s <= 0:  # 总和不再为正，后续加入无法提升答案
                break  # 立即停止贪心
            ans += s  # 已选每道菜都各贡献一次，故把总和 s 累加到答案
        return ans  # 返回最大总满意度
