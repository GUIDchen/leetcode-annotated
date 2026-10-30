# 题目：1610. 可见点的最大数目（Maximum Number of Visible Points）
# 思路：把点转成相对观察者的极角并排序，复制一份加 2π 以处理环形；对每个左端二分右端求窗口最大点数，最后加上重合点。
# 时间复杂度：O(n log n)，排序与 n 次二分；空间复杂度：O(n)，存放极角数组。
class Solution:
    def visiblePoints(  # points 为全部点，angle 为视野角度（度），location 为观察者位置
        self, points: List[List[int]], angle: int, location: List[int]  # 参数续行：保持原有的换行与缩进格式
    ) -> int:  # 返回最多可见点的数目
        v = []  # 保存非重合点相对观察者的极角（弧度）
        x, y = location  # 观察者坐标
        same = 0  # 与观察者重合的点数（它们始终可见）
        for xi, yi in points:  # 逐个处理每个点
            if xi == x and yi == y:  # 该点与观察者重合
                same += 1  # 重合点必然可见，单独计数
            else:  # 否则计算极角
                v.append(atan2(yi - y, xi - x))  # atan2(dy, dx) 得到方向角，范围 (-π, π]
        v.sort()  # 极角升序排序
        n = len(v)  # 非重合点的个数
        v += [deg + 2 * pi for deg in v]  # 复制一份并整体加 2π，把环形角度「拉直」，便于跨 0 度统计
        t = angle * pi / 180  # 角度制转弧度
        mx = max((bisect_right(v, v[i] + t) - i for i in range(n)), default=0)  # 对每个左端 i 二分出右端（≤ v[i] + t 的位置），差值即窗口大小；n 为 0 时 default=0
        return mx + same  # 窗口内的点加上与观察者重合的点
