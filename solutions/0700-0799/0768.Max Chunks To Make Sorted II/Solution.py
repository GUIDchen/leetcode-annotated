# 题目：768. 最多能完成排序的块 II（Max Chunks To Make Sorted II）
# 核心思路：用单调不减栈保存每个块的最大值，遇到比栈顶小的值就向前合并所有受影响的块。
# 时间复杂度 O(n)（每个下标最多进出栈各一次）；空间复杂度 O(n)（栈最多保存 n 个块的最大值）。
class Solution:  # LeetCode 约定的题解类
    def maxChunksToSorted(self, arr: List[int]) -> int:  # arr：允许重复元素的输入数组；返回最多能切分成多少块
        stk = []  # 单调不减栈：每个元素代表「当前某个块内的最大值」
        for v in arr:  # 从左到右扫描，v 是当前元素
            if not stk or v >= stk[-1]:  # 栈空（第一个元素）或当前值不小于栈顶：它不会和已有块冲突
                stk.append(v)  # 直接入栈，作为新块的最大值
            else:  # 否则 v 比栈顶小：v 必须并入前面的块，触发连续合并
                mx = stk.pop()  # 弹出栈顶 mx，它代表这个被合并块的最大值，稍后写回
                while stk and stk[-1] > v:  # 把所有最大值仍大于 v 的块一起弹出，它们只能并成同一个块
                    stk.pop()  # 循环体：弹出受影响的块标记
                stk.append(mx)  # 把合并后大块的最大值 mx 压回栈中
        return len(stk)  # 栈中元素个数就是最终块的数量
