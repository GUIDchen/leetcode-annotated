# 题目：3321. 计算子数组的 x-sum II（Find X-Sum of All K-Long Subarrays II）
# 思路：滑动窗口 + 两个 SortedList 对顶。l 维护窗口内按 (出现次数, 值) 排序的前 x 个元素，r 存其余元素，s 维护 l 中 次数×值 的和；
# 每次滑动先把进出窗口的元素从结构中删除再按新次数加回，并把 len(l) 调回 x。时间复杂度：O(n log n)；空间复杂度：O(n)。
class Solution:  # LeetCode 约定的题解类
    def findXSum(self, nums: List[int], k: int, x: int) -> List[int]:  # nums：输入数组；k：窗口长度；x：每个窗口取前 x 个元素
        def add(v: int):  # 把值 v 按它当前的 (次数, 值) 插入 l 或 r
            if cnt[v] == 0:  # 次数为 0 说明 v 不在窗口内
                return  # 无需插入，直接返回
            p = (cnt[v], v)  # (出现次数, 值) 二元组；元组的字典序比较正是题目要求的排序规则
            if l and p > l[0]:  # 比 l 中最小元素还大，说明它应当进入前 x 大
                nonlocal s  # 声明 s 来自外层作用域，这里要修改它
                s += p[0] * p[1]  # 计入 x-sum
                l.add(p)  # 放进 l
            else:  # 否则先放进 r 备用
                r.add(p)  # 否则先放进 r 备用

        def remove(v: int):  # 把值 v 当前的 (次数, 值) 从结构中删除
            if cnt[v] == 0:  # 次数为 0 说明结构里没有它
                return  # 直接返回
            p = (cnt[v], v)  # 用与插入时完全相同的二元组去查找
            if p in l:  # 判断它是否在 l 中
                nonlocal s  # 声明 s 来自外层作用域，这里要修改它
                s -= p[0] * p[1]  # 从 x-sum 中扣掉它的贡献
                l.remove(p)  # 从 l 中删除
            else:  # 不在 l 中，说明它一定在 r 中
                r.remove(p)  # 不在 l 就必然在 r，从 r 中删除

        l = SortedList()  # 有序列表：贡献 x-sum 的前 x 大元素
        r = SortedList()  # 有序列表：被挤出的剩余元素
        cnt = Counter()  # 窗口内每个元素值的出现次数
        s = 0  # l 中所有元素的 次数×值 之和，也就是答案
        n = len(nums)  # 数组长度，用于预先分配答案数组
        ans = [0] * (n - k + 1)  # 每个长度为 k 的窗口一个答案
        for i, v in enumerate(nums):  # 右端点 i 逐个扩张窗口
            remove(v)  # 先删掉 v 旧的 (次数, 值)
            cnt[v] += 1  # v 的出现次数 +1
            add(v)  # 再按新的次数重新插入
            j = i - k + 1  # 窗口左端点
            if j < 0:  # 窗口元素还不足 k 个
                continue  # 先不统计答案
            while r and len(l) < x:  # l 不足 x 个时，从 r 中补进最大的元素
                p = r.pop()  # 弹出 r 中的最大元素（次数多、值大者优先）
                l.add(p)  # 加入 l
                s += p[0] * p[1]  # 补进 x-sum
            while len(l) > x:  # l 超过 x 个时，把最小的挤回 r
                p = l.pop(0)  # 弹出 l 中的最小元素
                s -= p[0] * p[1]  # 从 x-sum 中扣掉
                r.add(p)  # 放回 r
            ans[j] = s  # 记录答案，下标就是窗口左端点

            remove(nums[j])  # 左端点即将滑出窗口，先移除它的旧二元组
            cnt[nums[j]] -= 1  # 它的出现次数 -1
            add(nums[j])  # 次数还不为 0 就按新次数插回结构
        return ans  # 返回所有窗口的答案
