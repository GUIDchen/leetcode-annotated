# 题目：853. 车队（Car Fleet）
# 思路：按位置从右到左（离终点由近到远）扫描，算出每辆车到终点的耗时；耗时严格大于当前车队耗时就会形成新车队。
# 时间复杂度：O(n log n)，排序主导；空间复杂度：O(n)，下标列表。
class Solution:  # 题解类
    def carFleet(self, target: int, position: List[int], speed: List[int]) -> int:  # target 为终点位置，position/speed 分别是初始位置与速度
        idx = sorted(range(len(position)), key=lambda i: position[i])  # 按下标按位置升序排序，后面逆序访问
        ans = pre = 0  # ans 车队数，pre 上一个车队的到达耗时
        for i in idx[::-1]:  # 逆序扫描：从离终点最近的车辆开始
            t = (target - position[i]) / speed[i]  # 该车独自到达终点所需时间
            if t > pre:  # 比前面的车队更慢就追不上，形成新车队
                ans += 1  # 车队数加一
                pre = t  # 更新当前车队的到达耗时
        return ans  # 返回车队总数
