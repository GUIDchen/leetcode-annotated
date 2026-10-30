// 题目：990. 等式方程的可满足性（Satisfiability of Equality Equations）
// 思路：并查集。先合并所有「==」两端的字母，再检查每个「!=」两端是否落在同一集合。
// 时间复杂度：O(n·α(26)) 近似 O(n)，n 为等式条数；空间复杂度：O(1)，只需要 26 个字母的父数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> p;  // 并查集父数组：下标 0..25 对应字母 'a'..'z'

    bool equationsPossible(vector<string>& equations) {  // equations：形如 "a==b" 或 "a!=b" 的等式列表；判断它们能否同时成立
        p.resize(26);  // 26 个小写字母，各自先自成一个集合
        for (int i = 0; i < 26; ++i) p[i] = i;  // 初始化：每个字母的父结点指向自己
        for (auto& e : equations) {  // 第一遍：只处理等号，把相等关系合并到同一集合
            int a = e[0] - 'a', b = e[3] - 'a';  // 等式固定形如 "x==y"，e[0] 与 e[3] 就是两侧的字母
            if (e[1] == '=') p[find(a)] = find(b);  // e[1] 为 '=' 表示两者相等，合并两个字母所在的集合
        }
        for (auto& e : equations) {  // 第二遍：检查不等号，若两端已被判等则约束矛盾
            int a = e[0] - 'a', b = e[3] - 'a';  // 同样取出不等号两侧的字母
            if (e[1] == '!' && find(a) == find(b)) return false;  // 要求不相等却查到同一集合，说明无解，直接返回 false
        }
        return true;  // 所有约束都不冲突，说明方程组可满足
    }

    int find(int x) {  // 并查集查找 + 路径压缩，返回 x 所在集合的代表元
        if (p[x] != x) p[x] = find(p[x]);  // 父结点不是自己说明还没到根：递归找根，并把 x 直接挂到根下
        return p[x];  // 返回根结点，即集合代表元
    }
};  // 类定义结束