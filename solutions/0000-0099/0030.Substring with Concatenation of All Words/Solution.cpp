// 题目：30. 串联所有单词的子串（Substring with Concatenation of All Words）
// 思路：所有单词长度都是 k，所以串联子串的起点只能落在 i ∈ [0, k) 这 k 个「相位」上。对每个相位用步长 k 做滑动窗口：窗口内是一个个整词，用哈希表 cnt1 统计词频，一旦某个词次数超过 cnt（或者遇到不在 words 里的词）就收缩左端，当窗口长度恰好为 n*k 时左端就是一个答案。
// 时间复杂度：O(m·k) 级别，m 是字符串长度，每个相位滑动窗口总移动 O(m/k) 次、每次哈希 O(k)；空间复杂度：O(n·k)，哈希表存 words 的单词。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> findSubstring(string s, vector<string>& words) {  // s：主串；words：等长单词表；返回所有串联子串的起始下标
        unordered_map<string, int> cnt;  // cnt：words 中每个单词需要的出现次数
        for (const auto& w : words) {  // 遍历单词表，用常引用避免拷贝
            cnt[w]++;  // 对应单词的计数加一
        }

        vector<int> ans;  // ans 收集所有合法起始下标
        int m = s.length(), n = words.size(), k = words[0].length();  // m 主串长度，n 单词个数，k 每个单词的长度（题目保证等长）

        for (int i = 0; i < k; ++i) {  // 枚举 k 个相位：起点 i 决定了切分单词的位置
            int l = i, r = i;  // 窗口左右边界，都以步长 k 移动；l 指向窗口内第一个单词的起点
            unordered_map<string, int> cnt1;  // cnt1：当前窗口内各单词的出现次数
            while (r + k <= m) {  // 只要 r 处还能切出一个完整的词，就继续向右扩
                string t = s.substr(r, k);  // 取出 r 处的整词 t
                r += k;  // 右边界右移一个词长

                if (!cnt.contains(t)) {  // C++20 的 contains：t 不在 words 里，窗口不可能再以 l 为起点成立
                    cnt1.clear();  // 清空窗口内的词频统计
                    l = r;  // 左指针直接跳到 r，从下一个词重新开始
                    continue;  // 跳过本轮剩余逻辑
                }

                cnt1[t]++;  // t 是合法单词，窗口计数加一

                while (cnt1[t] > cnt[t]) {  // t 出现次数超了，必须从左边不断吐出单词直到不超
                    string w = s.substr(l, k);  // 取出左端的整词 w
                    if (--cnt1[w] == 0) {  // 先把 w 的计数减一；减到 0 说明窗口里已经没有 w
                        cnt1.erase(w);  // 顺手删掉该键，避免哈希表里堆积无用的零值
                    }
                    l += k;  // 左边界右移一个词长
                }

                if (r - l == n * k) {  // 窗口长度正好等于 n 个单词的总长，说明恰好用完了全部单词
                    ans.push_back(l);  // 记录这个左端点作为答案
                }
            }
        }

        return ans;  // 返回全部答案下标
    }
};
