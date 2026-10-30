// 题目：1160. 拼写单词（Find Words That Can Be Formed by Characters）
// 思路：先统计 chars 各字母的可用次数，再逐词统计用量，任一字母超量则该词不可拼出。
// 时间复杂度：O(L)，L 为 chars 与所有单词的总长度；空间复杂度：O(1)（固定 26 个字母）。
class Solution {  // LeetCode 题解类
public:  // 解题方法对外公开
    int countCharacters(vector<string>& words, string chars) {  // words 是候选单词，chars 是可用字母集合
        int cnt[26]{};  // 统计 chars 中每个字母的可用次数，值初始化为 0
        for (char& c : chars) {  // 遍历可用字母
            ++cnt[c - 'a'];  // 对应字母计数加一
        }  // 结束统计
        int ans = 0;  // 能拼出的单词总长度
        for (auto& w : words) {  // 逐个检查每个单词
            int wc[26]{};  // 当前单词每个字母的用量，初始 0
            bool ok = true;  // 标记该单词能否被拼出
            for (auto& c : w) {  // 遍历单词中的字符
                int i = c - 'a';  // 映射到 0..25 的下标
                if (++wc[i] > cnt[i]) {  // 该字母用量超过可用数量
                    ok = false;  // 拼不出来
                    break;  // 提前结束检查
                }  // 结束用量检查分支
            }  // 结束字符遍历
            if (ok) {  // 全部字母都不缺
                ans += w.size();  // 把单词长度累加进答案
            }  // 结束该单词处理
        }  // 结束单词遍历
        return ans;  // 返回所有可拼出单词的总长度
    }  // 方法结束
};  // 类定义结束