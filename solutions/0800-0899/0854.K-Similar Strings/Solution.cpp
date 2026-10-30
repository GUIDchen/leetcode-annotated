// 题目：854. 相似度为 K 的字符串（K-Similar Strings）
// 思路：BFS 逐层扩展交换状态；每次固定最左侧的第一个不匹配位 i，只枚举能让 i 位变正确的交换 j，剪掉无效分支。
// 时间复杂度：最坏 O(n · 状态数)，实际远小于全排列；空间复杂度：O(状态数)，队列与访问集合。
class Solution {  // 题解类
public:
    int kSimilarity(string s1, string s2) {  // s1 与 s2 是长度相同的字符异位串，返回最少交换次数
        queue<string> q{{s1}};  // BFS 队列，起点是 s1
        unordered_set<string> vis{{s1}};  // 访问集合，防止同一状态重复入队
        int ans = 0;  // 当前 BFS 层数，即已用的交换次数
        while (1) {  // 逐层扩展，题目保证可达所以不会死循环
            for (int i = q.size(); i; --i) {  // 只处理当前这一层的所有状态
                auto s = q.front();  // 取队首状态
                q.pop();  // 出队
                if (s == s2) {  // 已经变成目标串
                    return ans;  // 当前层数就是最少交换次数
                }  // 未到达目标串
                for (auto& nxt : next(s, s2)) {  // 枚举所有值得尝试的一次交换结果
                    if (!vis.count(nxt)) {  // 只入队没访问过的状态
                        vis.insert(nxt);  // 标记为已访问
                        q.push(nxt);  // 加入队列，留待下一层扩展
                    }  // 访问判断结束
                }  // 后继遍历结束
            }  // 本层处理完毕
            ++ans;  // 一层结束，交换次数加一
        }  // 外层循环结束
    }  // 方法结束

    vector<string> next(string& s, string& s2) {  // 生成 s 所有「值得尝试」的一次交换结果
        int i = 0, n = s.size();  // i 指向第一个与 s2 不匹配的位置，n 为串长
        for (; s[i] == s2[i]; ++i) {}  // 跳过前缀中已经匹配的字符
        vector<string> res;  // 保存交换后的新串
        for (int j = i + 1; j < n; ++j) {  // 在 i 之后寻找可以交换的位置
            if (s[j] == s2[i] && s[j] != s2[j]) {  // j 上的字符正是 i 位需要的，且交换后 j 位也能改善，这样的交换才有效
                swap(s[i], s[j]);  // 试探性交换 i、j
                res.push_back(s);  // 记录交换后的状态
                swap(s[i], s[j]);  // 回溯恢复原串，以便尝试下一个 j
            }  // 有效交换判断结束
        }  // 候选位置遍历结束
        return res;  // 返回这一层的所有后继状态
    }  // 辅助方法结束
};  // 题解类结束