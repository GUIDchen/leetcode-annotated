# 题目：1850. 邻位交换的最小次数（Minimum Adjacent Swaps to Reach the Kth Smallest Number）
# 思路：手写下一个排列求出第 k 个最小数，再把目标串每位映射回原串下标，逆序对数就是最少相邻交换次数。
# 时间复杂度：O(k·n + n^2)，求排列 O(k·n)、统计逆序对 O(n^2)；空间复杂度：O(n)，要存映射与指针数组。
class Solution:  # LeetCode 约定的题解类
    def getMinSwaps(self, num: str, k: int) -> int:  # num：数字字符串；k：要到达的是第 k 个更大的最小数
        def next_permutation(nums: List[str]) -> bool:  # 手写的下一个排列：把 nums 原地改成字典序下一个更大排列，已是最大则返回 False
            n = len(nums)  # 字符个数
            i = n - 2  # 从倒数第二个位置开始找第一处“升序”断点
            while i >= 0 and nums[i] >= nums[i + 1]:  # 只要右边不比左边大就继续往左找
                i -= 1  # 指针左移
            if i < 0:  # 找不到升序断点，说明已经是最大排列
                return False  # 返回 False 表示无法再变大
            j = n - 1  # 从最右端找第一个大于断点字符的位置
            while j >= 0 and nums[j] <= nums[i]:  # 跳过所有不大于 nums[i] 的字符
                j -= 1  # 指针左移
            nums[i], nums[j] = nums[j], nums[i]  # 交换断点字符与右侧刚好更大的字符
            nums[i + 1 : n] = nums[i + 1 : n][::-1]  # 把断点之后的后缀反转成升序，保证是“最小的”下一个排列
            return True  # 成功推进到下一个排列

        s = list(num)  # 转成列表，字符可原地交换
        for _ in range(k):  # 连续求 k 次下一个排列，得到第 k 个最小数
            next_permutation(s)  # 推进一次
        d = [[] for _ in range(10)]  # 10 个桶，按数字 0~9 记录它在原串中出现的位置
        idx = [0] * 10  # 每个数字下一个待配对位置的指针
        n = len(s)  # 字符串长度
        for i, c in enumerate(num):  # 统计原串每个字符的出现下标
            j = ord(c) - ord("0")  # 字符转成 0~9 的数字下标
            d[j].append(i)  # 记录该数字的一次出现位置
        arr = [0] * n  # arr[i] 记录目标串第 i 位对应的原串下标
        for i, c in enumerate(s):  # 逐位建立目标串到原串下标的映射
            j = ord(c) - ord("0")  # 当前字符对应的数字
            arr[i] = d[j][idx[j]]  # 同数字按下标从小到大依次配对
            idx[j] += 1  # 该数字的指针后移，供下一次配对使用
        return sum(arr[j] > arr[i] for i in range(n) for j in range(i))  # 逆序对总数即最少相邻交换次数（后出现的更小下标都被算作逆序对）
