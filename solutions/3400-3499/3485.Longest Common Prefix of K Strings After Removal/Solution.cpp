// 3485. 删除元素后 K 个字符串的最长公共前缀 / Longest Common Prefix of K Strings After Removal
// 核心思路：先用字典树统计每个前缀被多少个单词共享；每个深度只要还有至少 k 个可用前缀，就能作为答案，于是用线段树按深度维护“可用前缀数 > 0”的最大深度，逐个单词临时撤销其恰好被 k 个单词共享的前缀深度并查询，最后恢复现场。
// 复杂度：时间 O(L log L + total_len)（L 为最大可用前缀长度），空间 O(total_len)。
class Solution {  // 定义题解类
public:  // 公有接口
    struct TrieNode {  // 字典树节点
        int count = 0;  // 经过该节点的单词数量，即该前缀的出现次数
        int depth = 0;  // 节点深度，也就是对应前缀的长度
        int children[26] = {0};  // 26 个小写字母子节点下标，0 表示没有子节点
    };  // 结束 TrieNode 结构体

    class SegmentTree {  // 线段树：按深度维护当前仍可用的最大前缀长度
    public:  // 公有接口
        int n;  // 线段树维护的深度范围
        vector<int> tree;  // 线段树数组，值为 -1 表示该深度没有可用前缀
        vector<int>& globalCount;  // 引用全局的各深度可用前缀数量，便于查询时读取
        SegmentTree(int n, vector<int>& globalCount)  // 构造函数：绑定维护范围与全局计数
            : n(n)  // 初始化维护的深度上界
            , globalCount(globalCount) {  // 绑定全局计数引用并进入函数体
            tree.assign(4 * (n + 1), -1);  // 按 4 倍大小分配数组，全部初始化为 -1
            build(1, 1, n);  // 递归建树
        }  // 结束构造函数
        void build(int idx, int l, int r) {  // 建树：idx 为节点编号，[l, r] 为对应深度区间
            if (l == r) {  // 区间只剩一个深度，即叶子节点
                tree[idx] = globalCount[l] > 0 ? l : -1;  // 该深度仍有可用前缀则记录深度本身，否则记 -1
                return;  // 叶子处理完毕，返回
            }  // 结束叶子判断
            int mid = (l + r) / 2;  // 取区间中点
            build(idx * 2, l, mid);  // 递归建左子树
            build(idx * 2 + 1, mid + 1, r);  // 递归建右子树
            tree[idx] = max(tree[idx * 2], tree[idx * 2 + 1]);  // 父节点取左右儿子的较大值
        }  // 结束 build
        void update(int idx, int l, int r, int pos, int newVal) {  // 单点更新：把深度 pos 的可用数量改为 newVal
            if (l == r) {  // 到达叶子节点
                tree[idx] = newVal > 0 ? l : -1;  // 按新数量决定该深度是否可用
                return;  // 叶子更新完毕，返回
            }  // 结束叶子判断
            int mid = (l + r) / 2;  // 取区间中点
            if (pos <= mid)  // 目标深度落在左半边
                update(idx * 2, l, mid, pos, newVal);  // 递归更新左子树
            else  // 目标深度落在右半边
                update(idx * 2 + 1, mid + 1, r, pos, newVal);  // 递归更新右子树
            tree[idx] = max(tree[idx * 2], tree[idx * 2 + 1]);  // 回溯更新父节点的最大值
        }  // 结束 update
        int query() {  // 查询当前仍可用的最大深度
            return tree[1];  // 根节点保存的就是整个区间内的最大可用深度
        }  // 结束 query
    };  // 结束 SegmentTree 类

