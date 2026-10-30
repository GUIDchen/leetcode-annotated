// 题目：399. 除法求值（Evaluate Division）
// 思路：带权并查集。把等式 a / b = v 看成 a 与 b 之间的权重关系，令 w[x] 表示「x 的值 / 父节点的值」，合并集合时按公式推出新根的权值，查询时用两点到根的权值相除。
// 时间复杂度：O((n + m) α(n))，n 为等式数、m 为查询数，路径压缩后近似常数；空间复杂度：O(n)，父指针表与权值表各存 O(n) 项。
class Solution {  // LeetCode 约定的题解类
public:  // 成员表与两个方法对外可见
    unordered_map<string, string> p;  // 并查集父指针：变量名 -> 父变量名
    unordered_map<string, double> w;  // 权值表：w[x] 表示「x 的值 / 父节点的值」，用来把比值沿路径累乘

    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {  // 先用等式建带权并查集，再逐条回答查询
        int n = equations.size();  // n 是等式个数
        for (auto e : equations) {  // 第一遍：把出现过的变量都初始化为独立集合
            p[e[0]] = e[0];  // 变量 e[0] 的父亲先设为自己
            p[e[1]] = e[1];  // 变量 e[1] 的父亲先设为自己
            w[e[0]] = 1.0;  // 自己与自己的比值是 1
            w[e[1]] = 1.0;  // 自己与自己的比值是 1
        }  // 初始化结束
        for (int i = 0; i < n; ++i) {  // 第二遍：按 a / b = values[i] 合并集合
            vector<string> e = equations[i];  // 取出当前等式（拷贝一份便于书写）
            string a = e[0], b = e[1];  // a 是被除数，b 是除数
            string pa = find(a), pb = find(b);  // 分别找到两个变量所在集合的根，find 会顺带压缩路径
            if (pa == pb) continue;  // 根相同说明这两个变量已被之前的等式约束，当前等式冗余
            p[pa] = pb;  // 把 a 的根挂到 b 的根下面
            w[pa] = w[b] * values[i] / w[a];  // 由 a/b = v 推出 pa/pb = w[b]*v/w[a]，据此设置新根 pa 的权值
        }
        int m = queries.size();  // m 是查询个数
        vector<double> ans(m);  // 先开好 m 个位置存放答案
        for (int i = 0; i < m; ++i) {  // 逐个回答查询
            string c = queries[i][0], d = queries[i][1];  // c 是被除数，d 是除数
            ans[i] = p.find(c) == p.end() || p.find(d) == p.end() || find(c) != find(d) ? -1.0 : w[c] / w[d];  // 变量没出现过或不在同一集合时无解，返回 -1；否则两者到根比值相除即 c/d
        }
        return ans;  // 返回所有查询的答案
    }

    string find(string x) {  // 带路径压缩的查找：返回根变量名，并把 w[x] 修正为 x 到根的比值
        if (p[x] != x) {  // x 还不是根节点
            string origin = p[x];  // 先记下旧的父节点，压缩之后还要用它的权值换算
            p[x] = find(p[x]);  // 递归找到根，并把 x 直接挂到根下面
            w[x] *= w[origin];  // 路径变短，权重改成 x 到新根（即旧父到根）的连乘
        }
        return p[x];  // 返回根变量名
    }
};  // 题解类结束