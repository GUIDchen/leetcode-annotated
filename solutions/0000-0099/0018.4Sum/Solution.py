# 题目：18. 四数之和（4Sum）
# 思路：先排序，两层循环固定前两个数 i、j 并跳过重复，后两个数用左右双指针 k、l 相向收缩逼近 target。
# 时间复杂度：O(n^3)，两层枚举加一次双指针扫描；空间复杂度：O(1)，不计排序与答案本身占用的空间。
class Solution:  # LeetCode 约定的题解类
    def fourSum(self, nums: List[int], target: int) -> List[List[int]]:  # nums：输入数组（会被就地排序）；target：目标和
        n = len(nums)  # 元素个数，后面用来定循环上界和双指针右端
        ans = []  # 收集所有互不相同的四元组
        if n < 4:  # 不足 4 个数，凑不出四元组
            return ans  # 直接返回空答案
        nums.sort()  # 排序后数组有序才能用双指针，同时让相同元素相邻便于去重
        for i in range(n - 3):  # 枚举第一个数，至少给后面留 3 个位置
            if i and nums[i] == nums[i - 1]:  # 与前一个值相同，同一组答案会重复产出
                continue  # 跳过这个重复的起点
            for j in range(i + 1, n - 2):  # 枚举第二个数，至少给 k、l 留 2 个位置
                if j > i + 1 and nums[j] == nums[j - 1]:  # j 是内层起点时不能跳过；其余情况与上一个相同就去重
                    continue  # 跳过重复的第二个数
                k, l = j + 1, n - 1  # 双指针：k 从左往右增大和，l 从右往左减小和
                while k < l:  # 两指针未相遇就还没枚举完
                    x = nums[i] + nums[j] + nums[k] + nums[l]  # 当前四数之和（Python 整数不会溢出）
                    if x < target:  # 当前和偏小
                        k += 1  # 左指针右移，使和变大
                    elif x > target:  # 当前和偏大
                        l -= 1  # 右指针左移，使和变小
                    else:  # 恰好等于 target，得到一个合法四元组
                        ans.append([nums[i], nums[j], nums[k], nums[l]])  # 记录答案
                        k, l = k + 1, l - 1  # 两个指针同时内移一步
                        while k < l and nums[k] == nums[k - 1]:  # 跳过与刚用过的 k 相同的值，避免重复答案
                            k += 1  # 继续右移
                        while k < l and nums[l] == nums[l + 1]:  # 跳过与刚用过的 l 相同的值，避免重复答案
                            l -= 1  # 继续左移
        return ans  # 返回全部不重复的四元组
