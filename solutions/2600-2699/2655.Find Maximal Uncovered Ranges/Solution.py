# 题目：2655. 寻找最大长度的未覆盖区间（Find Maximal Uncovered Ranges）
# 核心思路：把被覆盖区间按左端点排序后从左到右扫描，维护已覆盖的最右位置 last，遇到空隙就输出 [last+1, l-1]，最后补上尾部空隙。
# 时间复杂度：O(k log k)，k 是区间个数，主要是排序；空间复杂度：O(1) 额外（不计排序与返回值）。
class Solution:  # 题解类
    def findMaximalUncoveredRanges(  # 方法签名：返回所有极大未覆盖区间，参数写在下一行
        self, n: int, ranges: List[List[int]]  # n：坐标范围为 [0, n-1]；ranges：被覆盖的闭区间列表
    ) -> List[List[int]]:  # 返回值是区间列表
        ranges.sort()  # 按左端点升序排序，便于从左往右扫描合并
        last = -1  # last 是当前已被覆盖到的最右位置，-1 表示还没开始覆盖
        ans = []  # ans 收集所有极大未覆盖区间
        for l, r in ranges:  # 逐个取出被覆盖区间的左右端点
            if last + 1 < l:  # last 与 l 之间有空隙，说明 [last+1, l-1] 未被覆盖
                ans.append([last + 1, l - 1])  # 记录这一段极大未覆盖区间
            last = max(last, r)  # 更新已覆盖的最右端，取较大值防止被更短的区间「回退」
        if last + 1 < n:  # 扫完后末尾可能还有一段未覆盖
            ans.append([last + 1, n - 1])  # 记录末尾的极大未覆盖区间
        return ans  # 返回结果
