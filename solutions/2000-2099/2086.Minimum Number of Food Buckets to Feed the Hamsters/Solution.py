# 题目：2086. 喂食仓鼠的最小食物桶数（Minimum Number of Food Buckets to Feed the Hamsters）
# 思路：贪心。一个桶最多喂左右两只仓鼠，所以遇到仓鼠优先在它右侧放桶（可顺带喂到下一只），右侧不行再看左侧是否已有桶可放，两边都不行说明无解。
# 时间复杂度：O(n)，n 为街道长度，只从左到右扫一遍；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minimumBuckets(self, street: str) -> int:  # street：只含 'H'（仓鼠）与 '.'（空地）的字符串；返回最少桶数，无解返回 -1
        ans = 0  # 累计需要的食物桶数
        i, n = 0, len(street)  # i 为扫描下标，n 为街道长度；用 while 是因为放桶后 i 需要跳跃
        while i < n:  # 扫描到街道末尾为止
            if street[i] == 'H':  # 只有仓鼠这一格才需要被喂食
                if i + 1 < n and street[i + 1] == '.':  # 优先把桶放在仓鼠右边：这一个桶还能顺带喂到右邻格的那只仓鼠
                    i += 2  # 右边这格放桶并喂饱当前仓鼠，直接跳过，避免重复统计
                    ans += 1  # 桶数加一
                elif i and street[i - 1] == '.':  # 右边不能放桶时，退而看左边是否已有桶或为空地
                    ans += 1  # 在左侧放一个桶，这个桶只能喂当前这一只仓鼠
                else:  # 左右两侧都无法放桶
                    return -1  # 当前仓鼠永远喂不到，题目无解
            i += 1  # 普通格子（或放桶后落回来的一格）继续往后扫描一格
        return ans  # 返回最少桶数
