// 题目：721. 账户合并（Accounts Merge）
// 思路：以账户下标为元素建并查集，同一邮箱出现在多个账户时合并这些账户；再把每个合并组的邮箱去重排序，前面拼上账户名。
// 时间复杂度：O(total * log total)（并查集近线性 + 排序）；空间复杂度：O(total)，total 为邮箱总数。
class UnionFind {  // 并查集：维护账户之间的合并关系
public:  // 对外接口
    UnionFind(int n) {  // n：元素个数（账户个数）
        p = vector<int>(n);  // p[x] 表示 x 的父节点
        size = vector<int>(n, 1);  // size[x] 表示以 x 为根的集合大小，初始都为 1
        iota(p.begin(), p.end(), 0);  // iota 依次赋值 0..n-1：初始每个元素各自成集合
    }  // 构造函数结束

    bool unite(int a, int b) {  // 合并 a、b 所在集合，返回本次是否真的发生了合并
        int pa = find(a), pb = find(b);  // 先求出两个集合的根
        if (pa == pb) {  // 根相同，说明本来就在同一集合
            return false;  // 无需合并
        }  // if 分支结束
        if (size[pa] > size[pb]) {  // 按大小合并：把小集合挂到大集合上，保证树高为 O(log n)
            p[pb] = pa;  // 把 b 的根挂到 a 的根下面
            size[pa] += size[pb];  // 更新合并后集合的大小
        } else {  // 否则反过来把 a 的根挂到 b 的根下面
            p[pa] = pb;  // 挂接
            size[pb] += size[pa];  // 更新合并后集合的大小
        }  // else 分支结束
        return true;  // 本次确实合并成功
    }  // unite 方法结束

    int find(int x) {  // 查找 x 所在集合的根
        if (p[x] != x) {  // p[x] 不是自己，说明还有父节点
            p[x] = find(p[x]);  // 路径压缩：递归找到根后顺手把 x 直接挂到根上
        }  // if 分支结束
        return p[x];  // 压缩后 p[x] 就是根
    }  // find 方法结束

private:  // 以下为内部数据
    vector<int> p, size;  // p：父节点数组；size：集合大小（成员名与 std::size 同名，此处是成员变量）
};  // 并查集类定义结束

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {  // accounts：每个元素是「账户名 + 若干邮箱」
        int n = accounts.size();  // 账户数量
        UnionFind uf(n);  // 用账户下标建并查集
        unordered_map<string, int> d;  // 映射：邮箱 → 首次出现它的账户下标
        for (int i = 0; i < n; ++i) {  // 遍历每个账户
            for (int j = 1; j < accounts[i].size(); ++j) {  // 下标 0 是账户名，从 1 开始才是邮箱
                const string& email = accounts[i][j];  // 当前邮箱（用引用避免拷贝）
                if (d.find(email) != d.end()) {  // 该邮箱之前出现过，说明两个账户属于同一个人
                    uf.unite(i, d[email]);  // 合并这两个账户
                } else {  // 该邮箱第一次出现
                    d[email] = i;  // 记录它的归属账户
                }  // else 分支结束
            }  // 内层 for 结束
        }  // 外层 for 结束
        unordered_map<int, set<string>> g;  // 根账户下标 → 该合并组的邮箱集合（set 自动去重并按字典序排列）
        for (int i = 0; i < n; ++i) {  // 再次遍历账户，把邮箱按根归组
            int root = uf.find(i);  // 找到 i 所属合并组的代表
            g[root].insert(accounts[i].begin() + 1, accounts[i].end());  // 把 i 的邮箱（下标 1 之后）全部并入该组
        }  // for 循环结束
        vector<vector<string>> ans;  // 结果集
        for (const auto& [root, s] : g) {  // 遍历每个合并组（结构化绑定解包 key 与 value）
            vector<string> emails(s.begin(), s.end());  // 组内邮箱已按字典序排列
            emails.insert(emails.begin(), accounts[root][0]);  // 把账户名插到最前面
            ans.push_back(emails);  // 加入结果集
        }  // for 循环结束
        return ans;  // 返回合并后的账户列表
    }  // 方法结束
};  // 类定义结束