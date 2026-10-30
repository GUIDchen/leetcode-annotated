# 题目：3814. 预算下的最大总容量（Maximum Capacity Within Budget）
# 思路：先筛出花费小于 budget 的「(花费, 容量)」对并按花费升序排序，再用有序列表 SortedList 记录候选物品的容量。双指针 i、j 从两端收缩：固定左端点 i，把所有与 i 组合仍超预算的右端点 j 逐个移出集合，此时集合剩余容量中的最大值就是能与 i 搭配的最优解，取全局最大值即为答案。
# 时间复杂度：O(n log n)，排序与有序列表的增删查均为对数级；空间复杂度：O(n)，候选数组与有序列表各存至多 n 个元素。
class Solution:  # LeetCode 约定的题解类
    def maxCapacity(self, costs: List[int], capacity: List[int], budget: int) -> int:  # costs/capacity：每个物品的花费与容量；budget：总预算
        arr = []  # arr 存放所有买得起的物品，元素为 (花费, 容量)
        for a, b in zip(costs, capacity):  # 同时取出每个物品的花费 a 与容量 b
            if a < budget:  # 单个物品花费必须严格小于预算，否则根本买不起
                arr.append((a, b))  # 买得起就加入候选集合
        if not arr:  # 没有任何买得起的物品
            return 0  # 一个都买不了，最大总容量为 0
        arr.sort()  # 按 (花费, 容量) 升序排序，方便用双指针控制花费之和
        remain = SortedList()  # remain 保存「容量, 原下标」，按容量升序，可 O(log n) 取最大值并删除指定元素
        for i, (_, b) in enumerate(arr):  # 把全部候选物品放入 remain
            remain.add((b, i))  # 用下标 i 区分容量相同的不同物品，避免重复删除
        i, j = 0, len(arr) - 1  # i 从左端、j 从右端开始收缩双指针
        ans = remain[-1][0]  # 先只买一个物品：最大容量就是集合中容量最大的那个
        while i < j:  # 左右端点不能重合，重合的情形等价于只买一个物品（已统计过）
            remain.discard((arr[i][1], i))  # 把左端点 i 移出集合，之后集合只含 (i, j] 区间的物品
            while i < j and arr[i][0] + arr[j][0] >= budget:  # 花费之和超预算时，右端点 j 不可能与 i 搭配成功
                remain.discard((arr[j][1], j))  # 把不合法（超预算）的右端点 j 移出集合
                j -= 1  # 右端点左移，尝试花费更小的物品
            if remain:  # 集合里还有可以与 i 搭配的物品
                ans = max(ans, arr[i][1] + remain[-1][0])  # 用 i 的容量加上剩余集合中的最大容量更新答案
            i += 1  # 左端点右移，进入下一轮
        return ans  # 返回预算内能获得的最大总容量
