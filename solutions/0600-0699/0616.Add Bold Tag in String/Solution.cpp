// 题目：616. 给字符串添加加粗标签（Add Bold Tag in String）🔒
// 思路：字典树存下所有目标单词，枚举每个起点匹配出全部可加粗区间，合并相交/相邻区间后再拼上 <b> 标签。
// 时间复杂度：O(n^2 + 所有单词总长)，每个起点最多向右匹配 n 个字符；空间复杂度：O(所有单词总长)，即字典树节点数。
class Trie {  // 字典树节点：把 words 挂到树上，便于从任意位置向后贪心匹配
public:  // 成员对外可见
    vector<Trie*> children;  // 128 个孩子指针，直接用字符的 ASCII 码当下标
    bool isEnd;  // 标记从根走到当前节点的路径是否构成一个完整单词

    Trie() {  // 构造函数：分配孩子数组并复位结尾标记
        children.resize(128);  // ASCII 可见字符共 128 个，槽位下标就是字符编码
        isEnd = false;  // 新节点默认不是任何单词的结尾
    }

    void insert(string word) {  // 把一个单词插入字典树
        Trie* node = this;  // 从根节点开始向下走
        for (char c : word) {  // 逐字符沿树下行
            if (!node->children[c]) node->children[c] = new Trie();  // 该前缀路径不存在时补建一个节点
            node = node->children[c];  // 移动到刚走过的孩子节点
        }
        node->isEnd = true;  // 单词最后一个字符所在节点打上结尾标记
    }
};

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string addBoldTag(string s, vector<string>& words) {  // s 是原字符串，words 是需要加粗的单词列表
        Trie* trie = new Trie();  // 建树，所有单词一次性插好，后面每个起点复用
        for (string w : words) trie->insert(w);  // 逐个单词插入字典树
        int n = s.size();  // 记录原串长度，后面多处要用
        vector<pair<int, int>> pairs;  // 收集所有需要加粗的闭区间 [i, j]
        for (int i = 0; i < n; ++i) {  // 枚举每个可能的匹配起点 i
            Trie* node = trie;  // 每个起点都从字典树根重新出发
            for (int j = i; j < n; ++j) {  // 从 i 开始向右逐字符扩展
                int idx = s[j];  // 用字符的 ASCII 码作为孩子下标
                if (!node->children[idx]) break;  // 树上没有这条分支，再往右也不可能匹配，直接跳出
                node = node->children[idx];  // 沿树下行到下一个字符
                if (node->isEnd) pairs.push_back({i, j});  // 走到单词结尾，说明区间 [i, j] 需要加粗
            }
        }
        if (pairs.empty()) return s;  // 一个可加粗区间都没有，原串原样返回
        vector<pair<int, int>> t;  // 存放合并后的区间，起点保持递增
        int st = pairs[0].first, ed = pairs[0].second;  // 用第一个区间初始化当前合并区间 [st, ed]
        for (int i = 1; i < pairs.size(); ++i) {  // pairs 按起点递增产生，可以顺序合并
            int a = pairs[i].first, b = pairs[i].second;  // 取出下一个待合并区间 [a, b]
            if (ed + 1 < a) {  // 中间有间隔，说明两段既不相交也不相邻
                t.push_back({st, ed});  // 当前合并区间封口
                st = a, ed = b;  // 换用新区间继续合并
            } else  // 否则说明两段相交或相邻
                ed = max(ed, b);  // 合并成一个更长区间，终点取较大者
        }
        t.push_back({st, ed});  // 最后一个合并区间入列
        string ans = "";  // 结果字符串，逐段拼接
        int i = 0, j = 0;  // i 扫描原串，j 扫描合并后的区间数组
        while (i < n) {  // 依次把「未覆盖字符」和「加粗片段」拼到结果里
            if (j == t.size()) {  // 区间已经用完
                ans += s.substr(i);  // 剩余部分整段照抄
                break;  // 拼完即可结束
            }
            st = t[j].first, ed = t[j].second;  // 取出当前要处理的合并区间
            if (i < st) ans += s.substr(i, st - i);  // 先把区间左侧不会被加粗的字符接上
            ans += "<b>";  // 写入加粗开始标签
            ans += s.substr(st, ed - st + 1);  // 区间内的整段字符原样输出
            ans += "</b>";  // 写入加粗结束标签
            i = ed + 1;  // i 跳过已经加粗的这部分
            ++j;  // 处理下一个区间
        }
        return ans;  // 返回加粗后的字符串
    }
};