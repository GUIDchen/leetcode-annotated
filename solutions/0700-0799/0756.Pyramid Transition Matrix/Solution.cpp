// 题目：756. 金字塔转换矩阵（Pyramid Transition Matrix）——中等
// 思路：先预处理「两个字母对 → 可生成的第三个字母集合」为位掩码，再用记忆化深搜逐层由底向上拼出新串，能缩到只剩一个字母就成功。
// 时间复杂度：O(n * 2^7 * 状态数)，每个 (底串, 已构造前缀) 状态只算一次；空间复杂度：O(状态数)，记忆化哈希表与递归栈的开销。
class Solution {  // LeetCode 约定的题解类
public:  // 接口对外可见
    int d[7][7];  // d[a][b] 的第 c 位为 1 表示 a、b 两个字母可以生成字母 c，用位掩码压缩集合
    unordered_map<string, bool> f;  // 记忆化：键是「已构造层的底串 + 当前正在拼出的新串前缀」

    bool pyramidTransition(string bottom, vector<string>& allowed) {  // bottom 是最底层串，allowed 是允许的三元组
        memset(d, 0, sizeof(d));  // 多组测试复用同一个对象实例，先把转移表清零
        for (auto& s : allowed) {  // 把每个允许三元组写进转移表
            int a = s[0] - 'A', b = s[1] - 'A';  // 三元组的前两个字母（映射成 0~6）
            d[a][b] |= 1 << (s[2] - 'A');  // 第三个字母以位的形式累加到对应格子里
        }
        return dfs(bottom, "");  // 从最底层开始，已拼出的新串为空
    }

    bool dfs(string& s, string t) {  // s 是当前这一层，t 是正在上层拼接出的新串前缀
        if (s.size() == 1) {  // 只剩一个字母，金字塔已经搭到顶点，成功
            return true;
        }
        if (t.size() + 1 == s.size()) {  // 新串已经拼够长度，可以开始搭下一层
            return dfs(t, "");  // 以 t 作为新的底层，前缀重新置空
        }
        string k = s + "." + t;  // 构造唯一的状态键：底串 + 分隔符 + 已拼前缀
        if (f.contains(k)) {  // C++20 的 contains：该状态算过就直接复用
            return f[k];
        }
        int a = s[t.size()] - 'A', b = s[t.size() + 1] - 'A';  // 取当前需要合并的相邻两个字母
        int cs = d[a][b];  // 这两个字母能生成的字母集合（位掩码）
        for (int i = 0; i < 7; ++i) {  // 枚举 7 个可能生成的字母
            if (cs >> i & 1) {  // 第 i 个字母确实可以生成
                if (dfs(s, t + (char) (i + 'A'))) {  // 把该字母接到前缀后继续尝试
                    f[k] = true;  // 这个状态能成功，记下来
                    return true;  // 只要一条路可行就立刻返回
                }
            }
        }
        f[k] = false;  // 所有可选字母都失败，记录该状态无解避免重复搜索
        return false;  // 当前状态无法完成搭塔
    }
};
