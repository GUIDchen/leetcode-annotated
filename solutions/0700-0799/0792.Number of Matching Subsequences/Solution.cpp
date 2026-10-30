// 题目：792. 匹配子序列的单词数（Number of Matching Subsequences）
// 思路：按「下一个待匹配字符」把候选串分成 26 个桶；顺序扫母串 s，遇到字符 c 就把 c 桶里的串推进一格，匹配完的计数。
// 时间复杂度：O(|s| + 所有候选串总长)，每个字符只会被推进一次；空间复杂度：O(所有候选串总长)，桶里保存剩余后缀。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numMatchingSubseq(string s, vector<string>& words) {  // s 是母串，words 是候选串列表，返回其中是 s 子序列的个数
        vector<queue<string>> d(26);  // 26 个桶：d[c] 存「下一个待匹配字符是 c」的所有候选串
        for (auto& w : words) d[w[0] - 'a'].emplace(w);  // 按首字符把每个候选串放进对应桶
        int ans = 0;  // 匹配成功的计数
        for (char& c : s) {  // 顺序扫描母串的每个字符，保证子序列必须保持原顺序
            auto& q = d[c - 'a'];  // 取出期望匹配 c 的那个桶（引用，避免拷贝）
            for (int k = q.size(); k; --k) {  // 只处理进入本轮前就在桶里的串；本轮新入桶的串要等后面的字符再处理
                auto t = q.front();  // 取出队首候选串（拷贝一份，后面要改）
                q.pop();  // 把它从当前桶移除
                if (t.size() == 1)  // 若只剩一个字符，说明这是该候选串最后一个待匹配字符
                    ++ans;  // 该串确实是子序列，计数加一
                else  // 否则还有剩余字符待匹配
                    d[t[1] - 'a'].emplace(t.substr(1));  // 去掉首字符后按新首字符重新入桶
            }  // 本桶本轮处理的串数已固定，循环结束
        }  // 母串扫描结束
        return ans;  // 返回匹配成功的总数
    }  // 方法结束
};  // 题解类结束