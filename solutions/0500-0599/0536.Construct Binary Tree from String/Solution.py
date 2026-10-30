# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
# 题目：536. 从字符串生成二叉树（Construct Binary Tree from String）
# 思路：先取括号前的数字当根，再用括号计数（遇 '(' 加一、遇 ')' 减一）切出两段完整的子树串，第一段是左孩子，第二段是右孩子。
# 时间复杂度：O(n^2)，每层递归都重新切片并重新扫描；空间复杂度：O(n)，递归栈与构造出的树。
class Solution:  # LeetCode 约定的题解类
    def str2tree(self, s: str) -> TreeNode:  # s 是形如 "4(2(3)(1))(6(5))" 的字符串
        def dfs(s):  # 把一段字符串递归构造成子树
            if not s:  # 空串对应空子树，是递归出口
                return None  # 返回空节点
            p = s.find('(')  # 找第一个左括号，它前面就是根节点的数字
            if p == -1:  # 整串没有括号，说明是叶子
                return TreeNode(int(s))  # 直接把这个数字建成叶子节点
            root = TreeNode(int(s[:p]))  # 括号前那段数字转整数，作为当前子树的根
            start = p  # start 记录当前待切子串的左括号位置，初始指向第一个括号
            cnt = 0  # 括号计数器，用来判断一段括号是否已经闭合完整
            for i in range(p, len(s)):  # 从第一个括号开始向后扫描
                if s[i] == '(':  # 遇到左括号
                    cnt += 1  # 未匹配的括号数加一
                elif s[i] == ')':  # 遇到右括号
                    cnt -= 1  # 未匹配的括号数减一
                if cnt == 0:  # 计数归零说明从 start 到 i 这一段括号已配平
                    if start == p:  # 还是第一次闭合，这是左孩子那一段
                        root.left = dfs(s[start + 1 : i])  # 去掉最外层括号，递归构造左子树
                        start = i + 1  # 下一段的起点挪到右括号之后
                    else:  # 不是第一次闭合，这一段属于右孩子
                        root.right = dfs(s[start + 1 : i])  # 同样去掉外层括号，递归构造右子树
            return root  # 返回构造好的当前子树

        return dfs(s)  # 从整串开始递归构造并返回整棵树的根
