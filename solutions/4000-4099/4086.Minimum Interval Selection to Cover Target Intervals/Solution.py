# 题目：4086. 覆盖目标区间的最少区间（Minimum Interval Selection to Cover Target Intervals）
# 核心思路：可用区间与目标区间都按左端点升序排序后做「跳跃式覆盖」贪心：对每个目标区间，从当前覆盖位置 cur 与目标左端点 l 的较大值开始，在所有左端点能接上缺口的可用区间里取右端点最远的一个；若接不上则出现断层，返回 -1。
# 时间复杂度：O((n+m) log(n+m))，主要是两次排序，内层扫描因指针 i 单调前进总体线性；空间复杂度：O(1) 额外空间（不计排序开销）。
class Solution:  # LeetCode 约定的题解类
    def minSelection(  # 返回覆盖全部目标区间所需的最少可用区间数，无法覆盖则返回 -1
        self, availableIntervals: list[list[int]], targetIntervals: list[list[int]]  # availableIntervals：可选区间集合；targetIntervals：需要被覆盖的目标区间集合
    ) -> int:  # 返回类型为整数
        availableIntervals.sort(key=lambda x: x[0])  # 可用区间按左端点升序排序
        targetIntervals.sort(key=lambda x: x[0])  # 目标区间也按左端点升序排序，保证从左到右依次覆盖
        ans = cur = 0  # ans 为已选区间数，cur 为当前已覆盖到的位置
        i = 0  # i 为可用区间指针，只前进不回退
        for l, r in targetIntervals:  # 依次处理每个目标区间 [l, r]
            while cur < r:  # 还没覆盖到目标右端点时，继续补充区间
                uncover = max(l, cur)  # 当前真正需要被覆盖的起点：目标左端点与已覆盖位置的较大值
                nxt = cur  # nxt 记录这一轮能延伸到的最远位置
                while (  # 扫描所有左端点不超过缺口起点的可用区间
                    i < len(availableIntervals) and availableIntervals[i][0] <= uncover  # 两个条件：指针未越界，且区间左端点能接上缺口
                ):  # 内层扫描条件结束
                    nxt = max(nxt, availableIntervals[i][1])  # 取右端点最远的区间，延伸得最多
                    i += 1  # 指针后移；这些区间之后也不会更优，可以永久跳过
                if nxt < uncover or nxt == cur:  # 没有区间能覆盖缺口起点，或者无法再向右推进
                    return -1  # 出现断层，不可能覆盖全部目标区间
                cur = nxt  # 已覆盖位置推进到最远处
                ans += 1  # 又使用了一个可用区间
        return ans  # 返回最少的区间选择数量
