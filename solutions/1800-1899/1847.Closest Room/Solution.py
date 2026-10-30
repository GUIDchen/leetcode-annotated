# 题目：1847. 最近的房间（Closest Room）
# 思路：房间按面积升序、查询按 minSize 升序离线处理，用有序列表维护"面积达标"的房间编号；门槛升高时移除小房间，
#       再用 bisect_left 找到 prefer 的左右邻居，比较编号差取更近的那个（距离相同取编号更小）。
# 时间复杂度：O((n+k) log n)，排序与每次二分/删除都是对数级；空间复杂度：O(n + k)，有序列表与答案数组。
class Solution:  # LeetCode 约定的题解类
    def closestRoom(  # 求每个查询对应的最近房间编号
        self, rooms: List[List[int]], queries: List[List[int]]  # rooms：{编号, 面积}；queries：{偏好编号, 最小面积}
    ) -> List[int]:  # 返回与 queries 一一对应的房间编号列表
        rooms.sort(key=lambda x: x[1])  # 按面积升序排列房间，便于随门槛上升单向剔除
        k = len(queries)  # 查询数量
        idx = sorted(range(k), key=lambda i: queries[i][1])  # 按 minSize 升序排列查询下标，实现离线处理
        ans = [-1] * k  # 答案数组，默认 -1 表示没有面积达标的房间
        i, n = 0, len(rooms)  # i 指向第一个可能达标的房间，n 是房间总数
        sl = SortedList(x[0] for x in rooms)  # 有序列表保存当前所有达标房间的编号，支持二分与删除
        for j in idx:  # 按门槛从低到高逐个处理查询
            prefer, minSize = queries[j]  # 偏好编号与面积下限
            while i < n and rooms[i][1] < minSize:  # 面积不足的房间要从候选集合里移除
                sl.remove(rooms[i][0])  # 精确删除该编号的一次出现
                i += 1  # 门槛单调不减，指针只前进
            if i == n:  # 所有房间都不达标，后面的查询同样无解
                break  # 剩余答案保持 -1
            p = sl.bisect_left(prefer)  # 找到第一个编号 >= prefer 的位置
            if p < len(sl):  # 存在右侧邻居
                ans[j] = sl[p]  # 先以右侧邻居作为候选答案
            if p and (ans[j] == -1 or ans[j] - prefer >= prefer - sl[p - 1]):  # 左侧邻居存在且距离不大于右侧时更优（等距取编号更小）
                ans[j] = sl[p - 1]  # 用左侧邻居更新答案
        return ans  # 返回每个查询的答案
