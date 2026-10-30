// 题目：212. 单词搜索 II（Word Search II）
// 思路：把所有单词建成前缀树，再从矩阵每个格子出发做 DFS；沿途沿前缀树下走，走到单词结尾就收集，并用 # 标记回溯。
// 时间复杂度：O(m * n * 4^L)，L 为单词最大长度（前缀树剪枝后远小于此）；空间复杂度：O(总字符数 + L)。
class Trie {  // 前缀树节点：26 个儿子 + 记录该节点对应的单词下标
public:  // 成员公开
    vector<Trie*> children;  // 26 个槽位对应 a~z
    int ref;  // 若本节点是某个单词的结尾，存该单词在 words 中的下标；否则为 -1

    Trie()  // 构造函数
        : children(26, nullptr)  // 开 26 个空槽位
        , ref(-1) {}  // 默认不是任何单词的结尾

    void insert(const string& w, int ref) {  // 插入单词 w，并记下它的下标 ref
        Trie* node = this;  // 从当前节点（根）出发
        for (char c : w) {  // 逐字符建路径
            c -= 'a';  // 字符就地换算成 0~25 下标
            if (!node->children[c]) {  // 该字母分支不存在
                node->children[c] = new Trie();  // 新建节点挂上去
            }  // if 分支结束
            node = node->children[c];  // 向下走一层
        }  // 单词遍历结束
        node->ref = ref;  // 末尾节点记住这是 words 里第 ref 个单词
    }  // insert 结束
};  // Trie 定义结束

class Solution {  // LeetCode 约定的题解类
public:  // 解题接口对外可见
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {  // board 是字母矩阵，words 是待查找的单词表
        Trie* tree = new Trie();  // 建一棵空前缀树，把所有单词都挂上去
        for (int i = 0; i < words.size(); ++i) {  // 逐个单词插入
            tree->insert(words[i], i);  // 同时记下它在 words 中的下标
        }  // 建树完成
        vector<string> ans;  // 存放找到的单词
        int m = board.size(), n = board[0].size();  // 矩阵的行数 m 与列数 n

        function<void(Trie*, int, int)> dfs = [&](Trie* node, int i, int j) {  // DFS：从格子 (i, j) 出发，在树的 node 位置继续往下匹配
            int idx = board[i][j] - 'a';  // 当前格子字符对应的分支下标
            if (!node->children[idx]) {  // 前缀树里没有这条分支
                return;  // 剪枝：这条路走不出任何单词
            }  // if 分支结束
            node = node->children[idx];  // 沿该字符向下走一层
            if (node->ref != -1) {  // 走到的是一个单词的结尾
                ans.emplace_back(words[node->ref]);  // 把这个单词加入答案
                node->ref = -1;  // 置 -1，防止同一个单词被重复加入
            }  // if 分支结束
            int dirs[5] = {-1, 0, 1, 0, -1};  // 方向数组：相邻两项配出上、右、下、左四个方向
            char c = board[i][j];  // 先记下当前格子的字符，回溯时要还原
            board[i][j] = '#';  // 标记为已访问，避免同一次搜索里重复踩同一格
            for (int k = 0; k < 4; ++k) {  // 枚举四个方向
                int x = i + dirs[k], y = j + dirs[k + 1];  // 计算相邻格子的坐标
                if (x >= 0 && x < m && y >= 0 && y < n && board[x][y] != '#') {  // 坐标合法，且该格本次尚未被访问
                    dfs(node, x, y);  // 递归搜索相邻格子
                }  // if 分支结束
            }  // 四个方向枚举结束
            board[i][j] = c;  // 回溯：把格子字符还原，供其他路径使用
        };  // lambda 定义结束

        for (int i = 0; i < m; ++i) {  // 枚举每个起点行
            for (int j = 0; j < n; ++j) {  // 枚举每个起点列
                dfs(tree, i, j);  // 以 (i, j) 为起点尝试沿前缀树搜索
            }  // 列枚举结束
        }  // 行枚举结束
        return ans;  // 返回所有找到的单词
    }  // 方法结束
};  // 类定义结束（源文件末尾没有换行符，此处保持原样）