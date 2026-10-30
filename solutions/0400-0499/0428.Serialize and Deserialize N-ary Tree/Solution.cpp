// 题目：428. 序列化和反序列化 N 叉树（Serialize and Deserialize N-ary Tree）
// 思路：序列化用 BFS，先写根节点值，再对每个节点输出全部子节点的值并以 # 收尾；反序列化按同样的 BFS 顺序把值读回成子节点。
// 时间复杂度：O(n)，每个节点只处理一次；空间复杂度：O(n)，队列与编码串都要存下所有节点。
// 说明：下面是题目自带的 N 叉树 Node 定义（被注释掉，由判题器提供），仅作参考。
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Codec {  // 编解码类
public:  // 方法对外可见
    string serialize(Node* root) {  // 把 N 叉树编码成逗号分隔的字符串
        if (!root) {  // 空树
            return "";  // 用空串表示空树
        }
        queue<Node*> q{{root}};  // BFS 队列，初始只有根节点
        string ans = to_string(root->val);  // 根节点的值单独写在整个串的最前面
        while (!q.empty()) {  // 队列非空就继续处理
            auto node = q.front();  // 取出队首节点
            q.pop();  // 弹出队首
            for (auto child : node->children) {  // 依次处理该节点的所有子节点
                ans += "," + to_string(child->val);  // 用逗号分隔，把子节点的值追加到编码串
                q.push(child);  // 子节点入队，之后还要继续输出它们的子节点
            }
            ans += ",#";  // # 标记当前节点的子节点列表结束
        }
        return ans;  // 返回编码结果
    }

    Node* deserialize(string data) {  // 把字符串还原成 N 叉树
        if (data.empty()) {  // 空串表示空树
            return nullptr;  // 返回空指针
        }
        stringstream ss(data);  // 用字符串流按逗号切分
        string t;  // 存放当前读到的片段
        getline(ss, t, ',');  // 先读第一个片段，也就是根节点的值
        Node* root = new Node(stoi(t), {});  // 用该值创建根节点，子节点列表初始为空
        queue<Node*> q{{root}};  // BFS 队列，从根节点开始
        while (!q.empty()) {  // 队列非空说明还有节点需要挂子节点
            auto node = q.front();  // 取出待处理的节点
            q.pop();  // 弹出队首
            while (getline(ss, t, ',') && t != "#") {  // 一直读子节点的值，直到读到 # 结束标记
                Node* child = new Node(stoi(t), {});  // 用片段里的值创建子节点
                node->children.push_back(child);  // 挂到当前节点的子节点列表
                q.push(child);  // 子节点入队，稍后为它读自己的子节点
            }
        }  // 还原完成，返回根节点
        return root;
    }  // deserialize 结束
};  // 类定义结束

// 下面是判题器给出的调用示例（属于题目注释，不是本题实现）。
// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
