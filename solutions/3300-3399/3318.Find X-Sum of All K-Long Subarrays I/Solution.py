# 题目：3318. 计算子数组的 x-sum I（Find X-Sum of All K-Long Subarrays I）
# 核心思路：长度为 k 的滑动窗口 + 两个有序表（按 (出现次数, 数值) 排序）：l 保存前 x 大的元素并维护它们的「次数×数值」之和 s，r 是备选；每一步先加入新元素、调整 l 的规模、记录答案，再移除左端旧元素。
# 时间复杂度：O(n·x·log n)；空间复杂度：O(n)，用于答案数组与频次表。
class Solution:  # LeetCode 约定的题解类
    def findXSum(self, nums: List[int], k: int, x: int) -> List[int]:  # nums：原数组；k：窗口长度；x：取出现次数最多的前 x 种元素
        def add(v: int):  # 把值 v 按当前出现次数插入合适的集合
            if cnt[v] == 0:  # 出现 0 次的值不该留在集合里
                return  # 直接返回
            p = (cnt[v], v)  # 排序键：(出现次数, 数值)
            if l and p > l[0]:  # 比 l 的最小元素还大，说明它属于前 x 名
                nonlocal s  # 闭包内要给外层的 s 重新赋值
                s += p[0] * p[1]  # 计入 x-sum
                l.add(p)  # 放进 l
            else:  # 否则只能留在备选区
                r.add(p)  # 放进 r

        def remove(v: int):  # 把值 v 从所在集合中移除
            if cnt[v] == 0:  # 没出现过无需删除
                return  # 直接返回
            p = (cnt[v], v)  # 排序键
            if p in l:  # 它在 l 里
                nonlocal s  # 闭包内要给外层的 s 重新赋值
                s -= p[0] * p[1]  # 从 x-sum 扣除
                l.remove(p)  # 从 l 删除
            else:  # 否则它在 r 里
                r.remove(p)  # 从 r 删除

        l = SortedList()  # l：前 x 大的元素，按 (次数, 值) 升序存放
        r = SortedList()  # r：备选区，保存其余的 (次数, 值)
        cnt = Counter()  # 当前窗口内每个值的出现次数
        s = 0  # 当前窗口的 x-sum
        n = len(nums)  # 数组长度
        ans = [0] * (n - k + 1)  # 一共 n-k+1 个长度为 k 的窗口，答案数组按长度开好
        for i, v in enumerate(nums):  # 右指针 i 从左往右扫描
            remove(v)  # 先按旧次数把 v 从集合中摘下
            cnt[v] += 1  # 出现次数加一
            add(v)  # 再按新次数插回集合
            j = i - k + 1  # 窗口左端点 j = i-k+1
            if j < 0:  # 窗口还没凑满 k 个元素
                continue  # 不产生答案，直接进入下一轮
            while r and len(l) < x:  # 前 x 名不足时从备选区补
                p = r.pop()  # 弹出 r 中最大的元素
                l.add(p)  # 放入 l
                s += p[0] * p[1]  # 计入 x-sum
            while len(l) > x:  # 前 x 名超出个数
                p = l.pop(0)  # 弹出 l 中最小的元素
                s -= p[0] * p[1]  # 从 x-sum 扣除
                r.add(p)  # 退回备选区
            ans[j] = s  # 记录窗口 [j, i] 的 x-sum

            remove(nums[j])  # 把即将移出窗口的值摘下
            cnt[nums[j]] -= 1  # 出现次数减一
            add(nums[j])  # 按新次数插回集合
        return ans  # 返回所有长度为 k 的窗口的 x-sum
