// 题目：449. 序列化和反序列化二叉搜索树（Serialize and Deserialize BST）
// 思路：先序遍历序列配合 BST 的值域约束即可唯一还原——serialize 输出先序值串，deserialize 用 (mi, mx) 开区间逐个认领结点。
// 时间复杂度：O(n)，序列化遍历一次、反序列化每个值只消费一次；空间复杂度：O(n)，存值数组与递归栈。
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {  // 序列化 / 反序列化二叉搜索树的编解码器
public:  // 编解码接口对外可见
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {  // root：待序列化的 BST 根结点；返回空格分隔的先序遍历值串
        if (!root) {  // 空树：LeetCode 约定用空字符串表示
            return "";  // 返回空串，反序列化时据此还原成空指针
        }  // 结束空树判断
        string data = "";  // 收集先序遍历的结点值，每一项后面都会补一个空格
        function<void(TreeNode*)> dfs = [&](TreeNode* root) {  // 递归 lambda：用先序 DFS 把结点值写入 data（按引用捕获 data 自身）
            if (!root) {  // 递归出口：遇到空结点
                return;  // 直接返回，不写入任何值
            }  // 结束递归出口判断
            data += to_string(root->val) + " ";  // 先访问根：写入结点值并用空格分隔，便于之后按空格切分
            dfs(root->left);  // 再递归左子树
            dfs(root->right);  // 最后递归右子树
        };  // 结束递归 lambda 的定义
        dfs(root);  // 从根结点启动先序遍历
        data.pop_back();  // 去掉末尾多写的那个空格，得到规整的编码串
        return data;  // 返回编码结果
    }  // 结束 serialize

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {  // data：serialize 产生的先序遍历值串；返回还原出的 BST 根结点
        if (data.empty()) {  // 空串代表空树
            return nullptr;  // 还原为空指针
        }  // 结束空串判断
        vector<int> nums = split(data, ' ');  // 按空格切出所有结点值，其顺序就是先序遍历顺序
        int i = 0;  // 先序序列的读取下标，被下面的递归 lambda 共享
        function<TreeNode*(int, int)> dfs = [&](int mi, int mx) -> TreeNode* {  // 递归 lambda：借助 BST 的值域 (mi, mx) 还原子树，返回子树根
            if (i == nums.size() || nums[i] < mi || nums[i] > mx) {  // 序列已经读完，或当前值落在允许值域之外，说明该子树为空
                return nullptr;  // 该位置没有结点，返回空指针
            }  // 结束递归出口判断
            int x = nums[i++];  // 取出当前值并后移下标：它必然是这一子树的根
            TreeNode* root = new TreeNode(x);  // 用该值新建子树根结点
            root->left = dfs(mi, x);  // 左子树的值都必须小于 x，值域收紧为 (mi, x)
            root->right = dfs(x, mx);  // 右子树的值都必须大于 x，值域收紧为 (x, mx)
            return root;  // 返回还原好的子树根
        };  // 结束递归 lambda 的定义
        return dfs(INT_MIN, INT_MAX);  // 整棵树的值域是全部 int 取值范围，用极值作开区间边界
    }  // 结束 deserialize

    vector<int> split(const string& s, char delim) {  // 把字符串按分隔符切成按出现顺序排列的整数数组
        vector<int> tokens;  // 存放切分后转成的整数
        stringstream ss(s);  // 用字符串流模拟逐段读取
        string token;  // 保存当前读出的一段文本
        while (getline(ss, token, delim)) {  // 按 delim 逐段读取，直到流被读完
            tokens.push_back(stoi(token));  // 把文本段转成整数后加入结果
        }  // 结束切分循环
        return tokens;  // 返回整数序列
    }  // 结束 split
};  // 结束 Codec 类

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;