# 题目：2459. 通过移动项目到空白区域来排序数组（Sort Array by Moving Items to Empty Space）
# 思路：把数组视为置换，空位（值 0）每进入一个置换环就要付出「环长 + 1」次操作；对恒等映射与整体左移两种目标分别计算，取较小值。
# 时间复杂度：O(n)，两次遍历置换环；空间复杂度：O(n)，访问标记数组与复制出的新数组。
class Solution:  # LeetCode 约定的题解类
    def sortArray(self, nums: List[int]) -> int:  # nums：以 0 表示空白位的排列
        def f(nums, k):  # 通用代价函数：k 表示空白位在目标映射下应处的下标
            vis = [False] * n  # 访问标记，n 来自外层作用域
            cnt = 0  # 操作次数累计
            for i, v in enumerate(nums):  # 同时取得下标 i 与当前值 v，寻找未处理的置换环
                if i == v or vis[i]:  # 已经就位，或该位置已被之前的环统计过
                    continue  # 跳过，不构成新的环
                cnt += 1  # 每个非平凡环先付 1 次操作，相当于把空白位挪进这个环
                j = i  # 从当前未访问的位置出发沿置换行走
                while not vis[j]:  # 沿 j -> nums[j] 环行，直到回到已访问的位置
                    vis[j] = True  # 标记该位置已统计
                    cnt += 1  # 环上每个元素都要被移动一次
                    j = nums[j]  # 跳到当前元素应在的目标位置
            return cnt - 2 * (nums[k] != k)  # 空白位不在 k 处时省掉 2 次操作，布尔值参与算术

        n = len(nums)  # 数组长度，供内层函数闭包使用
        a = f(nums, 0)  # 方案一：目标为恒等映射，空白 0 应回到下标 0
        b = f([(v - 1 + n) % n for v in nums], n - 1)  # 方案二：整体循环左移生成新数组，空白 0 的目标下标为 n-1
        return min(a, b)  # 两种目标映射取更小的操作数
