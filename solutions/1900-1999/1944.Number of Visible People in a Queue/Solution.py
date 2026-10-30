# 题目：1944. 队列中可以看到的人数（Number of Visible People in a Queue）
# 思路：从右往左遍历，维护从栈底到栈顶递减的单调栈；比当前人矮的出栈并各计一次可见，栈若还不空，栈顶那个更高的人再计一次。
# 时间复杂度：O(n)，每个身高最多入栈出栈一次；空间复杂度：O(n)。
class Solution:  # LeetCode 约定的题解类
    def canSeePersonsCount(self, heights: List[int]) -> List[int]:  # heights：每个人的身高，返回每人向右能看到的人数
        n = len(heights)  # n 是人数
        ans = [0] * n  # ans 初值全 0，逐位累加能看见的人数
        stk = []  # 单调栈，保存尚未被遮挡的身高，从栈底到栈顶递减
        for i in range(n - 1, -1, -1):  # 从右往左遍历，range 的第三个参数 -1 表示下标递减
            while stk and stk[-1] < heights[i]:  # 栈顶身高矮于当前人：看得见，并且会被当前人挡住
                ans[i] += 1  # 当前人能看到这一个
                stk.pop()  # 弹出它，继续看更靠右的下一个候选
            if stk:  # 栈里还有更高的人，当前人也能看到他，之后视线被挡住
                ans[i] += 1  # 再计一个可见
            stk.append(heights[i])  # 当前身高入栈，供更左边的人向右看时判断
        return ans  # 返回每个人看到的人数
