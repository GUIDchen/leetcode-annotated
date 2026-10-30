# 题目：3551. 数位和排序需要的最小交换次数（Minimum Swaps to Sort by Digit Sum）
# 思路：把每个元素换成键 (数位和, 数值) 并排序得到目标排列；记录每个数值的目标下标，把“原下标 → 目标下标”的映射拆成若干置换环，长度 L 的环需要 L-1 次交换，故答案为 n 减去环的个数。
# 时间复杂度：O(n log n)，排序主导，环的遍历是 O(n)；空间复杂度：O(n)，存放键数组、位置表和访问标记。
class Solution:  # LeetCode 约定的题解类
    def minSwaps(self, nums: List[int]) -> int:  # 返回把数组按（数位和，数值）升序排好所需的最小交换次数
        def f(x: int) -> int:  # f：计算整数 x 的十进制数位和
            s = 0  # s：累计数位和
            while x:  # 逐位拆分，直到 x 为 0
                s += x % 10  # 累加最低位上的数字
                x //= 10  # 整除去掉最低位，继续处理更高位
            return s  # 返回数位和

        n = len(nums)  # n：数组长度
        arr = sorted((f(x), x) for x in nums)  # 按（数位和，数值）升序排序，得到目标顺序
        d = {a[1]: i for i, a in enumerate(arr)}  # d：数值 -> 它在目标顺序中的下标位置
        ans = n  # ans 初值取 n，每识别出一个置换环就减 1，最终等于 n 减去环的个数
        vis = [False] * n  # vis：目标位置是否已被访问
        for i in range(n):  # 枚举每个起点位置
            if not vis[i]:  # 尚未访问，说明进入了一个新的置换环
                ans -= 1  # 长度为 L 的环只需 L-1 次交换，这里先统一扣掉一份
                j = i  # j：环内的游标位置
                while not vis[j]:  # 沿置换关系走一圈，直到回到已访问位置
                    vis[j] = True  # 标记该位置已访问
                    j = d[nums[j]]  # nums[j] 的目标下标就是置换关系中的下一个节点
        return ans  # 交换次数 = Σ(环长-1) = n - 环的个数
