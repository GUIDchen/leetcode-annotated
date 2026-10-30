// 题目：1061. 按字典序排列最小的等效字符串（Lexicographically Smallest Equivalent String）
// 思路：用并查集合并等价字母，合并时始终让字典序更小的根当父节点，于是每个集合的根就是最小字符，替换 baseStr 的每个字符即可。
// 时间复杂度：O((n + m)·α(26))，近似线性；空间复杂度：O(26) 即 O(1)，只用固定大小的字母表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string smallestEquivalentString(string s1, string s2, string baseStr) {  // s1[i] 与 s2[i] 等价，求 baseStr 的字典序最小等价串
        vector<int> p(26);  // 并查集父指针，节点 0..25 对应 'a'..'z'
        iota(p.begin(), p.end(), 0);  // 初始时每个字母自成一个集合
        auto find = [&](this auto&& find, int x) -> int {  // C++23 显式对象参数实现递归 lambda：查根并路径压缩
            if (p[x] != x) {  // 当前节点不是根
                p[x] = find(p[x]);  // 递归压缩路径，把父指针直接指向根
            }  // 压缩判断结束
            return p[x];  // 返回根节点
        };  // lambda 定义结束
        for (int i = 0; i < s1.length(); ++i) {  // 逐对处理等价关系
            int x = s1[i] - 'a';  // 把 s1[i] 映射为 0..25 的编号
            int y = s2[i] - 'a';  // 把 s2[i] 映射为 0..25 的编号
            int px = find(x), py = find(y);  // 分别找到两个集合的根
            if (px < py) {  // 让字典序更小的根作为新根
                p[py] = px;  // 大根挂到小根下
            } else {  // 否则（py 更小，或两者相等）
                p[px] = py;  // 同样把大根挂到小根下（相等时自赋值无副作用）
            }  // 合并分支结束
        }  // 等价关系处理完毕
        string s;  // 结果字符串
        for (char c : baseStr) {  // 逐个字符替换
            s.push_back('a' + find(c - 'a'));  // 取所在集合的最小字符（根始终是字典序最小的）
        }  // 替换结束
        return s;  // 返回字典序最小的等价串
    }  // 方法结束
};  // 类定义结束