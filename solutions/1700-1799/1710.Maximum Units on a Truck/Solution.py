# 题目：1710. 卡车上的最大单元数（Maximum Units on a Truck）
# 思路：贪心，按每箱单元数从大到小排序，依次尽量装满收益最高的规格，直到卡车容量用完。
# 时间复杂度：O(n log n)，主要是排序；空间复杂度：O(n)，sorted 生成新列表。
class Solution:  # LeetCode 约定的题解类
    def maximumUnits(self, boxTypes: List[List[int]], truckSize: int) -> int:  # boxTypes 每项为 [箱子数, 每箱单元数]；truckSize 是可装的箱数上限
        ans = 0  # 累计能装上的单元总数
        for a, b in sorted(boxTypes, key=lambda x: -x[1]):  # 按每箱单元数从大到小排序，优先装收益高的规格
            ans += b * min(truckSize, a)  # 该规格最多再装 min(剩余容量, 该规格箱数) 箱，再乘每箱单元数累加
            truckSize -= a  # 扣除该规格的全部箱数（可能变负，随后立即退出）
            if truckSize <= 0:  # 卡车已经装满
                break  # 无需再考虑收益更低的规格
        return ans  # 返回最大单元总数
