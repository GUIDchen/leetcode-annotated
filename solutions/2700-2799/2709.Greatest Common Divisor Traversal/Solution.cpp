// 题目：2709. 最大公约数遍历（Greatest Common Divisor Traversal）
// 思路：把每个下标和它的各个质因子都当作图上的节点，下标与质因子连边；并查集合并后，所有下标同属一个连通块即可遍历全部下标。
// 时间复杂度：O(MX·log MX + n·ω·α)，预处理质因子加并查集；空间复杂度：O(MX·ω + n + m)，质因子表与并查集数组。
int MX = 100010;  // 预处理上限：题目中 nums[i] 最大可达 10^5
vector<int> P[100010];  // P[x] 保存 x 的所有不同质因子

int init = []() {  // 静态初始化：程序启动时先建好 1..MX-1 的质因子表（LeetCode 惯用的预处理技巧）
    for (int x = 1; x < MX; ++x) {  // 依次处理每个数 x
        int v = x;  // v 是试除过程中的剩余部分，初始为 x
        int i = 2;  // 从最小的质数 2 开始试除
        while (i <= v / i) {  // 只需试除到 sqrt(v)，写成 i <= v / i 可避免溢出
            if (v % i == 0) {  // i 能整除 v，说明 i 是 v 的一个质因子
                P[x].push_back(i);  // 记录质因子 i
                while (v % i == 0) {  // 把 v 中所有因子 i 除尽，保证之后找到的都是质因子
                    v /= i;  // 除以 i
                }
            }
            ++i;  // 试除下一个候选因子
        }
        if (v > 1) {  // 除完后若 v 仍大于 1，则剩下的 v 本身就是一个质因子
            P[x].push_back(v);  // 记录这个剩余的质因子
        }
    }
    return 0;  // 初始化 lambda 要求有返回值，返回任意 int 即可
}();  // 立即调用该 lambda，把结果赋给全局变量 init

class UnionFind {  // 并查集：负责合并「下标节点」与「质因子节点」
public:  // 下面的接口对外可见
    UnionFind(int n) {  // 构造 n 个元素，初始各自成一个集合
        p = vector<int>(n);  // 父指针数组，先分配 n 个空间
        size = vector<int>(n, 1);  // 每个集合的大小，初始都是 1
        iota(p.begin(), p.end(), 0);  // 令 p[i] = i，即每个元素自己就是根
    }

    bool unite(int a, int b) {  // 合并两个元素所在集合，返回是否真的发生了合并
        int pa = find(a), pb = find(b);  // 分别找到两个元素所在集合的根
        if (pa == pb) {  // 本来就在同一集合，无需合并
            return false;  // 返回 false 表示没有合并
        }
        if (size[pa] > size[pb]) {  // 按大小合并：把较小的集合挂到较大的集合下，控制树高
            p[pb] = pa;  // pb 的父节点改成 pa
            size[pa] += size[pb];  // 更新大集合的大小
        } else {  // 否则把 pa 挂到 pb 下面
            p[pa] = pb;  // pa 的父节点改成 pb
            size[pb] += size[pa];  // 更新 pb 所在集合的大小
        }
        return true;  // 两个集合成功合并
    }

    int find(int x) {  // 查找 x 所在集合的根，并做路径压缩
        if (p[x] != x) {  // x 还不是根，需要继续往上找
            p[x] = find(p[x]);  // 递归找根，同时让 x 直接指向根
        }
        return p[x];  // 返回根节点
    }

private:  // 以下成员只在类内部使用
    vector<int> p, size;  // p：父指针数组；size：集合大小数组
};

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool canTraverseAllPairs(vector<int>& nums) {  // nums：待判断的数组
        int m = *max_element(nums.begin(), nums.end());  // 数组中的最大值，决定质因子编号的上界
        int n = nums.size();  // 数组长度
        UnionFind uf(m + n + 1);  // 并查集大小 = n 个下标节点 + m 个质因子节点 + 1 个安全余量
        for (int i = 0; i < n; ++i) {  // 遍历每个下标 i
            for (int j : P[nums[i]]) {  // 遍历 nums[i] 的所有不同质因子 j
                uf.unite(i, j + n);  // 把下标 i 与质因子节点 j+n 连起来，共享质因数即可互相到达
            }
        }
        unordered_set<int> s;  // 收集所有下标所在的集合根，用于统计连通块个数
        for (int i = 0; i < n; ++i) {  // 遍历每个下标
            s.insert(uf.find(i));  // 记录该下标所在集合的根
        }
        return s.size() == 1;  // 所有下标都在同一连通块时才能遍历全部下标
    }
};