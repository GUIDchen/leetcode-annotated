// 题目：1948. 删除系统中的重复文件夹（Delete Duplicate Folders in System）
// 思路：先用 Trie 建目录树，再自底向上给每棵子树算结构签名，签名相同的子树标记删除，最后 DFS 输出剩余路径。
// 时间复杂度：O(N·L·logN)，N 为路径数、L 为路径长度，签名需排序；空间复杂度：O(N·L)，Trie 节点与签名哈希表。
class Trie {  // 目录树节点
public:
    unordered_map<string, Trie*> children;  // 子目录名 → 对应的子节点
    bool deleted = false;  // 该子树是否因为重复而需要被删除
};

class Solution {  // LeetCode 约定的题解类
public:
    vector<vector<string>> deleteDuplicateFolder(vector<vector<string>>& paths) {  // paths：若干条目录路径
        Trie* root = new Trie();  // 虚拟根节点，便于统一处理各条路径

        for (auto& path : paths) {  // 逐条路径插入 Trie
            Trie* cur = root;  // 每条路径都从根节点开始走
            for (auto& name : path) {  // 沿路径逐个目录名向下
                if (cur->children.find(name) == cur->children.end()) {  // 该子目录还不存在
                    cur->children[name] = new Trie();  // 新建节点挂到父节点下
                }
                cur = cur->children[name];  // 走到这个子目录，继续处理下一个名字
            }
        }

        unordered_map<string, Trie*> g;  // 结构签名 → 第一次出现该签名的节点

        auto dfs = [&](this auto&& dfs, Trie* node) -> string {  // 递归求以 node 为根的子树签名
            if (node->children.empty()) return "";  // 叶子目录没有子结构，签名是空串

            vector<string> subs;  // 收集每个子目录的「名字(子签名)」
            for (auto& child : node->children) {  // 遍历所有子目录
                subs.push_back(child.first + "(" + dfs(child.second) + ")");  // 先递归求子签名再拼成字符串
            }
            sort(subs.begin(), subs.end());  // 排序，消除子目录先后顺序带来的差异
            string s = "";  // 当前子树的结构签名
            for (auto& sub : subs) s += sub;  // 拼接所有子结构，得到完整签名

            if (g.contains(s)) {  // 之前已经出现过完全相同的结构
                node->deleted = true;  // 当前子树标记为待删除
                g[s]->deleted = true;  // 先前那棵同构子树也标记为待删除
            } else {
                g[s] = node;  // 首次出现该签名，登记下来供后续比较
            }
            return s;  // 把签名交回父节点继续拼接
        };

        dfs(root);  // 自底向上算出所有签名并标记重复子树

        vector<vector<string>> ans;  // 输出：所有被保留下来的目录路径
        vector<string> path;  // 回溯过程中维护的当前路径

        auto dfs2 = [&](this auto&& dfs2, Trie* node) -> void {  // 第二次 DFS，收集保留下来的路径
            if (node->deleted) return;  // 被标记删除的子树，整棵直接跳过
            if (!path.empty()) {  // 根节点本身不算一条目录路径
                ans.push_back(path);  // 把当前路径加入答案
            }
            for (auto& child : node->children) {  // 递归处理每个子目录
                path.push_back(child.first);  // 先压入子目录名
                dfs2(child.second);  // 递归进入该子目录
                path.pop_back();  // 回溯：弹出子目录名，恢复现场
            }
        };

        dfs2(root);  // 从根节点开始收集答案

        return ans;  // 返回所有保留下来的目录路径
    }
};
