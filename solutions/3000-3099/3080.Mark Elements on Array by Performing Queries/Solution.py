# 题目：3080. 执行操作标记数组中的元素（Mark Elements on Array by Performing Queries）
# 思路：先按 (值, 下标) 排序，用指针 j 单调前进；每条查询标记指定下标，再从最小元素起补足 k 个未标记元素，同时维护未标记元素之和。
# 时间复杂度：O(n log n)，排序是瓶颈，其后扫描总共 O(n)；空间复杂度：O(n)，标记数组与排序数组。
class Solution:  # LeetCode 约定的题解类
    def unmarkedSumArray(self, nums: List[int], queries: List[List[int]]) -> List[int]:  # nums：原数组；queries：每条形如 [index, k] 的查询
        n = len(nums)  # 数组长度
        s = sum(nums)  # s 维护当前所有未标记元素之和，初值为全部元素之和
        mark = [False] * n  # mark[i] 表示下标 i 是否已被标记
        arr = sorted((x, i) for i, x in enumerate(nums))  # 把 (元素值, 下标) 按值升序排序，值相同时下标小的在前
        j = 0  # 排序数组 arr 上只前进不回退的指针
        ans = []  # 依次保存每条查询之后的未标记元素和
        for index, k in queries:  # 逐条处理查询
            if not mark[index]:  # 该下标尚未被标记时才需要从总和中扣减
                mark[index] = True  # 标记该下标
                s -= nums[index]  # 从总和中减去被标记元素的值
            while k and j < n:  # 从最小元素开始找前 k 个尚未标记的元素
                if not mark[arr[j][1]]:  # 只处理还没被标记过的元素
                    mark[arr[j][1]] = True  # 标记该元素
                    s -= arr[j][0]  # 从总和中减去它的值
                    k -= 1  # 还需要标记的元素个数减一
                j += 1  # 无论是否跳过，指针都前移一位
            ans.append(s)  # 记录本条查询执行完后的未标记元素和
        return ans  # 返回每条查询对应的答案
