# 题目：2454. 下一个更大元素 IV（Next Greater Element IV）
# 思路：先按数值从大到小（同值下标升序）排序，再用有序列表 SortedList 维护已处理的下标；对下标 i 二分，若其右侧还剩至少两个已处理下标，第二个就是它的第二个更大元素。
# 时间复杂度：O(n log n)，排序加上每次二分/插入 O(log n)；空间复杂度：O(n)，排序数组、有序列表与答案数组各占 O(n)。
class Solution:  # LeetCode 约定的题解类
    def secondGreaterElement(self, nums: List[int]) -> List[int]:  # nums：输入数组
        arr = [(x, i) for i, x in enumerate(nums)]  # 把每个元素打包成 (数值, 下标)
        arr.sort(key=lambda x: -x[0])  # 按数值从大到小排序；sort 稳定，因此同值元素保持下标升序
        sl = SortedList()  # 有序列表，保存已处理过的元素下标（其值不小于当前值）
        n = len(nums)  # 数组长度
        ans = [-1] * n  # 答案数组，默认 -1 表示不存在第二个更大元素
        for _, i in arr:  # 按数值从大到小，依次处理每个下标
            j = sl.bisect_right(i)  # 二分得到有序列表中第一个大于 i 的位置
            if j + 1 < len(sl):  # 该位置之后还剩至少两个下标，说明存在第二个更大元素
                ans[i] = nums[sl[j + 1]]  # 第二个更大元素是右侧第二个已处理下标处的值
            sl.add(i)  # 把当前下标插入有序列表，供数值更小的元素查询
        return ans  # 返回每个位置的第二个更大元素
