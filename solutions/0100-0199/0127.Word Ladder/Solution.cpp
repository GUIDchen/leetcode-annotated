// 题目：127. 单词接龙（Word Ladder）
// 思路：把每个单词看作图上的节点，BFS 逐层扩展（每次只改动一个字母），第一次碰到 endWord 时的层数就是最短转换序列长度。
// 时间复杂度：O(n·L·26)，n 为词表大小、L 为单词长度；空间复杂度：O(n·L)，队列与哈希集合的开销。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {  // 返回从 beginWord 到 endWord 的最短转换序列长度
        unordered_set<string> words(wordList.begin(), wordList.end());  // 词表转哈希集合，便于 O(1) 查询与删除
        queue<string> q{{beginWord}};  // BFS 队列，初始只有起点词
        int ans = 1;  // 序列长度从 1 开始（起点本身算一个词）
        while (!q.empty()) {  // 队列非空说明还能继续扩展
            ++ans;  // 每扩展一层，序列长度加一
            for (int i = q.size(); i > 0; --i) {  // 先记下本层节点数，实现逐层 BFS
                string s = q.front();  // 取出队首单词
                q.pop();  // 弹出
                for (int j = 0; j < s.size(); ++j) {  // 枚举要替换的位置
                    char ch = s[j];  // 暂存原字符，回溯时恢复
                    for (char k = 'a'; k <= 'z'; ++k) {  // 枚举 26 个字母生成邻居
                        s[j] = k;  // 得到一个新单词
                        if (!words.count(s)) continue;  // 不在词表里就跳过
                        if (s == endWord) return ans;  // 第一次遇到终点，当前层数就是最短长度
                        q.push(s);  // 入队，留到下一层扩展
                        words.erase(s);  // 从词表删除，避免重复访问
                    }  // 字母枚举结束
                    s[j] = ch;  // 恢复原字符，尝试下一个位置
                }  // 位置枚举结束
            }  // 本层处理结束
        }  // while 结束
        return 0;  // 队列耗尽仍未到达终点，返回 0
    }  // ladderLength 结束
};