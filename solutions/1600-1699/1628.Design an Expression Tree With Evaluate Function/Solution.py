# 题目：1628. 设计带解析函数的表达式树（Design an Expression Tree With Evaluate Function）
# 思路：实现题面给出的 Node 接口，再用栈按后缀表达式建树，运算符弹两个操作数作左右子树，求值时递归计算左右子树再按运算符合并。
# 时间复杂度：建树 O(n)，单次求值 O(n)；空间复杂度：O(n)，栈与树节点。
import abc  # 导入 abc 模块（题面接口已给出，保持原样）
from abc import ABC, abstractmethod  # 导入抽象基类与抽象方法装饰器

# 题面给定的表达式树 Node 接口说明（原文保留在下方字符串中）
"""
This is the interface for the expression tree Node.
You should not remove it, and you can define some classes to implement it.
"""


class Node(ABC):  # 抽象基类：表达式树节点接口
    @abstractmethod  # 声明为抽象方法，子类必须实现
    # define your fields here
    def evaluate(self) -> int:  # 求值接口
        pass  # 抽象方法无需实现，用 pass 占位


class MyNode(Node):  # 自己实现的节点类，继承题面给定的接口
    def __init__(self, val):  # 构造函数：val 为数字字符串或四则运算符
        self.val = val  # 保存节点内容
        self.left = None  # 左子树初始为空
        self.right = None  # 右子树初始为空

    def evaluate(self) -> int:  # 递归求值
        x = self.val  # 先取出当前节点内容，后面要反复用
        if x.isdigit():  # 内容是数字字符串
            return int(x)  # 转成整数直接返回，作为叶子值

        left, right = self.left.evaluate(), self.right.evaluate()  # 否则是运算符，先递归求左右子树的值
        if x == '+':  # 加法
            return left + right  # 返回两数之和
        if x == '-':  # 减法
            return left - right  # 返回两数之差
        if x == '*':  # 乘法
            return left * right  # 返回两数之积
        if x == '/':  # 除法
            return left // right  # 题目保证整除，用整除 // 得到整数结果


# TreeBuilder 的职责说明（原文保留在下方字符串中）
"""
This is the TreeBuilder class.
You can treat it as the driver code that takes the postinfix input
and returns the expression tree represnting it as a Node.
"""


class TreeBuilder(object):  # 由后缀表达式构建表达式树的类
    def buildTree(self, postfix: List[str]) -> 'Node':  # postfix 为后缀表达式 token 列表，返回整棵树的根节点
        stk = []  # 用栈保存已经建好的子树
        for s in postfix:  # 逐个处理后缀表达式中的 token
            node = MyNode(s)  # 先按当前 token 建一个节点
            if not s.isdigit():  # 不是数字说明是运算符，需要两个操作数
                node.right = stk.pop()  # 栈顶是右操作数
                node.left = stk.pop()  # 再弹出的是左操作数
            stk.append(node)  # 把新子树压栈，供上层的运算符使用
        return stk[-1]  # 栈中只剩整棵树的根，取栈顶返回


# 题面给出的调用方式示例（原文保留在下方字符串中）
"""
Your TreeBuilder object will be instantiated and called as such:
obj = TreeBuilder();
expTree = obj.buildTree(postfix);
ans = expTree.evaluate();
"""
