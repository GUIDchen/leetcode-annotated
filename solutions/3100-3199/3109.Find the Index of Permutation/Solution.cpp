// 题目：3109. 查找排列的下标（Find the Index of Permutation）🔒
// 思路：康托展开求字典序排名，从高位到低位累加「本位可选的更小未用数字个数 × 剩余位阶乘」，用树状数组统计更小值中有多少已被用掉。
// 时间复杂度：O(n log n)，每次树状数组查询/更新 O(log n)；空间复杂度：O(n)，阶乘表与树状数组各 O(n)。
class BinaryIndexedTree {  // 树状数组（Fenwick 树），维护 1..n 中哪些数值已经被使用
private:  // 以下为内部数据成员
    int n;  // 数值下标的上界
    vector<int> c;  // 树状数组本体，c[i] 保存区间 (i - lowbit(i), i] 的和

public:  // 以下为对外接口
    BinaryIndexedTree(int n)  // 构造函数，n 是数值范围上界
        : n(n)  // 初始化成员变量 n
        , c(n + 1) {}  // 开 n+1 个桶，因为树状数组下标从 1 开始用

    void update(int x, int delta) {  // 单点修改：把位置 x 的值增加 delta
        for (; x <= n; x += x & -x) {  // 沿父链向上跳，直到越过上界
            c[x] += delta;  // 每个覆盖位置 x 的节点都累加同样的增量
        }
    }

    int query(int x) {  // 前缀查询：返回 1..x 的区间和
        int s = 0;  // 前缀和累加器
        for (; x > 0; x -= x & -x) {  // 每次剥掉最低位的 1，逐段向下累加
            s += c[x];  // 把当前段所管区间的和累加进 s
        }
        return s;  // 返回 1..x 的前缀和
    }
};

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int getPermutationIndex(vector<int>& perm) {  // perm 是待求字典序排名的排列
        const int mod = 1e9 + 7;  // 结果需要对 1e9+7 取模
        using ll = long long;  // 简写 long long，避免阶乘乘法溢出
        ll ans = 0;  // 累计的字典序排名
        int n = perm.size();  // 排列长度
        BinaryIndexedTree tree(n + 1);  // 数值取值是 1..n，所以树状数组开到 n+1
        ll f[n];  // 阶乘表，f[i] 表示 i!
        f[0] = 1;  // 0! = 1，作为递推基准
        for (int i = 1; i < n; ++i) {  // 递推求出 1! 到 (n-1)!
            f[i] = f[i - 1] * i % mod;  // i! = (i-1)! × i，边乘边取模防止溢出
        }
        for (int i = 0; i < n; ++i) {  // 从高位到低位逐位计算对排名的贡献
            int cnt = perm[i] - 1 - tree.query(perm[i]);  // 比 perm[i] 小且还没被使用过的数字个数
            ans += cnt * f[n - i - 1] % mod;  // 本位贡献 = 可选个数 × 剩余位数的全排列数
            tree.update(perm[i], 1);  // 把 perm[i] 标记为已使用，供后面的位置查询
        }
        return ans % mod;  // 返回取模后的字典序排名
    }
};