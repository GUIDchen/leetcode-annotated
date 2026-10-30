# 3961. 设备评分的最大和 / Maximize Sum of Device Ratings
# 核心思路：设备评分为其所有单元容量的最小值。把每台设备的最小单元移走后，其评分升为次小值 x[1]，
#          共 m-1 台设备如此操作后剩一台设备作为接收方不损失，其评分降为全局最小值，因此答案为 sum(x[1]) - (mn2 - mn)。
# 复杂度：时间 O(m * n log n)（m 台设备、每台 n 个单元，逐个排序），空间 O(1)（排序就地完成）。

class Solution:
    def maxRatings(self, units: List[List[int]]) -> int:  # 返回所有设备评分之和的最大值
        n = len(units[0])  # 每台设备的单元数量
        if n == 1:  # 每台设备只有一个单元：移走会让它清空、评分变 0，不操作最优
            return sum(x[0] for x in units)  # 直接返回所有设备唯一评分之和

        ans = 0  # 累加每台设备贡献的次小值 x[1]
        mn = mn2 = inf  # mn 记录全局最小容量，mn2 记录最小次小值
        for x in units:  # 逐台设备处理
            x.sort()  # 将该设备的单元容量升序排序
            ans += x[1]  # 移走最小单元后该设备评分变为次小值，累加进总和
            mn2 = min(mn2, x[1])  # 更新最小的次小值（即损失最小的接收方）
            mn = min(mn, x[0])  # 更新全局最小容量（会被送入接收方）
        ans -= mn2 - mn  # 扣除一台设备评分由次小值降到全局最小值的损失
        return ans  # 返回所有设备评分之和的最大值
