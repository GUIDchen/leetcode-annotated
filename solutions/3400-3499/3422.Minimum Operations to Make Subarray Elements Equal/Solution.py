# 3422. 将子数组元素变为相等所需的最小操作数 / Minimum Operations to Make Subarray Elements Equal
# 核心思路：对每个长度为 k 的窗口维护左右两个有序列表（左边元素不大于右边，右边至多多一个），以右侧最小值为中位数，按“距中位数的绝对差之和”统计代价；窗口右移时增量更新两个集合及其元素和
# 复杂度：时间 O(n·log k)，空间 O(k)（两个有序列表最多共 k 个元素）
class Solution:  # 定义题解类
    def minOperations(self, nums: List[int], k: int) -> int:  # 求使每个长度 k 的子数组元素相等的最小操作数
        l = SortedList()  # l 存较小的一半（含中位数）
        r = SortedList()  # r 存较大的一半，r 至多比 l 多一个元素
        s1 = s2 = 0  # s1、s2 分别是 l、r 的元素和
        ans = inf  # ans 初值取正无穷
        for i, x in enumerate(nums):  # 枚举窗口右端点 i 与对应元素 x
            l.add(x)  # 先把新元素加入左集合
            s1 += x  # 同步累加左集合的和
            y = l.pop()  # 弹出左集合的最大值，准备迁移到右集合
            s1 -= y  # 左集合元素和相应减少
            r.add(y)  # 把它加入右集合
            s2 += y  # 右集合元素和相应增加
            if len(r) - len(l) > 1:  # 保持平衡：右集合最多比左集合多一个元素
                y = r.pop(0)  # 弹出右集合的最小值，归还给左集合
                s2 -= y  # 右集合元素和相应减少
                l.add(y)  # 加入左集合
                s1 += y  # 左集合元素和相应增加
            if i >= k - 1:  # 窗口长度达到 k 时才开始统计代价
                ans = min(ans, s2 - r[0] * len(r) + r[0] * len(l) - s1)  # 代价为中位数 r[0] 两侧的绝对差之和，用元素和公式 O(1) 算出
                j = i - k + 1  # 左端点下标，准备把它移出窗口以滑动
                if nums[j] in r:  # 若待删元素在右集合
                    r.remove(nums[j])  # 从右集合删除它
                    s2 -= nums[j]  # 右集合元素和相应减少
                else:  # 否则该元素在左集合
                    l.remove(nums[j])  # 从左集合删除它
                    s1 -= nums[j]  # 左集合元素和相应减少
        return ans  # 返回所有窗口中代价的最小值
