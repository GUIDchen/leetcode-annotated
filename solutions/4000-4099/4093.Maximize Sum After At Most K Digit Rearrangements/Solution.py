# 题目：4093. 至多 K 次数字重排后的最大和（Maximize Sum After At Most K Digit Rearrangements）
# 思路：先用辅助函数 f 把每个数的十进制数字降序重排，得到同位数下尽可能大的值 t[i]，重排收益就是 t[i] - nums[i]；把下标按收益降序排序，只给收益最大的前 k 个做重排（收益非负，用满 k 次不吃亏），其余保留原值，求和即为最大总和。
# 时间复杂度：O(n * 10 + n log n)，逐个拆位重排是每个数 O(10)，主要开销是排序；空间复杂度：O(n)，需要 t 与 ids 两个辅助数组。
class Solution:  # LeetCode 约定的题解类
    def maximizeSum(self, nums: list[int], k: int) -> int:  # nums：原始数组；k：至多可重排的元素个数；返回重排后的最大元素之和
        def f(x: int) -> int:  # 辅助函数：把 x 的十进制数字降序重排，得到同位数下尽量大的数
            cnt = [0] * 10  # cnt[d]：数字 d 在 x 的十进制表示中出现的次数
            while x:  # 逐位拆分 x
                x, v = divmod(x, 10)  # 同时得到去掉最低位后的商 x 与最低位数字 v
                cnt[v] += 1  # 该数字的出现次数加一
            y = 0  # y 用来拼出降序重排后的新数
            for i in range(9, -1, -1):  # 从大到小枚举数字，保证高位尽量大
                for _ in range(cnt[i]):  # 数字 i 出现几次就放几位
                    y = y * 10 + i  # 把数字 i 追加到 y 的末尾
            return y  # 返回重排后的最大数（x 为 0 时 y 也为 0，恰好正确）

        n = len(nums)  # n 是数组长度
        t = [f(x) for x in nums]  # t[i] 是 nums[i] 降序重排后的值
        ids = list(range(n))  # ids 存放待排序的下标
        ids.sort(key=lambda i: t[i] - nums[i], reverse=True)  # 按「重排收益」降序排列下标，收益大的排在前面
        return sum(t[ids[i]] if i < k else nums[ids[i]] for i in range(n))  # 前 k 个（收益最大）取重排后的值，其余取原值，求和即最大总和
