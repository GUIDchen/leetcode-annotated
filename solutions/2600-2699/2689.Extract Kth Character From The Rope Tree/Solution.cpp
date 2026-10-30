// 题目：2689. 从 Rope 树中提取第 K 个字符（Extract Kth Character From The Rope Tree）
// 核心思路：对 Rope 树做深度优先遍历，按「左子树在前、右子树在后」的顺序把字符拼成一整串，再取下标 k-1 的字符。
// 时间复杂度：O(n)，n 为字符串总长，每个结点只访问一次（拼接带来额外的 O(n^2) 字符拷贝）；空间复杂度：O(n)，递归栈（O(树高)）与结果字符串。
/**
 * Definition for a rope tree node.
 * struct RopeTreeNode {
 *     int len;
 *     string val;
 *     RopeTreeNode *left;
 *     RopeTreeNode *right;
 *     RopeTreeNode() : len(0), val(""), left(nullptr), right(nullptr) {}
 *     RopeTreeNode(string s) : len(0), val(std::move(s)), left(nullptr), right(nullptr) {}
 *     RopeTreeNode(int x) : len(x), val(""), left(nullptr), right(nullptr) {}
 *     RopeTreeNode(int x, RopeTreeNode *left, RopeTreeNode *right) : len(x), val(""), left(left), right(right) {}
 * };
 */
// 结点语义：len == 0 表示叶子结点，val 里存着真实字符串；len > 0 表示内部结点，它的内容由左右子树按顺序拼接而成。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    char getKthCharacter(RopeTreeNode* root, int k) {  // root：Rope 树根结点；k：从 1 开始计数的第 k 个字符，返回值就是该字符
        function<string(RopeTreeNode * root)> dfs = [&](RopeTreeNode* root) -> string {  // 局部递归函数 dfs：返回以 root 为根的子树按顺序拼出的字符串
            if (root == nullptr) {  // 空结点不贡献任何字符
                return "";  // 空串是字符串拼接的单位元，直接返回不影响结果
            }
            if (root->len == 0) {  // len 为 0 说明是叶子结点，val 才是真正的字符串内容
                return root->val;  // 叶子结点直接给出自己保存的字符串
            }
            string left = dfs(root->left);  // 先递归拿到左子树拼成的字符串（左侧部分）
            string right = dfs(root->right);  // 再递归拿到右子树拼成的字符串（右侧部分）
            return left + right;  // Rope 树的中序语义：左子树的字符整体排在右子树之前
        };  // lambda 定义结束，把可调用对象装入 function
        return dfs(root)[k - 1];  // k 从 1 开始计数，转成 0 基下标后取字符；题目保证 1 <= k <= 总长度
    }
};