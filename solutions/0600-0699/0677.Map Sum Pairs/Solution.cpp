// 题目：677. 键值映射（Map Sum Pairs）
// 思路：字典树每个节点维护「经过它的所有键对应值之和」，插入时先把新值与旧值之差累加到路径上，查询前缀时直接返回该前缀末尾节点的累加值。
// 时间复杂度：插入与查询均为 O(L)，L 为键长；空间复杂度：O(总字符数 * 26)，字典树节点开销。
class Trie {  // 前缀树，节点上累计经过此处的键值之和
public:  // 对外接口
    Trie()  // 构造节点
        : children(26, nullptr) {  // 26 个孩子指针全部初始化为空
    }

    void insert(string& w, int x) {  // 把差值 x 累加到路径 w 上的每个节点
        Trie* node = this;  // 从根节点开始
        for (char c : w) {  // 逐字符向下
            c -= 'a';  // 把字符转成 0~25 的下标
            if (!node->children[c]) {  // 该分支还不存在
                node->children[c] = new Trie();  // 新建节点补上
            }
            node = node->children[c];  // 走到对应的孩子节点
            node->val += x;  // 该节点代表一个前缀，把差值累加到它的前缀和上
        }
    }

    int search(string& w) {  // 查询以 w 为前缀的所有键的值之和
        Trie* node = this;  // 从根节点开始
        for (char c : w) {  // 沿前缀逐字符向下
            c -= 'a';  // 把字符转成 0~25 的下标
            if (!node->children[c]) {  // 前缀分支不存在
                return 0;  // 没有任何键以此为前缀
            }
            node = node->children[c];  // 走到对应的孩子节点
        }
        return node->val;  // 该节点累计的就是所有以 w 为前缀的键值之和
    }

private:  // 内部数据
    vector<Trie*> children;  // 26 个孩子指针
    int val = 0;  // 经过当前节点的所有键的值之和
};

class MapSum {  // 题目要求的键值映射类
public:  // 对外接口
    MapSum() {  // 构造对象
    }

    void insert(string key, int val) {  // 插入或覆盖一个键值对
        int x = val - d[key];  // 只需把「新值 - 旧值」的增量写进树里（旧键不存在时 d[key] 为 0）
        d[key] = val;  // 更新哈希表中该键的最新值
        trie->insert(key, x);  // 把增量累加到前缀树的对应路径上
    }

    int sum(string prefix) {  // 求所有以 prefix 为前缀的键的当前值之和
        return trie->search(prefix);  // 前缀树末尾节点累计的就是答案
    }

private:  // 内部数据
    unordered_map<string, int> d;  // 记录每个键当前的值，用于计算覆盖时的增量
    Trie* trie = new Trie();  // 前缀树根节点，维护前缀和
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum* obj = new MapSum();
 * obj->insert(key,val);
 * int param_2 = obj->sum(prefix);
 */