// 3590. 第 K 小的路径异或和（Kth Smallest Path XOR Sum）
// 核心思路：先求根到每个节点的路径异或，再自底向上用按位 Trie 按“小并大”合并每个子树的异或集合；查询 (u,k) 即在该集合中取第 k 小的值。
// 复杂度：时间 O((n log n + q) · B)，空间 O(n · B)，其中 B = 17 为值域位数。
class BinarySumTrie {  // 按位 Trie，维护一个可去重的异或值集合，支持第 k 小查询
public:  // 对外接口
    int count = 0;  // 当前子树中包含的不同数值个数
    BinarySumTrie* children[2]{};  // 0/1 两个子节点，默认初始化为空指针

    void add(int num, int delta, int bit) {  // 把 num 从第 bit 位开始插入（delta=1）或删除（delta=-1）
        count += delta;  // 沿途节点的计数同步增减
        if (bit < 0) {  // 所有位都处理完了
            return;  // 到达叶节点，递归出口
        }  // if 结束
        int b = (num >> bit) & 1;  // 取出 num 的第 bit 位
        if (!children[b]) {  // 该分支的子节点还不存在
            children[b] = new BinarySumTrie();  // 新建子节点
        }  // if 结束
        children[b]->add(num, delta, bit - 1);  // 递归处理下一位
    }  // add 结束

    void collect(int prefix, int bit, vector<int>& output) {  // 收集本 Trie 内的全部数值，用于小并大合并
        if (count == 0) {  // 子树为空
            return;  // 没有值可收集
        }  // if 结束
        if (bit < 0) {  // 到达叶节点
            output.push_back(prefix);  // prefix 已拼成完整数值，放入结果
            return;  // 结束本次递归
        }  // if 结束
        if (children[0]) {  // 存在 0 分支
            children[0]->collect(prefix, bit - 1, output);  // 沿 0 位继续向下收集
        }  // if 结束
        if (children[1]) {  // 存在 1 分支
            children[1]->collect(prefix | (1 << bit), bit - 1, output);  // 沿 1 位继续向下收集，并把第 bit 位置 1
        }  // if 结束
    }  // collect 结束

    bool exists(int num, int bit) {  // 查询数值 num 是否已在集合中
        if (count == 0) {  // 空 Trie
            return false;  // 必然不存在
        }  // if 结束
        if (bit < 0) {  // 所有位都匹配到底
            return true;  // 数值存在
        }  // if 结束
        int b = (num >> bit) & 1;  // 取出当前位
        return children[b] && children[b]->exists(num, bit - 1);  // 子节点存在且后续位也能匹配
    }  // exists 结束

    int findKth(int k, int bit) {  // 返回集合中第 k 小（k 从 1 起）的值
        if (k > count) {  // k 超出集合大小
            return -1;  // 不存在，返回 -1
        }  // if 结束
        if (bit < 0) {  // 已经到达叶节点
            return 0;  // 低位不再有贡献
        }  // if 结束
        int leftCount = children[0] ? children[0]->count : 0;  // 0 分支中包含的数值个数
        if (k <= leftCount) {  // 第 k 小落在 0 分支
            return children[0]->findKth(k, bit - 1);  // 递归进入 0 分支
        }  // if 结束
        if (children[1]) {  // 落在 1 分支
            return (1 << bit) + children[1]->findKth(k - leftCount, bit - 1);  // 加上当前位的权值后递归进入 1 分支
        }  // if 结束
        return -1;  // 兜底：不存在
    }  // findKth 结束
};  // BinarySumTrie 定义结束

class Solution {  // 主解类
public:  // 对外接口
    vector<int> kthSmallest(vector<int>& par, vector<int>& vals, vector<vector<int>>& queries) {  // 入口：par 为父节点数组，vals 为节点值，queries 为 (u,k) 查询
        int n = par.size();  // 节点个数
        tree.assign(n, {});  // 邻接表：每个节点保存其子节点
        for (int i = 1; i < n; ++i) {  // 节点 0 是根，从 1 开始建边
            tree[par[i]].push_back(i);  // 父节点 par[i] 指向子节点 i
        }  // 循环结束
        pathXor = vals;  // 先把每个节点的值作为路径异或的初值
        computeXor(0, 0);  // 计算根到每个节点的路径异或
        nodeQueries.assign(n, {});  // 为每个节点准备查询列表
        for (int i = 0; i < (int) queries.size(); ++i) {  // 枚举所有查询
            nodeQueries[queries[i][0]].push_back({queries[i][1], i});  // 按起点 u 归组，保存 (k, 原始下标)
        }  // 循环结束
        pool.assign(n, nullptr);  // 为每个节点准备一棵子树 Trie
        result.assign(queries.size(), 0);  // 答案数组，长度等于查询数
        dfs(0);  // 自底向上合并并回答查询
        return result;  // 返回答案
    }  // kthSmallest 结束

private:  // 内部成员与辅助函数
    static constexpr int BITS = 17;  // 值域位数，2^17 已覆盖节点值的异或范围
    vector<vector<int>> tree;  // 树结构（父到子的邻接表）
    vector<int> pathXor;  // 根到每个节点的路径异或
    vector<vector<pair<int, int>>> nodeQueries;  // 挂在每个节点上的 (k, 查询下标)
    vector<BinarySumTrie*> pool;  // 每个节点对应的子树 Trie
    vector<int> result;  // 按原始下标存放答案

    void computeXor(int node, int acc) {  // 计算路径异或，acc 为父节点的路径异或
        pathXor[node] ^= acc;  // 把父路径的异或累加到当前节点
        for (int child : tree[node]) {  // 遍历所有子节点
            computeXor(child, pathXor[node]);  // 把当前节点的路径异或继续向下传递
        }  // 循环结束
    }  // computeXor 结束

    void dfs(int node) {  // 后序 DFS：合并子树 Trie 并回答本节点上的查询
        pool[node] = new BinarySumTrie();  // 为本节点新建一棵 Trie
        pool[node]->add(pathXor[node], 1, BITS);  // 先把自己的路径异或放进集合
        for (int child : tree[node]) {  // 遍历所有子节点
            dfs(child);  // 先递归处理子树，得到子树的 Trie
            if (pool[node]->count < pool[child]->count) {  // 小并大：让 node 始终持有规模更大的 Trie
                swap(pool[node], pool[child]);  // 交换两棵 Trie，避免反复遍历大集合
            }  // if 结束
            vector<int> vals;  // 暂存子 Trie 中的全部数值
            pool[child]->collect(0, BITS, vals);  // 把子 Trie 的所有值收集出来
            for (int val : vals) {  // 逐个值合并到父 Trie
                if (!pool[node]->exists(val, BITS)) {  // 集合语义需要去重
                    pool[node]->add(val, 1, BITS);  // 插入尚未存在的数值
                }  // if 结束
            }  // 循环结束
        }  // 循环结束
        for (auto [k, idx] : nodeQueries[node]) {  // 处理挂在当前节点上的所有查询
            result[idx] = pool[node]->count < k ? -1 : pool[node]->findKth(k, BITS);  // 不同值不足 k 个返回 -1，否则取第 k 小
        }  // 循环结束
    }  // dfs 结束
};  // Solution 定义结束
