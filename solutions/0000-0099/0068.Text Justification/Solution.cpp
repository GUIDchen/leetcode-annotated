// 题目：68. 文本左右对齐（Text Justification）
// 思路：先贪心地把能塞进一行的单词都取出，再按是否是最后一行/单个单词决定左对齐或两端对齐：空格总数按间隙均分，余下的补在左边几个间隙。
// 时间复杂度：O(N·L)，N 为单词数、L 为 maxWidth，每个字符都要写进结果；空间复杂度：O(N·L)，存放返回的全部行。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> fullJustify(vector<string>& words, int maxWidth) {  // words：单词表；maxWidth：每行宽度
        vector<string> ans;  // 保存已经排好的每一行
        for (int i = 0, n = words.size(); i < n;) {  // i 是当前行第一个单词的下标；循环体内 i 自行推进，故不写 ++i
            vector<string> t = {words[i]};  // 本行先放入第一个单词
            int cnt = words[i].size();  // cnt：本行单词总长度 + 已预留的单词间空格数（至少一个空格）
            ++i;  // 指针后移，准备尝试后续单词
            while (i < n && cnt + 1 + words[i].size() <= maxWidth) {  // 若再加一个单词（含一个分隔空格）仍不超宽，就继续装
                cnt += 1 + words[i].size();  // 累加这个单词的长度和它前面的那个空格
                t.emplace_back(words[i++]);  // 单词收入本行，同时把指针推进到下一个单词
            }
            if (i == n || t.size() == 1) {  // 最后一行或本行只有一个单词：按规则必须左对齐
                string left = t[0];  // 用第一个单词开始拼这一行
                for (int j = 1; j < t.size(); ++j) {  // 依次把其余单词接上来
                    left += " " + t[j];  // 单词之间只放一个空格
                }
                string right = string(maxWidth - left.size(), ' ');  // 右侧用空格补齐到 maxWidth
                ans.emplace_back(left + right);  // 左对齐的行直接入答案
                continue;  // 本行处理完毕，处理下一行
            }
            int spaceWidth = maxWidth - (cnt - t.size() + 1);  // 可分配的空格总数 = 行宽 - 纯字母总长（cnt 里多算了 t.size()-1 个空格，要还回去）
            int w = spaceWidth / (t.size() - 1);  // 每个间隙先均分到 w 个空格
            int m = spaceWidth % (t.size() - 1);  // 除不尽的 m 个空格要分给最左边 m 个间隙
            string row;  // 逐步拼接本行的内容
            for (int j = 0; j < t.size() - 1; ++j) {  // 遍历除最后一个单词外的所有单词（它们后面都要跟空格）
                row += t[j] + string(w + (j < m ? 1 : 0), ' ');  // 单词 + 均分空格，若 j 落在余数范围内再多补 1 个
            }
            row += t.back();  // 最后一个单词后面不加空格
            ans.emplace_back(row);  // 两端对齐的行入答案
        }
        return ans;  // 返回全部对齐后的行
    }
};