# 题目：2938. 区分黑球与白球（Separate Black and White Balls）
# 思路：把所有 1 挪到右边；从右往左数第 cnt 个 1 应落到位置 n-cnt，需要交换 (n-cnt)-i 次。
# 时间复杂度：O(n)，从右到左一次扫描；空间复杂度：O(1)，只用常数个计数器。
class Solution:  # LeetCode 约定的题解类
    def minimumSteps(self, s: str) -> int:  # s：由 '0'（白球）与 '1'（黑球）组成的字符串
        n = len(s)  # n：字符串长度
        ans = cnt = 0  # ans 累计交换次数；cnt 记录已扫描到的 1 的个数（Python 整数无溢出之忧）
        for i in range(n - 1, -1, -1):  # 从右往左扫描，最右边的 1 应留在最右边
            if s[i] == '1':  # 当前位置是黑球，需要往右挪
                cnt += 1  # 这是从右往左数的第 cnt 个 1
                ans += n - i - cnt  # 它最终应落在下标 n-cnt，与当前位置 i 的距离即交换次数
        return ans  # 返回最少交换次数
