# 题目：3748. 统计稳定子数组的数目（Count Stable Subarrays）
# 核心思路：稳定子数组即非降序子数组，先把 nums 按降序断点切成若干非降序段，记录每段起点与「段内答案数」的前缀和；对每个查询用两次二分定位左右端点所属的段，同一段内直接算三角形数，跨段时用「左残段 + 中间整段前缀和之差 + 右残段」拼出答案。
# 复杂度：时间 O(n + q log n)，扫描一遍分段、每个查询两次二分；空间 O(n)，段起点数组与答案前缀和数组各占一份。
class Solution:  # LeetCode 约定的题解类
    def countStableSubarrays(  # 返回每个查询区间内稳定子数组的个数
        self, nums: List[int], queries: List[List[int]]  # nums 为原数组，queries 的每个元素是 [l, r]
    ) -> List[int]:  # 返回值为整数列表，第 k 项就是第 k 个查询的答案
        s = [0]  # s 是段内稳定子数组个数的前缀和，s[0] 为初值 0
        l, n = 0, len(nums)  # l 为当前非降序段左端点，n 为数组长度
        seg = []  # seg 记录每个非降序段的起始下标，起点天然递增，便于二分
        for r, x in enumerate(nums):  # r 为下标、x 为对应元素，从左到右扫描寻找段右端点
            if r == n - 1 or x > nums[r + 1]:  # 已到末尾，或出现降序断点，说明当前段在 r 处结束
                seg.append(l)  # 记下这一段的起始下标
                k = r - l + 1  # k 是这一段的长度
                s.append(s[-1] + (1 + k) * k // 2)  # 长度为 k 的段内共有 k(k+1)/2 个非降序子数组，累加进前缀和
                l = r + 1  # 下一段的左端点从 r+1 开始
        ans = []  # ans 按查询顺序收集答案
        for l, r in queries:  # 依次处理每个查询 [l, r]（此处的 l、r 覆盖了上面的同名变量）
            i = bisect_right(seg, l)  # i 是第一个起点大于 l 的段下标，说明 l 落在第 i-1 段里
            j = bisect_right(seg, r) - 1  # j 是最后一个起点不大于 r 的段下标，说明 r 落在第 j 段里
            if i > j:  # i > j 说明整个查询区间落在同一段内，完全非降序
                k = r - l + 1  # k 是查询区间的长度
                ans.append((1 + k) * k // 2)  # 区间内任意子数组都稳定，共 k(k+1)/2 个
            else:  # 否则区间跨越多个段，拆成左残段、中间整段、右残段
                a = seg[i] - l  # a 是左端残段的长度（从 l 到第 i 段起点之前）
                b = r - seg[j] + 1  # b 是右端残段的长度（从第 j 段起点到 r）
                ans.append((1 + a) * a // 2 + s[j] - s[i] + (1 + b) * b // 2)  # 三段各自的三角形数相加，中间整段用前缀和之差得到
        return ans  # 返回每个查询对应的稳定子数组个数
