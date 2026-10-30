// 题目：2307. 检查方程中的矛盾之处（Check for Contradictions in Equations）
// 思路：带权并查集，每条方程 a/b = v 表示 a 是 b 的 v 倍；合并集合时按比例维护权值，同一集合内比例对不上即为矛盾。
// 时间复杂度：O(n·α(m))，n 为方程数、m 为变量数；空间复杂度：O(m)，父指针与权值数组各一。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool checkContradictions(vector<vector<string>>& equations, vector<double>& values) {  // equations 是形如 [a, b] 的方程数组，values[i] 表示 a / b 的比值
        unordered_map<string, int> d;  // 哈希表：把变量名字符串映射成从 0 开始的连续编号
        int n = 0;  // n 记录已经分配出去的变量编号个数
        for (auto& e : equations) {  // 第一遍：给每个出现过的变量分配一个编号
            for (auto& s : e) {  // 遍历一条方程里的两个变量名
                if (!d.count(s)) {  // 变量第一次出现时才需要分配新编号
                    d[s] = n++;  // 写入编号，并把计数器加一
                }
            }
        }
        vector<int> p(n);  // 并查集父指针数组，初始时每个变量各自成集合
        iota(p.begin(), p.end(), 0);  // iota 把 0..n-1 依次填入 p，即令 p[i] = i
        vector<double> w(n, 1.0);  // 权值数组：w[x] = x / parent[x]，表示 x 相对父节点的倍数，初始各自为根所以都是 1
        function<int(int)> find = [&](int x) -> int {  // 带权路径压缩的 find：返回 x 所在集合的根，同时把 w[x] 更新为「x 相对根」的倍数
            if (p[x] != x) {  // 自己不是根，说明还有父节点要往上走
                int root = find(p[x]);  // 先递归求出父节点所属的根，此时 w[p[x]] 已被更新为相对根的倍数
                w[x] *= w[p[x]];  // x 相对根的倍数 = x 相对旧父的倍数 × 旧父相对根的倍数
                p[x] = root;  // 路径压缩：让 x 的父指针直接指向根
            }
            return p[x];  // 返回 x 所在集合的根
        };  // lambda 的赋值语句到此结束
        for (int i = 0; i < equations.size(); ++i) {  // 第二遍：逐条方程检查是否与已建立的关系矛盾
            int a = d[equations[i][0]], b = d[equations[i][1]];  // 取出方程两端变量对应的编号 a、b
            double v = values[i];  // v 就是 a / b 的比值
            int pa = find(a), pb = find(b);  // 分别求出 a、b 所在集合的根
            if (pa != pb) {  // 两个集合尚未连通，需要按比例合并
                p[pb] = pa;  // 让 b 的根 pb 指向 a 的根 pa，即把 b 的集合并入 a 的集合
                w[pb] = v * w[a] / w[b];  // 由 a/b=v、w[a]=a/pa、w[b]=b/pb 推出 pb/pa = v·w[a]/w[b]
            } else if (fabs(v * w[a] - w[b]) >= 1e-5) {  // 已连通时校验现有比例是否与方程一致，1e-5 是浮点误差容忍度
                return true;  // 比例对不上，说明出现矛盾
            }
        }
        return false;  // 所有方程都不矛盾
    }
};  // 类定义结束，最后一个分号收尾