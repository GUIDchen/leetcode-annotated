// 题目：126. 单词接龙 II（Word Ladder II）
// 思路：先用 BFS 按层建图，用 dist 记录每个单词首次被访问的层数、prev 记录它在上一层的全部前驱（只保留最短路径上的边）；再用 DFS 从 endWord 逆着前驱边回溯出所有最短序列。
// 时间复杂度：O(n·L·26)，n 是词表大小、L 是单词长度（路径输出另计）；空间复杂度：O(n·L)，用于存图与答案。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {  // 返回从 beginWord 到 endWord 的所有最短转换序列
        vector<vector<string>> ans;  // 收集所有最短路径
        unordered_set<string> words(wordList.begin(), wordList.end());  // 词表转哈希集合，便于 O(1) 判断某个单词是否可用
        if (!words.count(endWord)) {  // 终点词不在词表中
            return ans;  // 永远无法到达，直接返回空答案
        }  // if 结束
        words.erase(beginWord);  // 起点从集合中移除，防止 BFS 再次走回起点
        unordered_map<string, int> dist{{beginWord, 0}};  // 记录每个单词第一次被访问时的层号
        unordered_map<string, unordered_set<string>> prev;  // 记录每个单词在上一层的所有前驱，用于最后回溯路径
        queue<string> q{{beginWord}};  // BFS 队列，初始只放起点词
        bool found = false;  // 标记是否已经扩展到终点
        int step = 0;  // 当前 BFS 层号
        while (!q.empty() && !found) {  // 队列非空且还没找到终点就继续扩展
            ++step;  // 进入下一层
            for (int i = q.size(); i > 0; --i) {  // 先记下本层节点数，逐层处理
                string p = q.front();  // 取出队首单词作为当前节点
                q.pop();  // 弹出
                string t = p;  // 复制一份用于逐位替换字符
                for (int j = 0; j < t.size(); ++j) {  // 枚举要替换的位置
                    char ch = t[j];  // 暂存原字符，回溯时恢复
                    for (char k = 'a'; k <= 'z'; ++k) {  // 枚举 26 个字母生成邻居
                        t[j] = k;  // 得到一个新单词
                        if (dist.count(t) && dist[t] == step) {  // 该单词已在当前层被访问过，说明还有一条同样短的前驱边
                            prev[t].insert(p);  // 补充一条前驱关系
                        }  // if 结束
                        if (!words.count(t)) {  // 新单词不在可用词表中（已用过或根本不存在）
                            continue;  // 跳过
                        }  // if 结束
                        prev[t].insert(p);  // 记录 p 是 t 的前驱
                        words.erase(t);  // 从词表移除，保证每个单词只入队一次
                        q.push(t);  // 入队，留到下一层扩展
                        dist[t] = step;  // 记录它被访问的层号
                        if (t == endWord) {  // 命中了终点词
                            found = true;  // 标记已找到，外层循环结束时就能停止继续扩展
                        }  // if 结束
                    }  // 字母枚举结束
                    t[j] = ch;  // 恢复原字符，再尝试替换下一个位置
                }  // 位置枚举结束
            }  // 本层处理结束
        }  // BFS 结束
        function<void(vector<string>&, const string&)> dfs = [&](vector<string>& path, const string& cur) {  // 逆着 prev 中的前驱边回溯路径
            if (cur == beginWord) {  // 已经倒推回起点，说明找到一条完整路径
                ans.emplace_back(path.rbegin(), path.rend());  // 当前 path 是逆序的，反转后加入答案
                return;  // 一条路径收集完毕
            }  // if 结束
            for (const string& precursor : prev[cur]) {  // 枚举 cur 在上一层的所有前驱
                path.push_back(precursor);  // 前驱加入路径
                dfs(path, precursor);  // 继续向前回溯
                path.pop_back();  // 恢复现场，尝试下一个前驱
            }  // for 结束
        };  // lambda 定义结束
        if (found) {  // 只有真正到达过终点才需要回溯
            vector<string> path{endWord};  // 从终点开始倒着收集路径
            dfs(path, endWord);  // 启动回溯
        }  // if 结束
        return ans;  // 返回所有最短转换序列
    }  // findLadders 结束
};
