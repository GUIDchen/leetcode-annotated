# 题目：2772. 使数组中的所有元素都等于零（Apply Operations to Make All Array Elements Equal to Zero）
# 思路：从左到右贪心 + 差分数组。要让 nums[i] 归零，必须以 i 为左端点对长度 k 的区间整体减去 nums[i]；用差分数组 d 和累计量 s 记录这些区间操作的效果。
# 时间复杂度：O(n)，只遍历一遍数组；空间复杂度：O(n)，差分数组长度为 n + 1。
class Solution:  # LeetCode 约定的题解类
    def checkArray(self, nums: List[int], k: int) -> bool:  # nums 是目标数组，k 是每次操作选定的子数组长度
        n = len(nums)  # 数组长度
        d = [0] * (n + 1)  # 差分数组：d[i] 是“作用于下标 i 的变化量”相对前一位的增量
        s = 0  # 当前位置实际生效的数值变化总量，即 d 的前缀和
        for i, x in enumerate(nums):  # 从左到右依次把每个位置清零，i 是下标
            s += d[i]  # 把从下标 i 开始生效的差分增量并入累计变化量
            x += s  # 加上此前区间操作对当前位置的影响，得到剩余值（只在本轮使用，不回写数组）
            if x == 0:  # 剩余值已为 0，不需要以它为左端点再做操作
                continue  # 直接处理下一个位置
            if x < 0 or i + k > n:  # 剩余值为负说明被减过头；剩余长度不足 k 也无法再消去它
                return False  # 该数组无法全部归零
            s -= x  # 对区间 [i, i + k - 1] 整体减去 x：当前位置立即生效，累计量随之减少
            d[i + k] += x  # 差分标记：这次减法的效果在窗口右端 i + k 处撤回
        return True  # 所有位置都成功清零
