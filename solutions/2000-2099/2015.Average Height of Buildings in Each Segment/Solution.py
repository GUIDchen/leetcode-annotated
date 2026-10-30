# 题目：2015. 每段建筑物的平均高度（Average Height of Buildings in Each Segment）
# 思路：差分思想，cnt 记录各坐标处建筑数量的变化量、d 记录高度和的变化量；按坐标升序扫描，覆盖数大于 0 时产出一段「起点、终点、平均高度」，并与前一段合并。
# 时间复杂度：O(n log n)，n 为建筑数（对端点排序）；空间复杂度：O(n)，两张端点字典。
class Solution:  # LeetCode 约定的题解类
    def averageHeightOfBuildings(self, buildings: List[List[int]]) -> List[List[int]]:  # buildings：每栋建筑的 [起点, 终点, 高度]；返回合并后的 [起点, 终点, 平均高度] 列表
        cnt = defaultdict(int)  # cnt[x] 记录坐标 x 处建筑数量的变化量（差分）
        d = defaultdict(int)  # d[x] 记录坐标 x 处高度总和的变化量
        for start, end, height in buildings:  # 遍历每栋建筑，在两端打差分标记
            cnt[start] += 1  # 起点处建筑数量 +1
            cnt[end] -= 1  # 终点处建筑数量 -1
            d[start] += height  # 起点处高度和加上该建筑高度
            d[end] -= height  # 终点处高度和减去该建筑高度
        s = m = 0  # s：当前区间总高度；m：当前区间建筑数量；两者同时清零
        last = -1  # last 记录上一段的起点坐标
        ans = []  # ans 保存合并后的结果段
        for k, v in sorted(d.items()):  # 按坐标升序扫描所有端点
            if m:  # 上一段有建筑覆盖时才可能产出结果段 [last, k]
                avg = s // m  # 该段的平均高度，题目保证整除，用整数除法
                if ans and ans[-1][2] == avg and ans[-1][1] == last:  # 与上一段平均高度相同且首尾相接，可以合并
                    ans[-1][1] = k  # 延长上一段的右端点
                else:  # 否则需要新开一段
                    ans.append([last, k, avg])  # 把 [last, k] 这一段及其平均高度加入答案
            s += v  # 把当前坐标的高度变化计入总高度
            m += cnt[k]  # 把当前坐标的建筑数量变化计入覆盖数
            last = k  # 当前坐标成为下一段的起点
        return ans  # 返回所有结果段
