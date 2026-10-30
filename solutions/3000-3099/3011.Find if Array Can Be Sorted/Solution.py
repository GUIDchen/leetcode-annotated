# 题目：3011. 判断一个数组是否可以变为有序（Find if Array Can Be Sorted）
# 思路：只有相邻且二进制中 1 的个数相同的元素才能互换，因此数组被切分成若干可自由排序的连续块；逐块求最小/最大值，只要每块的最小值都不小于前一块的最大值，就能整体排成非降序。
# 时间复杂度：O(n)，每个元素只被归入一个块访问一次；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def canSortArray(self, nums: List[int]) -> bool:  # nums 是输入数组；返回它能否排成非降序
        pre_mx = 0  # pre_mx 记录前一个可交换块的最大值；第一块之前没有约束，初值 0（题面元素为正）
        i, n = 0, len(nums)  # i 是当前块的左端点，n 是元素个数
        while i < n:  # 外层循环：依次处理每个由「1 的个数相同」划分出的块
            cnt = nums[i].bit_count()  # 当前块的标志：整数二进制中 1 的个数（int.bit_count）
            j = i + 1  # j 指向块内下一个位置，用来向后扩展同一块
            mi = mx = nums[i]  # mi、mx 是块内最小值与最大值，初始都是块的第一个元素
            while j < n and nums[j].bit_count() == cnt:  # 相邻元素 1 的个数相同就可以互换，因此同属一个块
                mi = min(mi, nums[j])  # 维护块内最小值
                mx = max(mx, nums[j])  # 维护块内最大值
                j += 1  # 右端点继续前进
            if pre_mx > mi:  # 块内可以任意排序，但块与块之间不能跨越；前一块最大值大于本块最小值就是跨块逆序
                return False  # 存在无法消除的逆序，直接判定不可行
            pre_mx = mx  # 更新前一块的最大值，供下一块比较
            i = j  # 跳到下一块的开头
        return True  # 每块最小值都不小于前一块最大值，整体可以排成非降序
