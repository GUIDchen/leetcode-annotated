# 题目：457. 环形数组是否存在循环（Circular Array Loop）
# 思路：枚举起点，快慢指针在同向路径上判环；一条路径走完后把元素置 0 标记，整体均摊 O(n)。
# 时间复杂度：O(n)，每个下标最多被访问常数次；空间复杂度：O(1)，只用到几个指针变量。
class Solution:  # LeetCode 约定的题解类
    def circularArrayLoop(self, nums: List[int]) -> bool:  # nums 是步数数组，判断是否存在同向且长度大于 1 的循环
        n = len(nums)  # n 为数组长度，供内部函数取模使用

        def next(i):  # 内部函数 next：计算从 i 走 nums[i] 步后的下标（支持负步数）
            return (i + nums[i] % n + n) % n  # 先对步数取模防溢出，+n 把负数纠正为正，再取模得到 [0,n)

        for i in range(n):  # 枚举每个下标作为环的起点
            if nums[i] == 0:  # 值为 0 说明已被标记为访问过
                continue  # 跳过这个起点
            slow, fast = i, next(i)  # 快慢指针初始化：slow 在起点，fast 先走一步
            while nums[slow] * nums[fast] > 0 and nums[slow] * nums[next(fast)] > 0:  # 追及条件：当前点与下一点同号，且 fast 的下一点也同号（排除长度 1 的自环）
                if slow == fast:  # 快慢指针相遇，说明有环
                    if slow != next(slow):  # 环长必须大于 1
                        return True  # 是合法循环，返回真
                    break  # 是自环，退出本次探查
                slow, fast = next(slow), next(next(fast))  # 慢指针走一步，快指针走两步
            j = i  # 从起点重走这条路径，准备标记
            while nums[j] * nums[next(j)] > 0:  # 只要下一步仍同号，就仍在这条路径上
                nums[j] = 0  # 置 0 标记已访问，后续不再从该下标出发
                j = next(j)  # 移动到下一个下标
        return False  # 所有起点都试过，不存在合法循环
