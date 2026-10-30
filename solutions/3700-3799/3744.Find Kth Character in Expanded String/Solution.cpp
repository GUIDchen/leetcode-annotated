// 题目：3744. 在展开字符串中查找第 K 个字符（Find Kth Character in Expanded String）
// 核心思路：按单词逐个跳过。长度为 L 的单词展开后是「第 1 个字母重复 1 次、第 2 个字母重复 2 次……」共 L(L+1)/2 个字符；用 k 与这段长度 m 比较，k==m 正好落在词后空格上，k>m 就减去 m+1 继续看下一个词，否则在词内按 1,2,3,... 的累加区间定位字母。
// 复杂度：时间 O(|s|)，每个单词至多顺序扫一遍其字符；空间 O(|s|)，stringstream 复制了一份输入。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    char kthCharacter(string s, long long k) {  // s：由单个空格分隔的单词串；k：展开串 t 中 0 起的下标
        stringstream ss(s);  // 用字符串流按空白把 s 切成一个个单词
        string w;  // 当前正在处理的单词
        while (ss >> w) {  // 依次取出每个单词
            long long m = (1 + (long long) w.size()) * (long long) w.size() / 2;  // 该单词展开后的长度 = 1+2+...+L = L(L+1)/2
            if (k == m) {  // 恰好落在该单词展开部分之后的那一个分隔空格上
                return ' ';  // 返回这个空格
            }  // 空格判断结束
            if (k > m) {  // 第 k 个位置还在后面的单词里
                k -= m + 1;  // 跳过本单词展开的 m 个字符以及其后的一个空格
            } else {  // 否则第 k 个位置落在当前单词的展开部分内
                long long cur = 0;  // 当前已累计的字符数
                for (int i = 0;; ++i) {  // 逐个字母累加它的重复次数
                    cur += i + 1;  // 第 i 个字母被重复 i+1 次
                    if (k < cur) {  // k 落在第 i 个字母的重复区间内
                        return w[i];  // 返回这个字母
                    }  // 命中判断结束
                }  // 单词内定位结束
            }  // 分支结束
        }  // 单词遍历结束
        return ' ';  // 理论上不会走到这里，兜底返回空格
    }  // 方法结束
};  // 类定义结束
