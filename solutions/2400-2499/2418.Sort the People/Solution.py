# 题目：2418. 按身高排序（Sort the People）
# 思路：对下标数组按身高从大到小排序，再按排好的下标顺序取出姓名，避免同时搬运两个数组。
# 时间复杂度：O(n log n)，瓶颈是下标排序；空间复杂度：O(n)，下标数组与结果列表各占 n 个位置。
class Solution:  # LeetCode 约定的题解类
    def sortPeople(self, names: List[str], heights: List[int]) -> List[str]:  # names 与 heights 按下标一一对应
        idx = list(range(len(heights)))  # 生成 0..n-1 的下标列表，排序下标可保留姓名与身高的对应关系
        idx.sort(key=lambda i: -heights[i])  # 以身高取负作为排序键，等价于按身高从大到小排序
        return [names[i] for i in idx]  # 按排好的下标顺序取出姓名，组成最终答案
