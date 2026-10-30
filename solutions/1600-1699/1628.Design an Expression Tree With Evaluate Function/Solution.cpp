// 题目：1628. 设计带解析函数的表达式树（Design an Expression Tree With Evaluate Function）
// 思路：实现题面给出的 Node 接口，再用栈按后缀表达式建树，运算符弹两个操作数作左右子树，求值时递归计算左右子树再按运算符合并。
// 时间复杂度：建树 O(n)，单次求值 O(n)；空间复杂度：O(n)，栈与树节点。
/**
 * This is the interface for the expression tree Node.
 * You should not remove it, and you can define some classes to implement it.
 */

class Node {  // 题面给定的表达式树节点接口
public:  // public:
    virtual ~Node(){};  // 虚析构函数，保证通过基类指针删除子类对象时能正确析构
    virtual int evaluate() const = 0;  // 纯虚函数：求值接口，由子类实现

protected:  // protected:
    // define your fields here
    string val;  // 节点内容：数字字符串或四则运算符
    Node* left;  // 左子树指针
    Node* right;  // 右子树指针
};  // 接口定义结束

class MyNode : public Node {  // 自己实现的节点类，继承题面给定的接口
public:  // public:
    MyNode(string val) {  // 叶子节点构造函数（只有值）
        this->val = val;  // 保存节点内容
    }  // 构造函数结束

    MyNode(string val, Node* left, Node* right) {  // 运算符节点构造函数：需要左右子树
        this->val = val;  // 保存运算符
        this->left = left;  // 挂上左子树
        this->right = right;  // 挂上右子树
    }  // 构造函数结束

    int evaluate() const {  // 递归求值
        if (!(val == "+" || val == "-" || val == "*" || val == "/")) return stoi(val);  // 不是四则运算符就当作数字，用 stoi 转成整数
        auto leftVal = left->evaluate(), rightVal = right->evaluate();  // 先递归求出左右子树的值
        if (val == "+") return leftVal + rightVal;  // 加法
        if (val == "-") return leftVal - rightVal;  // 减法
        if (val == "*") return leftVal * rightVal;  // 乘法
        if (val == "/") return leftVal / rightVal;  // 除法（题目保证合法）
        return 0;  // 兜底返回，正常不会执行到（只为消除编译告警）
    }  // evaluate 结束
};  // MyNode 类定义结束

/**
 * This is the TreeBuilder class.
 * You can treat it as the driver code that takes the postinfix input
 * and returns the expression tree represnting it as a Node.
 */

class TreeBuilder {  // 由后缀表达式构建表达式树的类
public:  // public:
    Node* buildTree(vector<string>& postfix) {  // postfix 是后缀表达式 token 列表，返回整棵树的根节点
        stack<MyNode*> stk;  // 栈：保存已经建好的子树根
        for (auto s : postfix) {  // 逐个处理后缀表达式中的 token
            MyNode* node;  // 当前 token 对应的节点
            if (s == "+" || s == "-" || s == "*" || s == "/") {  // 运算符：需要从栈中弹出两个操作数
                auto right = stk.top();  // 后缀表达式里先出现的是右操作数，所以栈顶是右子树
                stk.pop();  // 弹出右操作数
                auto left = stk.top();  // 再取左操作数
                stk.pop();  // 弹出左操作数
                node = new MyNode(s, left, right);  // 用运算符和左右子树构造内部节点
            } else {  // 否则是数字
                node = new MyNode(s);  // 数字直接建叶子节点
            }  // if 分支结束
            stk.push(node);  // 把新子树压栈，供上层的运算符使用
        }  // 遍历结束
        return stk.top();  // 栈中唯一剩下的节点就是整棵树的根
    }  // buildTree 结束
};  // TreeBuilder 类定义结束

/**
 * Your TreeBuilder object will be instantiated and called as such:
 * TreeBuilder* obj = new TreeBuilder();
 * Node* expTree = obj->buildTree(postfix);
 * int ans = expTree->evaluate();
 */