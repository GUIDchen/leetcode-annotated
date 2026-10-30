# 题目：2078. 两栋颜色不同且距离最远的房子（Two Furthest Houses With Different Colors）
# 思路：首尾颜色不同则答案就是 n-1；否则分别从左侧、右侧找第一个与 colors[0] 不同的位置，取两者能形成的最大距离。
# 时间复杂度：O(n)，两个指针合起来最多扫一遍数组；空间复杂度：O(1)，只用了常数个下标变量。
class Solution:  # LeetCode 约定的题解类
    def maxDistance(self, colors: List[int]) -> int:  # colors 是每栋房子的颜色，返回最远的异色两栋的距离
        n = len(colors)  # 房子总数，后面用来换算下标距离
        if colors[0] != colors[-1]:  # 首尾颜色不同，整段首尾就是最远的一对
            return n - 1  # 0 号与 n-1 号的距离就是 n-1
        i, j = 1, n - 2  # 双指针：i 从左、j 从右向中间找异色位置
        while colors[i] == colors[0]:  # 跳过左端与首元素同色的房子
            i += 1  # 右移，停在第一个异色位置
        while colors[j] == colors[0]:  # 跳过右端与首元素同色的房子
            j -= 1  # 左移，停在最后一个异色位置
        return max(n - i - 1, j)  # i 到最右端（n-i-1）与最左端到 j（j）取较大者
