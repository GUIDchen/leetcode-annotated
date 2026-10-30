# 题目：3386. 按下时间最长的按钮（Button with Longest Push Time）
# 思路：相邻两次按键的时刻差就是后一个按钮的按下时长，遍历一次取最大；时长相同则取按钮编号更小的。
# 时间复杂度：O(n)，只扫一遍事件数组；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def buttonWithLongestTime(self, events: List[List[int]]) -> int:  # events 的每个元素是 [按钮编号, 按下时刻]，返回按下时间最长的按钮编号
        ans, t = events[0]  # 初始化：第一个按钮的编号 ans，以及它从 0 时刻开始的耗时 t
        for (_, t1), (i, t2) in pairwise(events):  # pairwise 依次给出相邻两次按键：(_ 旧编号, t1 旧时刻) 与 (i 新编号, t2 新时刻)
            d = t2 - t1  # 本次按钮被按住的时长
            if d > t or (d == t and i < ans):  # 时长更长则胜出；时长相同取编号更小的按钮
                ans, t = i, d  # 同时更新答案编号与当前最长时长
        return ans  # 返回累计耗时最长的按钮编号
