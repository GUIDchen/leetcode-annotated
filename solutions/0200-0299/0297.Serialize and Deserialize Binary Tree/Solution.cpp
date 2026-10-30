// 题目：297. 二叉树的序列化与反序列化（Serialize and Deserialize Binary Tree）
// 思路：层序（BFS）编码，空结点记为 #、结点值后跟空格；反序列化时用同一层序队列逐个给父结点补左右孩子。
// 时间复杂度：O(n)，每个结点进出队列各一次；空间复杂度：O(n)，队列与结果字符串最多存 n 个结点。
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {  // Codec：负责树的序列化与反序列化
public:  // 对外接口
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {  // root：树根；返回层序编码后的字符串
        if (!root) {  // 空树需要单独处理
            return "";  // 空树编码为空串
        }  // if 块结束
        queue<TreeNode*> q{{root}};  // 层序（BFS）队列，初始只有根结点
        string ans;  // 结果字符串，各结点之间用空格分隔
        while (!q.empty()) {  // 队列非空就继续层序遍历
            auto node = q.front();  // 取出队首结点（可能为空指针）
            q.pop();  // 弹出队首
            if (node) {  // 是真实结点
                ans += to_string(node->val) + " ";  // 写入结点值并补一个空格作为分隔符
                q.push(node->left);  // 左孩子入队（可能为 nullptr，也要入队占位）
                q.push(node->right);  // 右孩子入队（可能为 nullptr，也要入队占位）
            } else {  // 空结点用 # 占位
                ans += "# ";  // 写入空标记
            }  // if/else 结束
        }  // while 循环结束
        ans.pop_back();  // 去掉末尾多余的一个空格
        return ans;  // 返回编码后的字符串
    }  // serialize 结束

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {  // data：编码字符串；返回重建出的树根
        if (data == "") {  // 空串对应空树
            return nullptr;  // 返回空树
        }  // if 块结束
        stringstream ss(data);  // 用字符串流按空格切分 token
        string t;  // 当前读到的 token
        ss >> t;  // 先读出根结点的 token
        TreeNode* root = new TreeNode(stoi(t));  // 用根结点的值建树
        queue<TreeNode*> q{{root}};  // 层序队列，保存待补孩子的结点
        while (!q.empty()) {  // 逐个结点补左右孩子
            auto node = q.front();  // 取出队首父结点
            q.pop();  // 弹出队首
            ss >> t;  // 读左孩子的 token
            if (t != "#") {  // 左孩子非空
                node->left = new TreeNode(stoi(t));  // 新建左孩子挂到父结点上
                q.push(node->left);  // 左孩子入队，等待补它自己的孩子
            }  // if 块结束
            ss >> t;  // 读右孩子的 token
            if (t != "#") {  // 右孩子非空
                node->right = new TreeNode(stoi(t));  // 新建右孩子挂到父结点上
                q.push(node->right);  // 右孩子入队，等待补它自己的孩子
            }  // if 块结束
        }  // while 循环结束
        return root;  // 返回重建好的树根
    }  // deserialize 结束
};  // 类定义结束

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));