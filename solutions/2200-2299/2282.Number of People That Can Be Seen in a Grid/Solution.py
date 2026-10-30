# 题目：2282. 在一个网格中可以看到的人数（Number of People That Can Be Seen in a Grid）
# 核心思路：用同一个单调栈函数分别处理每一行与每一列，从右往左扫描，数出每个人向右/向下的可见人数后相加。
# 时间复杂度：O(mn)，每行每列各扫一次且每个元素最多进出栈一次；空间复杂度：O(mn)，答案矩阵与栈等辅助开销。
class Solution:  # LeetCode 约定的题解类
    def seePeople(self, heights: List[List[int]]) -> List[List[int]]:  # heights：网格中每个格子上的人的身高
        def f(nums: List[int]) -> List[int]:  # 内部函数：处理一条一维序列，返回每个位置在单一方向上的可见人数
            n = len(nums)  # 序列长度
            stk = []  # 单调递减栈：保存从右往左扫描时还没被完全遮住的身高
            ans = [0] * n  # 每个位置的可见人数，初始全为 0
            for i in range(n - 1, -1, -1):  # 从右往左扫描，保证右边的情况已经处理完
                while stk and stk[-1] < nums[i]:  # 栈顶比当前身高矮，这个人一定看得见
                    ans[i] += 1  # 记一次可见
                    stk.pop()  # 更矮的人被当前身高完全挡住，左侧的人再也看不到他
                if stk:  # 矮的都弹完了，栈顶是最近的、不低于自己且未被遮挡的人
                    ans[i] += 1  # 这一个人也能看见
                while stk and stk[-1] == nums[i]:  # 身高相同的人会相互遮挡，只应计一次
                    stk.pop()  # 弹出相等身高，避免同一个人被重复统计
                stk.append(nums[i])  # 当前身高入栈，继续阻挡随后从左边看过来的人
            return ans  # 返回这条序列每个位置的可见人数

        ans = [f(row) for row in heights]  # 先按行统计：每行向右能看见的人数
        m, n = len(heights), len(heights[0])  # 网格的行数与列数
        for j in range(n):  # 再按列统计：每列向下能看见的人数
            add = f([heights[i][j] for i in range(m)])  # 抽出第 j 列拼成一维序列，复用同一个函数求向下可见人数
            for i in range(m):  # 把列方向的结果合并进答案
                ans[i][j] += add[i]  # 行方向 + 列方向 = 该格的总可见人数
        return ans  # 返回最终矩阵
