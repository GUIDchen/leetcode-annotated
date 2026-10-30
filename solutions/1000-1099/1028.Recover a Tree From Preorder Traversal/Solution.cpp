// 题目：1028. 从先序遍历还原二叉树（Recover a Tree From Preorder Traversal）
// 思路：串中 '-' 的个数就是节点深度，用栈维护当前祖先路径，每凑齐一个数字就按深度弹栈并把新节点挂到栈顶的左右空位。
// 时间复杂度：O(n)，每个字符与每个节点各处理一次；空间复杂度：O(n)，栈与新建节点合计线性规模。
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    TreeNode* recoverFromPreorder(string S) {  // S：先序遍历串，数字是节点值，数字前的 '-' 个数是该节点的深度
        stack<TreeNode*> st;  // 栈保存当前路径上的祖先节点，栈的大小恰好等于「已建成部分」的深度
        int depth = 0;  // 正在累计的 '-' 个数，即下一个节点的深度
        int num = 0;  // 正在累计的节点值（值可能有多位，需要逐位拼接）
        for (int i = 0; i < S.length(); ++i) {  // 从左到右逐字符扫描整个先序串
            if (S[i] == '-') {  // 遇到分隔符 '-'，说明深度计数要加一
                depth++;  // 深度加一，记录即将出现的节点位于第几层
            } else {  // 否则该字符是数字，把它并入当前节点值
                num = 10 * num + S[i] - '0';  // 十进制逐位累加：num * 10 左移一位再加上新数字
            }  // 字符已按「分隔符 / 数字」分类处理完毕
            if (i + 1 >= S.length() || (isdigit(S[i]) && S[i + 1] == '-')) {  // 数字已经读完：串尾，或者下一个字符是 '-' 表示要进入新节点
                TreeNode* newNode = new TreeNode(num);  // 按累计好的值创建当前节点
                while (st.size() > depth) {  // 栈太深说明上一条分支已经走完，弹出到当前深度的父节点为止
                    st.pop();  // 弹出不属于当前路径的节点，保证栈顶就是父节点
                }  // 循环结束，此时 st.size() <= depth
                if (!st.empty()) {  // 栈非空说明当前节点有父节点（整个串的第一个节点是根，入栈前栈为空）
                    if (st.top()->left == nullptr) {  // 先序遍历先填左孩子，左孩子为空就接到左边
                        st.top()->left = newNode;  // 把新节点挂为左孩子
                    } else {  // 左孩子已经有节点，说明左子树已建成
                        st.top()->right = newNode;  // 只能把新节点挂为右孩子
                    }  // 分支结束
                }  // 挂接完成
                st.push(newNode);  // 新节点入栈，成为后续更深层节点的候选父节点
                depth = 0;  // 深度计数清零，为下一个节点重新统计 '-'
                num = 0;  // 节点值清零，避免影响下一个节点的数值
            }  // 单个节点处理完毕
        }  // 遍历结束，整棵树已经建好
        TreeNode* res;  // 用来取出栈底节点：最后被弹出的那个就是整棵树的根
        while (!st.empty()) {  // 把保存路径的栈彻底弹空
            res = st.top();  // 每轮记下当前栈顶，循环结束时 res 恰为最后弹出的元素
            st.pop();  // 弹出当前栈顶
        }  // 循环结束
        return res;  // 返回整棵树的根节点
    }  // 方法结束
};  // 类定义结束