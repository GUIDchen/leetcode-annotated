// 题目：1202. 交换字符串中的元素（Smallest String With Swaps）
// 思路：并查集把能互相交换的下标合并成连通块，块内字符降序排好再按原顺序弹尾，得到字典序最小的串。
// 时间复杂度：O(n log n + m α(n))，块内排序主导；空间复杂度：O(n)，并查集与每块的字符列表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {  // s 是原字符串，pairs 是可任意次交换的下标对，返回交换后字典序最小的串
        int n = s.size();  // n 是字符串长度
        int p[n];  // 并查集数组 p，p[i] 是下标 i 所在连通块的代表元
        iota(p, p + n, 0);  // iota 把 p 初始化为 0..n-1，每个下标自成一个集合
        vector<char> d[n];  // d[i] 存放根为 i 的连通块里的所有字符
        function<int(int)> find = [&](int x) -> int {  // 递归版查找函数，用 std::function 支持自引用
            if (p[x] != x) {  // 当前下标不是根，需要继续往上找
                p[x] = find(p[x]);  // 路径压缩：把沿途节点直接挂到根上
            }
            return p[x];  // 返回根节点
        };
        for (auto e : pairs) {  // 遍历所有可交换的下标对，把它们合并到同一连通块
            int a = e[0], b = e[1];  // 取出这一对的两个下标
            p[find(a)] = find(b);  // 合并：把 a 的根挂到 b 的根下面
        }
        for (int i = 0; i < n; ++i) {  // 按下标顺序把每个字符放进它所属的连通块
            d[find(i)].push_back(s[i]);  // s[i] 归入 find(i) 这个根对应的桶
        }
        for (auto& e : d) {  // 遍历每个连通块
            sort(e.rbegin(), e.rend());  // 块内降序排序（反向迭代器），配合后面的尾弹出即得升序
        }
        for (int i = 0; i < n; ++i) {  // 再按原下标顺序回填每个位置
            auto& e = d[find(i)];  // 取出下标 i 所属的桶
            s[i] = e.back();  // 从尾部弹出当前块中最小的字符，写回位置 i
            e.pop_back();  // 弹出后该字符从桶中移除
        }
        return s;  // 返回字典序最小的结果串
    }
};