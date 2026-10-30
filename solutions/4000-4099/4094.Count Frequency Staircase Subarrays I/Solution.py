# 题目：4094. 统计频次阶梯子数组的数目 I（Count Frequency Staircase Subarrays I）
# 思路：枚举左端点 i 并向右扩展 j，同时维护每个值在子数组里的出现次数 cnt 与它「首次出现的名次」orders（第几个出现的不同值，从 1 开始）；频次阶梯要求第 k 个出现的不同值恰好出现 k 次，所以某值出现次数一旦超过它的名次就立刻剪枝退出，而当所有不同值的「次数 == 名次」都成立（ok 等于不同值个数）时记一个答案。
# 时间复杂度：O(n^2)，左右端点各一层枚举，内层每次 O(1)；空间复杂度：O(n)，两张哈希表最多存 n 个不同值。
class Solution:  # LeetCode 约定的题解类
    def countStaircase(self, nums: list[int]) -> int:  # nums：输入数组；返回作为频次阶梯的连续子数组个数
        n = len(nums)  # n 是数组长度
        ans = 0  # ans 累计答案
        for i in range(n):  # 枚举子数组左端点 i
            orders = {}  # orders：值 → 首次出现的名次
            cnt = defaultdict(int)  # cnt：值 → 当前出现次数
            ok = 0  # ok 记录「出现次数已恰好等于名次」的不同值个数
            for j in range(i, n):  # 右端点 j 从 i 开始向右扩展
                x = nums[j]  # 取出新加入子数组的元素
                if x not in orders:  # 该值第一次出现
                    orders[x] = len(orders) + 1  # 它是第 len(orders)+1 个出现的新值，名次从 1 开始
                cnt[x] += 1  # 该值的出现次数加一
                if cnt[x] > orders[x]:  # 出现次数已超过名次，阶梯不可能再被修复
                    break  # 右端点继续扩展只会更糟，直接结束本左端点的枚举
                if cnt[x] == orders[x]:  # 该值刚达到它的目标频次
                    ok += 1  # 达标的不同值个数加一
                    if ok == len(cnt):  # 所有不同值都已达标
                        ans += 1  # 当前子数组 [i, j] 是一个频次阶梯
        return ans  # 返回频次阶梯子数组的总数
