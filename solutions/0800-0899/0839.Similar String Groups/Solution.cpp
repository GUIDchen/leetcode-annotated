// 题目：839. 相似字符串组（Similar String Groups）
// 思路：两个变位词若能通过至多一次交换（等价于恰好 0 或 2 个位置不同）互相转换就相似，相似关系可传递，于是用并查集把所有相似串合并，最终集合数就是组数。
// 时间复杂度：O(n^2·m·α(n))，两两比较字符串并做并查集合并；空间复杂度：O(n)，并查集的父指针与大小数组。
class UnionFind {  // 并查集模板：维护连通分量，用来把相似的字符串合并成一组
public:  // 对外提供构造、合并与查根三个接口
    UnionFind(int n) {  // 构造函数：n 个元素一开始各自独立
        p = vector<int>(n);  // 父指针数组，p[i] 指向 i 的父结点
        size = vector<int>(n, 1);  // 每棵树的大小，初始都为 1，用于按大小合并
        iota(p.begin(), p.end(), 0);  // iota 把 0..n-1 依次写入，初始时每个元素的父结点就是自己
    }  // 构造结束

    bool unite(int a, int b) {  // 合并 a、b 所在集合，返回本次是否真的发生了合并
        int pa = find(a), pb = find(b);  // 先找到两个元素所在集合的代表元（根）
        if (pa == pb) {  // 代表元相同说明本来就在同一集合
            return false;  // 无需合并，返回 false
        }  // if 结束
        if (size[pa] > size[pb]) {  // 按大小合并：把小的树挂到大的树上，保证树高为对数级
            p[pb] = pa;  // 小树根 pb 的父改为大树根 pa
            size[pa] += size[pb];  // 大树的大小累加小树的大小
        } else {  // 对称情况：pa 所在树更小或相等
            p[pa] = pb;  // 小树根 pa 的父改为大树根 pb
            size[pb] += size[pa];  // 大树的大小累加小树的大小
        }  // if-else 结束
        return true;  // 合并成功，返回 true
    }  // unite 结束

    int find(int x) {  // 查找 x 所在集合的根，同时做路径压缩
        if (p[x] != x) {  // x 不是根，说明还有父结点
            p[x] = find(p[x]);  // 递归查根，并把 x 直接挂到根上，压缩后续查询路径
        }  // if 结束
        return p[x];  // 返回 x 所在集合的根
    }  // find 结束

private:  // 以下成员只在类内部使用
    vector<int> p, size;  // p 为父指针数组，size 为集合大小数组
};  // UnionFind 类结束

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numSimilarGroups(vector<string>& strs) {  // strs 是一组互为变位词的字符串，返回相似字符串的组数
        int n = strs.size(), m = strs[0].size();  // n 为字符串个数，m 为每个字符串的长度（本题所有串等长）
        int cnt = n;  // 组数初值为 n：每个字符串先各自成组，每成功合并一次就减一
        UnionFind uf(n);  // 为每个字符串建立一个并查集元素
        for (int i = 0; i < n; ++i) {  // 枚举第一个字符串
            for (int j = 0; j < i; ++j) {  // 只与它前面的字符串比较，避免同一对被检查两次
                int diff = 0;  // 统计两个字符串在相同位置上字符不同的个数
                for (int k = 0; k < m; ++k) {  // 逐位比较
                    diff += strs[i][k] != strs[j][k];  // 不同则差异计数加一
                }  // 内层比较结束
                if (diff <= 2 && uf.unite(i, j)) {  // 两串互为变位词，差异只能是 0 或 ≥2，所以 diff≤2 恰好表示相同或恰好两位互换；合并成功才说明组数减少
                    --cnt;  // 两个集合合并成功，组数减一
                }  // if 结束
            }  // j 循环结束
        }  // i 循环结束
        return cnt;  // 返回最终组数
    }  // 方法结束
};
