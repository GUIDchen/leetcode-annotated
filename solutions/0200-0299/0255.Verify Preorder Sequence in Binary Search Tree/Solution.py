# 题目：255. 验证二叉搜索树的前序遍历序列（Verify Preorder Sequence in Binary Search Tree）
# 思路：单调栈。last 是已经回溯过的祖先最大值，作为当前值的下界；用递减栈模拟前序下降，遇到更大值时弹栈更新 last。
# 时间复杂度：O(n)，每个元素至多入栈、出栈一次；空间复杂度：O(n)，栈最多保存 n 个节点值。

class Solution:  # LeetCode 约定的题解类
    def verifyPreorder(self, preorder: List[int]) -> bool:  # preorder：待验证的前序序列
        stk = []  # 单调栈：保存从根到当前节点的路径，值从栈底到栈顶递减
        last = -inf  # last：已出栈祖先中的最大值，作为下界（-inf 表示尚未有下界）
        for x in preorder:  # 按前序顺序扫描每个节点值
            if x < last:  # 小于下界，说明落在右子树里却不够大，违反 BST 性质
                return False  # 序列非法，直接返回 False
            while stk and stk[-1] < x:  # 当前值更大：栈顶节点的左子树结束，转而进入其右子树
                last = stk.pop()  # 弹出栈顶并把它记为新的下界
            stk.append(x)  # 当前节点入栈，继续深入它的左子树
        return True  # 全部元素都满足约束，序列合法
