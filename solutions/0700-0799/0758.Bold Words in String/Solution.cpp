// 题目：758. 字符串中的加粗单词（Bold Words in String）——中等（付费题）
// 思路：把所有关键词建成 Trie，枚举 s 的每个起点在 Trie 上匹配，得到一批被覆盖的区间，合并后再统一在原文上插入 <b>…</b>。
// 时间复杂度：O(n^2 + L)，n 为 s 长度、L 为所有关键词总长；空间复杂度：O(L * 128)，Trie 结点数，另加 O(n) 的区间数组。
class Trie {  // 字典树，用于快速判断某个前缀是否是关键词
public:  // 接口对外可见
    vector<Trie*> children;  // 128 个孩子指针，直接用字符的 ASCII 码当下标
    bool isEnd;  // 标记这里是否是某个关键词的结尾

    Trie() {  // 构造函数：初始化一个空结点
        children.resize(128);  // 预留全部 ASCII 位置，省去插入时的判空扩容
        isEnd = false;  // 新结点默认不是单词结尾
    }

    void insert(string word) {  // 把关键词 word 插入字典树
        Trie* node = this;  // 从根结点开始
        for (char c : word) {  // 逐字符沿树下行
            if (!node->children[c]) node->children[c] = new Trie();  // 该字符的子结点不存在就新建
            node = node->children[c];  // 走到子结点
        }
        node->isEnd = true;  // 最后一个字符所在结点标记为关键词结尾
    }
};

class Solution {  // LeetCode 约定的题解类
public:  // 接口对外可见
    string boldWords(vector<string>& words, string s) {  // words 是关键词表，s 是待加粗的原串
        Trie* trie = new Trie();  // 建一棵空字典树
        for (string w : words) trie->insert(w);  // 把所有关键词插进 Trie
        int n = s.size();  // 原串长度
        vector<pair<int, int>> pairs;  // 收集所有被关键词覆盖的区间 [起点, 终点]
        for (int i = 0; i < n; ++i) {  // 枚举每个起点
            Trie* node = trie;  // 每个起点都从根重新开始匹配
            for (int j = i; j < n; ++j) {  // 从 i 开始向右延伸
                int idx = s[j];  // 当前字符的 ASCII 码，正好作为孩子下标
                if (!node->children[idx]) break;  // Trie 上走不下去，说明再长也不可能是关键词
                node = node->children[idx];  // 沿着 Trie 向下走
                if (node->isEnd) pairs.push_back({i, j});  // 走到关键词结尾，记录这一段的覆盖区间
            }
        }
        if (pairs.empty()) return s;  // 一个关键词都没匹配到，原样返回
        vector<pair<int, int>> t;  // 合并后互不重叠的区间
        int st = pairs[0].first, ed = pairs[0].second;  // 用第一个区间初始化当前合并段
        for (int i = 1; i < pairs.size(); ++i) {  // 顺序扫描其余区间（pairs 天然按起点递增）
            int a = pairs[i].first, b = pairs[i].second;  // 当前区间
            if (ed + 1 < a) {  // 与当前合并段不相邻，也不重叠
                t.push_back({st, ed});  // 收束当前合并段
                st = a, ed = b;  // 从当前区间重新开始合并
            } else
                ed = max(ed, b);  // 重叠或首尾相邻，把右端点扩展到更远的一侧
        }
        t.push_back({st, ed});  // 别忘了把最后一段合并结果收进去
        string ans = "";  // 拼装最终字符串
        int i = 0, j = 0;  // i 是原串上的游标，j 是当前待处理的合并区间下标
        while (i < n) {  // 扫描完整个原串为止
            if (j == t.size()) {  // 所有区间都处理完，剩下的都是普通文本
                ans += s.substr(i);  // 一次性拼接剩余部分
                break;  // 结束
            }
            st = t[j].first, ed = t[j].second;  // 取出当前合并区间
            if (i < st) ans += s.substr(i, st - i);  // 先原样拷贝区间之前的普通文本
            ans += "<b>";  // 加粗开始标签
            ans += s.substr(st, ed - st + 1);  // 加粗区间内的子串
            ans += "</b>";  // 加粗结束标签
            i = ed + 1;  // 游标跳过整个已加粗区间
            ++j;  // 处理下一个合并区间
        }
        return ans;  // 返回加粗后的字符串
    }
};