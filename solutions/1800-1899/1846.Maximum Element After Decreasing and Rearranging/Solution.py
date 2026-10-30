# 题目：1846. 减小和重新排列数组后的最大元素（Maximum Element After Decreasing and Rearranging）
# 思路：先排序，把首元素压到 1，再从左到右令 arr[i] = min(arr[i], arr[i-1]+1)，每步取可行上限，末元素即为答案。
# 时间复杂度：O(n log n)，主要开销是排序；空间复杂度：O(1) 额外空间（排序原地进行，直接改传入列表）。
class Solution:  # LeetCode 约定的题解类
    def maximumElementAfterDecrementingAndRearranging(self, arr: List[int]) -> int:  # arr：可任意重排、只能减小的数组
        arr.sort()  # 升序排序，让相邻元素依次形成尽量平缓的上升序列
        arr[0] = 1  # 题目条件要求首元素等于 1，只能减小，所以直接改成 1
        for i in range(1, len(arr)):  # 从第二个元素开始向右推进
            arr[i] = min(arr[i], arr[i - 1] + 1)  # 相邻差最多为 1，取"原值"与"前项+1"的较小者
        return arr[-1]  # 末元素已是这些约束下能取到的最大值
