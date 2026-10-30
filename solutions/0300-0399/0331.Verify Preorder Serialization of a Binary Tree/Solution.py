# 题目：331. 验证二叉树的前序序列化（Verify Preorder Serialization of a Binary Tree）
# 思路：用栈消解序列；每读一个 token 入栈，一旦出现「非空节点 + # + #」就把这棵子树折叠成一个 #，最后栈里只剩一个 # 即合法。
# 时间复杂度：O(n)，每个节点最多入栈出栈各常数次；空间复杂度：O(n)，栈的最大深度。
class Solution:    # LeetCode 约定的题解类
    def isValidSerialization(self, preorder: str) -> bool:    # preorder：逗号分隔的前序序列字符串，返回它是否是合法的二叉树序列化
        stk = []    # 栈：保存还没被消解的节点
        for c in preorder.split(","):    # 按 ',' 切分并逐个 token 处理
            stk.append(c)    # 先把当前 token 压栈
            while len(stk) > 2 and stk[-1] == stk[-2] == "#" and stk[-3] != "#":    # 栈顶是「非空节点 + "#" + "#"」时，这棵子树已合法，可折叠成一个空槽
                stk = stk[:-3]    # 切掉栈顶的三个元素
                stk.append("#")    # 用一个 "#" 代替整棵已合法的子树
        return len(stk) == 1 and stk[0] == "#"    # 最后栈里恰好只剩一个 "#" 才说明整棵树合法
