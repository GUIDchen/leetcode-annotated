# 题目：1187. 使数组严格递增（Make Array Strictly Increasing）
# 思路：arr2 排序后原地去重，arr1 两端加 ±inf 哨兵，用 f[i] 表示「i 保留原值」时的最少替换数，转移时枚举 i 前面整段替换的长度 k。
# 时间复杂度：O(n·m + m log m)，m 为 arr2 长度；空间复杂度：O(n + m)。
class Solution:  # LeetCode 约定的题解类
    def makeArrayIncreasing(self, arr1: List[int], arr2: List[int]) -> int:  # arr1 的元素可用 arr2 中的值替换，返回使 arr1 严格递增的最少替换次数
        arr2.sort()  # 排序：为去重和二分做准备
        m = 0  # m 记录去重后已经写入的个数
        for x in arr2:  # 原地去重，避免额外分配
            if m == 0 or x != arr2[m - 1]:  # 第一个元素无条件保留，其余只保留与上一个不同的值
                arr2[m] = x  # 把不重复的值写到去重后的位置
                m += 1  # 去重长度加一
        arr2 = arr2[:m]  # 截断，只留下前 m 个不重复的值
        arr = [-inf] + arr1 + [inf]  # 两端加哨兵：-inf 统一「整段前缀被替换」的转移起点，+inf 作为最终答案位置
        n = len(arr)  # 加哨兵后的长度
        f = [inf] * n  # f[i]：以 i 结尾、且 i 保留原值时使前缀严格递增的最少替换数
        f[0] = 0  # 头哨兵不需要替换
        for i in range(1, n):  # 按位置依次递推
            if arr[i - 1] < arr[i]:  # 情况一：前一个位置也保留原值且天然有序
                f[i] = f[i - 1]  # 无需新替换，直接继承
            # 也可以把 i 前面连续的 k 个位置整段替换：取 arr2 中最大的 k 个小于 arr[i] 的值
            # （即 arr2[j-k .. j-1]），这样只需检查 arr[i-k-1] 是否小于 arr2[j-k]。
            j = bisect_left(arr2, arr[i])  # j：arr2 中小于 arr[i] 的元素个数，即最多能放几个替换值
            for k in range(1, min(i - 1, j) + 1):  # 枚举 i 前面被连续替换的长度 k，受已有个数与备选值个数双重限制
                if arr[i - k - 1] < arr2[j - k]:  # 替换块前一个保留值必须小于替换块最小值，才能严格递增
                    f[i] = min(f[i], f[i - k - 1] + k)  # 代价 = 前面位置的代价 + 本段替换的 k 个
        return -1 if f[n - 1] >= inf else f[n - 1]  # 尾哨兵不可达说明无解，返回 -1
