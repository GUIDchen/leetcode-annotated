// 题目：269. 火星词典（Alien Dictionary）
// 思路：相邻单词第一个不同的字母给出字母间的先后关系，据此建有向图再拓扑排序；若成环或顺序矛盾则返回空串。
// 时间复杂度：O(C + 26²)，C 为所有单词的总字符数；空间复杂度：O(26²)，邻接矩阵大小固定。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解法接口
    string alienOrder(vector<string>& words) {  // words 是按外星字母序排好的单词表，返回还原出的字母顺序
        vector<vector<bool>> g(26, vector<bool>(26));  // 邻接矩阵：g[i][j] 为真表示字母 i 排在字母 j 前面
        vector<bool> s(26);  // s[i] 记录字母 i 是否在输入里出现过
        int cnt = 0;  // cnt 统计一共出现了多少种不同字母
        int n = words.size();  // 单词个数
        for (int i = 0; i < n - 1; ++i) {  // 相邻两两比较，共 n-1 对
            for (char c : words[i]) {  // 先把当前单词里的字母登记为已出现
                if (cnt == 26) break;  // 26 个字母都齐了就不用再统计
                c -= 'a';  // 把字符转成 0..25 的下标
                if (!s[c]) {  // 第一次见到这个字母
                    ++cnt;  // 不同字母计数加一
                    s[c] = true;  // 标记为已出现
                }  // 字母登记结束
            }  // 当前单词长度
            int m = words[i].size();  // 逐位比较当前单词与下一个单词
            for (int j = 0; j < m; ++j) {  // 出现前缀情况（长词排在短词前），顺序非法，返回空串
                if (j >= words[i + 1].size()) return "";  // 取同一位上的两个字母
                char c1 = words[i][j], c2 = words[i + 1][j];  // 相同就继续找下一个不同位
                if (c1 == c2) continue;  // 已经存在反向边，说明出现矛盾，返回空串
                if (g[c2 - 'a'][c1 - 'a']) return "";  // 记录 c1 排在 c2 前面
                g[c1 - 'a'][c2 - 'a'] = true;  // 第一个不同字母就是唯一的先后关系，后面的不用再看
                break;  // 相邻单词比较结束
            }  // 最后一对比较结束
        }  // 最后一个单词没有后继，单独补登记它的字母
        for (char c : words[n - 1]) {  // 26 个字母都齐了就不用再统计
            if (cnt == 26) break;  // 转成 0..25 的下标
            c -= 'a';  // 第一次见到这个字母
            if (!s[c]) {  // 计数加一
                ++cnt;  // 标记为已出现
                s[c] = true;  // 最后一个单词登记结束
            }  // 统计每个字母的入度
        }  // 遍历所有起点字母
        vector<int> indegree(26);  // 遍历所有终点字母
        for (int i = 0; i < 26; ++i)  // 只统计出现过的字母之间的边
            for (int j = 0; j < 26; ++j)  // 终点字母的入度加一
                if (i != j && s[i] && s[j] && g[i][j])  // 拓扑排序用的队列
                    ++indegree[j];  // 找出所有入度为 0 的字母作为起点
        queue<int> q;  // 只考虑出现过的字母
        for (int i = 0; i < 26; ++i)  // 入度为 0 即可以作为当前最靠前的字母
            if (s[i] && indegree[i] == 0)  // 入队
                q.push(i);  // 用字符拼接答案，从字母序最靠前的开始
        string ans = "";  // 队列非空就继续取出
        while (!q.empty()) {  // 取队首字母的下标
            int t = q.front();  // 转回字符并追加到答案
            ans += (t + 'a');  // 出队
            q.pop();  // 删除它指向的边
            for (int i = 0; i < 26; ++i)  // 只处理出现过的字母
                if (i != t && s[i] && g[t][i])  // 只需考虑这条边真实存在的后继
                    if (--indegree[i] == 0)  // 后继入度减一，减到 0 说明它前面的字母都排完了
                        q.push(i);  // 后继入队
        }  // 拓扑排序结束
        return ans.size() < cnt ? "" : ans;  // 排出的字母少于实际出现过的字母数，说明成环，返回空串
    }  // 方法结束
};  // 类定义结束