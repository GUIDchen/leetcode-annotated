// 题目：331. 验证二叉树的前序序列化（Verify Preorder Serialization of a Binary Tree）
// 思路：用栈消解序列；每读一个 token 入栈，一旦出现「非空节点 + # + #」就把这棵子树折叠成一个 #，最后栈里只剩一个 # 即合法。
// 时间复杂度：O(n)，每个节点最多入栈出栈各常数次；空间复杂度：O(n)，栈的最大深度。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isValidSerialization(string preorder) {  // preorder：逗号分隔的前序序列字符串，返回它是否是合法的二叉树序列化
        vector<string> stk;  // 用栈保存还没被消解的节点
        stringstream ss(preorder);  // 把字符串包成 stringstream，便于按 ',' 切分
        string s;  // 存放当前切出来的一个节点
        while (getline(ss, s, ',')) {  // 逐个 token 读取：getline 以 ',' 为分隔符
            stk.push_back(s);  // 先无脑压栈
            while (stk.size() >= 3 && stk[stk.size() - 1] == "#" && stk[stk.size() - 2] == "#" && stk[stk.size() - 3] != "#") {  // 栈顶出现「非空节点 + 两个空孩子」时，这棵子树已合法，可整体折叠成一个空槽
                stk.pop_back();  // 弹出右空孩子
                stk.pop_back();  // 弹出左空孩子
                stk.pop_back();  // 弹出这个非空节点
                stk.push_back("#");  // 用单个 "#" 代替这棵已合法的子树
            }  // 折叠循环结束：继续检查新的栈顶是否还能合并
        }  // 读取循环结束
        return stk.size() == 1 && stk[0] == "#";  // 最后栈里恰好只剩一个 "#" 才说明整棵树合法
    }  // 方法结束
};  // 类结束