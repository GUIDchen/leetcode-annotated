# 题目：1184. 公交站间的距离（Distance Between Bus Stops）
# 思路：环形线路上只有两个方向，先算出总长，再沿顺时针从 start 走到 destination 得到一段距离 t，
#       答案就是 min(t, 总长 - t)。时间复杂度 O(n)，空间复杂度 O(1)。
class Solution:  # LeetCode 约定的题解类
    def distanceBetweenBusStops(  # distance[i] 为第 i 站到下一站的距离，start/destination 为起终点站号
        self, distance: List[int], start: int, destination: int  # 签名换行只是排版，形参含义同上
    ) -> int:  # 返回两个方向中的较短距离
        s = sum(distance)  # 整条环形线路的总长度
        t, n = 0, len(distance)  # t 累计顺时针距离，n 为站数
        while start != destination:  # 沿顺时针一站站前进，直到抵达终点
            t += distance[start]  # 累加当前站到下一站的距离
            start = (start + 1) % n  # 下标前进一并对 n 取模实现环形回绕
        return min(t, s - t)  # 另一方向长度为总长减去顺时针距离，两者取较小值
