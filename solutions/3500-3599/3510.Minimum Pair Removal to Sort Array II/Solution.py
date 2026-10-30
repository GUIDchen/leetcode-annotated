# 题目：3510. 移除最小数对使数组有序 II（Minimum Pair Removal to Sort Array II）
# 思路：用一张有序表维护「每个相邻对的和 + 左端下标」，另一张有序表维护仍存活的下标（代替双向链表）。同时统计当前相邻逆序对数量：每轮取出和最小的相邻对并合并，只更新被合并位置前后两个邻居的逆序对计数与相邻对记录，逆序对清零时即结束。
# 时间复杂度：O(n log n)，每个下标最多被合并一次，每次操作是若干次 O(log n) 的有序表操作；空间复杂度：O(n)，两张有序表各存 O(n) 条记录。
class Solution:  # LeetCode 约定的题解类
    def minimumPairRemoval(self, nums: List[int]) -> int:  # nums：待处理数组；返回使数组非递减所需的最少合并次数
        n = len(nums)  # 数组长度
        sl = SortedList()  # 按 (和, 左端下标) 升序的有序表，首元素即和最小的相邻对
        idx = SortedList(range(n))  # 仍存活的下标有序表，用相邻位置模拟双向链表
        inv = 0  # 当前相邻逆序对（nums[i] > nums[i+1]）的数量
        for i in range(n - 1):  # 预处理每一个相邻对
            sl.add((nums[i] + nums[i + 1], i))  # 把 (相邻和, 左端下标) 插入有序表
            if nums[i] > nums[i + 1]:  # 这一对构成逆序
                inv += 1  # 逆序对计数加一
        ans = 0  # 记录已执行的合并次数
        while inv:  # 还存在逆序对就继续合并
            ans += 1  # 合并次数加一
            s, i = sl.pop(0)  # 弹出并返回和最小的那个相邻对，和记作 s，左端下标记作 i
            pos = idx.index(i)  # i 在存活下标有序表中的位置
            j = idx[pos + 1]  # 右邻居下标（它会被合并掉）
            if nums[i] > nums[j]:  # 合并前 (i, j) 是逆序对
                inv -= 1  # 该逆序对随合并一起消失
            if pos > 0:  # 存在左邻居 h 时才需要更新它
                h = idx[pos - 1]  # 取出左邻居下标
                if nums[h] > nums[i]:  # 合并前 (h, i) 是逆序对
                    inv -= 1  # 该逆序对即将失效
                sl.remove((nums[h] + nums[i], h))  # 旧的相邻对 (h, i) 记录作废
                if nums[h] > s:  # 合并后这一对变成 (h, 新值 s)
                    inv += 1  # 新值变小，于是新增一个逆序对
                sl.add((nums[h] + s, h))  # 登记新的相邻对和
            if pos + 2 < len(idx):  # 存在右邻居的右邻居 k 时才需要更新
                k = idx[pos + 2]  # 取出 k 的下标
                if nums[j] > nums[k]:  # 合并前 (j, k) 是逆序对
                    inv -= 1  # j 被删除，该逆序对消失
                sl.remove((nums[j] + nums[k], j))  # 旧的相邻对 (j, k) 记录作废
                if s > nums[k]:  # 合并后相邻对变成 (i, k)
                    inv += 1  # 新值变大，于是新增一个逆序对
                sl.add((s + nums[k], i))  # 登记新的相邻对和，左端下标是 i

            nums[i] = s  # 把合并后的和写回左端位置
            idx.remove(j)  # 右端下标被移除，相当于链表删除节点
        return ans  # 返回最少合并次数
