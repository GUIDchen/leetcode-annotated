// 题目：1166. 设计文件系统（Design File System）
// 思路：用字典树按 '/' 切分路径逐段建树；createPath 要求父路径已存在且自身不重复，get 沿路径走到末端返回存下的值。
// 时间复杂度：createPath 与 get 都是 O(L)（L 为路径段数）；空间复杂度：O(S)，S 为所有已创建路径的字符总数。
class Trie {  // 字典树节点：一个节点代表一层路径，根节点代表 "/"
public:  // 对外开放
    unordered_map<string, Trie*> children;  // 子节点表：键是下一段路径名，值是对应的子节点
    int v;  // 当前路径保存的值，-1 表示根节点或中间目录

    Trie(int v) {  // 构造函数：为新路径节点绑定值
        this->v = v;  // 记录该节点保存的值
    }  // 构造函数结束

    bool insert(string& w, int v) {  // 创建路径 w 并赋值为 v，成功返回 true，失败返回 false
        Trie* node = this;  // 从根节点出发向下走
        auto ps = split(w, '/');  // 按 '/' 切分路径，例如 "/a/b" 会得到 ["", "a", "b"]
        for (int i = 1; i < ps.size() - 1; ++i) {  // 只遍历父目录部分，跳过首段空串和最后一段自身
            auto p = ps[i];  // 取当前层的路径名
            if (!node->children.count(p)) {  // 父目录不存在时不能创建子路径
                return false;  // 父路径缺失，创建失败
            }  // if 结束
            node = node->children[p];  // 沿路径继续下沉一层
        }  // 父目录全部校验完毕
        if (node->children.count(ps.back())) {  // 目标路径已经存在（不允许重复创建）
            return false;  // 重复创建返回失败
        }  // if 结束
        node->children[ps.back()] = new Trie(v);  // 挂上新的叶子节点，并把值保存在节点里
        return true;  // 创建成功
    }  // insert 方法结束

    int search(string& w) {  // 查询路径 w 对应的值，不存在时返回 -1
        Trie* node = this;  // 从根节点出发
        auto ps = split(w, '/');  // 同样按 '/' 切分路径
        for (int i = 1; i < ps.size(); ++i) {  // 逐段向下查找，这里需要走到最后一段（即目标本身）
            auto p = ps[i];  // 取当前层的路径名
            if (!node->children.count(p)) {  // 某一段路径不存在
                return -1;  // 路径不存在，返回 -1
            }  // if 结束
            node = node->children[p];  // 继续下沉一层
        }  // 循环结束，已经走到目标节点
        return node->v;  // 返回末端节点保存的值
    }  // search 方法结束

private:  // 私有辅助函数
    vector<string> split(string& s, char delim) {  // 按分隔符切分字符串
        stringstream ss(s);  // 用字符串流逐个读取片段
        string item;  // 存放每次读到的片段
        vector<string> res;  // 存放切分结果
        while (getline(ss, item, delim)) {  // 一直读到流结束
            res.emplace_back(item);  // 把当前片段收集起来
        }  // while 结束
        return res;  // 返回切分结果
    }  // split 方法结束
};  // Trie 类定义结束

class FileSystem {  // 题目要求实现的文件系统类
public:  // 对外开放
    FileSystem() {  // 构造函数：初始化字典树的根节点
        trie = new Trie(-1);  // 根节点值为 -1，代表根目录 "/"
    }  // 构造函数结束

    bool createPath(string path, int value) {  // 创建新路径并赋值为 value
        return trie->insert(path, value);  // 交给字典树完成插入
    }  // createPath 方法结束

    int get(string path) {  // 查询路径对应的值
        return trie->search(path);  // 交给字典树完成查找
    }  // get 方法结束

private:  // 私有成员
    Trie* trie;  // 字典树根指针
};  // FileSystem 类定义结束

/**
 * Your FileSystem object will be instantiated and called as such:
 * FileSystem* obj = new FileSystem();
 * bool param_1 = obj->createPath(path,value);
 * int param_2 = obj->get(path);
 */