    vector<int> longestCommonPrefix(vector<string>& words, int k) {  // 主函数：返回每个单词删除后的最长公共前缀长度
        int n = words.size();  // 单词个数
        vector<int> ans(n, 0);  // 记录每个下标删除后的答案，初始为 0
        if (n - 1 < k) return ans;  // 剩余单词不足 k 个，任何下标删除后都无法凑出 k 个字符串
        vector<TrieNode> trie(1);  // 字典树数组，下标 0 为根节点
        for (const string& word : words) {  // 把所有单词插入字典树以统计前缀出现次数
            int cur = 0;  // 从根节点开始
            for (char c : word) {  // 逐字符沿树向下走
                int idx = c - 'a';  // 字符映射到 0..25
                if (trie[cur].children[idx] == 0) {  // 该字母对应的子节点还不存在
                    trie[cur].children[idx] = trie.size();  // 新节点下标就是当前数组长度
                    trie.push_back({0, trie[cur].depth + 1});  // 追加新节点：计数为 0，深度为父节点深度加一
                }  // 结束新建子节点判断
                cur = trie[cur].children[idx];  // 走向该字符对应的子节点
                trie[cur].count++;  // 该前缀的出现次数加一
            }  // 结束单词内字符遍历
        }  // 结束所有单词的插入
        int maxDepth = 0;  // 仍有至少 k 个单词共享的最大前缀长度
        for (int i = 1; i < trie.size(); ++i) {  // 遍历所有非根节点
            if (trie[i].count >= k) {  // 该前缀被至少 k 个单词共享
                maxDepth = max(maxDepth, trie[i].depth);  // 用它更新最大前缀长度
            }  // 结束可用性判断
        }  // 结束深度统计
        vector<int> globalCount(maxDepth + 1, 0);  // 各深度上“计数仍 >= k 的前缀”个数
        for (int i = 1; i < trie.size(); ++i) {  // 再次遍历所有非根节点
            if (trie[i].count >= k && trie[i].depth <= maxDepth) {  // 只统计深度不超过最大可用深度的前缀
                globalCount[trie[i].depth]++;  // 该深度可用前缀数加一
            }  // 结束统计判断
        }  // 结束各深度计数
        vector<vector<int>> fragileList(n);  // 每个单词删除后会让计数从 k 变成 k-1 的深度列表
        for (int i = 0; i < n; ++i) {  // 逐个单词收集敏感深度
            int cur = 0;  // 从根节点开始
            for (char c : words[i]) {  // 沿该单词的字符向下走
                int idx = c - 'a';  // 字符映射到 0..25
                cur = trie[cur].children[idx];  // 走向对应子节点
                if (trie[cur].count == k) {  // 恰好 k 个单词共享该前缀，删除本单词后它就不再可用
                    fragileList[i].push_back(trie[cur].depth);  // 记录这个受影响的深度
                }  // 结束敏感深度判断
            }  // 结束单词内字符遍历
        }  // 结束敏感深度收集
        int segSize = maxDepth;  // 线段树维护的深度范围就是最大可用深度
        if (segSize >= 1) {  // 存在可用深度时才需要建树
            SegmentTree segTree(segSize, globalCount);  // 建立线段树
            for (int i = 0; i < n; ++i) {  // 逐个计算删除该单词后的答案
                if (n - 1 < k) {  // 防御性判断：剩余单词不足 k 个
                    ans[i] = 0;  // 此时答案只能是 0
                } else {  // 否则正常计算
                    for (int d : fragileList[i]) {  // 先撤销本单词带来的失效深度
                        segTree.update(1, 1, segSize, d, globalCount[d] - 1);  // 该深度的可用前缀数减一
                    }  // 结束失效深度撤销
                    int res = segTree.query();  // 查询当前仍可用的最大深度
                    ans[i] = res == -1 ? 0 : res;  // 返回 -1 表示没有任何可用前缀，答案记为 0
                    for (int d : fragileList[i]) {  // 恢复现场
                        segTree.update(1, 1, segSize, d, globalCount[d]);  // 该深度的可用前缀数复原
                    }  // 结束现场恢复
                }  // 结束正常计算分支
            }  // 结束逐个单词计算
        }  // 结束线段树分支
        return ans;  // 返回每个下标删除后的答案
    }  // 结束 longestCommonPrefix
};  // 结束 Solution 类