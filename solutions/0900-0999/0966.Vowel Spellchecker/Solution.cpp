// 题目：966. 元音拼写检查器（Vowel Spellchecker）
// 思路：建三套索引——原始单词集合、小写到原词的映射、元音统一换成 '*' 的模式到原词的映射，查询时按这三级优先级依次匹配。
// 时间复杂度：O((|wordlist| + |queries|) * L)，L 为单词长度；空间复杂度：O(|wordlist| * L)，三套索引的存储。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries) {  // wordlist 是词典，queries 是待检查单词，返回与 queries 等长的匹配结果
        unordered_set<string> s(wordlist.begin(), wordlist.end());  // 集合：保存原始单词，用于第一优先级「完全相同」的匹配
        unordered_map<string, string> low;  // 映射：小写形式 -> 词典中首次出现的原始单词（第二优先级）
        unordered_map<string, string> pat;  // 映射：元音模糊化后的模式 -> 词典中首次出现的原始单词（第三优先级）
        auto f = [](string& w) {  // 辅助函数：把单词中的元音统一替换成 '*'，得到忽略大小写与元音差异的模式
            string res;  // 保存模式字符串
            for (char& c : w) {  // 逐字符扫描单词
                if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {  // 当前字符是元音（调用前已转小写）
                    res += '*';  // 元音一律替换成 '*'
                } else {  // 非元音分支
                    res += c;  // 辅音原样保留
                }  // 分支结束
            }  // 遍历结束
            return res;  // 返回模式串
        };  // lambda 定义结束
        for (const auto& w : wordlist) {  // 遍历词典，建立两套低优先级索引
            string t = w;  // 复制一份单词，准备转小写
            transform(t.begin(), t.end(), t.begin(), ::tolower);  // 统一转成小写，供第二、第三优先级使用
            if (!low.contains(t)) {  // 只有该小写形式首次出现时才记录，保证取到词典中最靠前的原词
                low[t] = w;  // 记录小写形式到原始单词的映射
            }  // 首次出现判断结束
            t = f(t);  // 在转小写的基础上再做元音模糊化
            if (!pat.contains(t)) {  // 同一模式首次出现时才记录，保证取到词典中最靠前的原词
                pat[t] = w;  // 记录模式到原始单词的映射
            }  // 首次出现判断结束
        }  // 词典遍历结束
        vector<string> ans;  // 存放每个查询的答案
        for (auto& q : queries) {  // 按顺序处理每个查询词
            if (s.contains(q)) {  // 第一优先级：词典中存在完全相同的单词
                ans.emplace_back(q);  // 原样返回该单词
                continue;  // 直接处理下一个查询
            }  // 完全相同判断结束
            transform(q.begin(), q.end(), q.begin(), ::tolower);  // 第二优先级：忽略大小写，先把查询词转成小写
            if (low.contains(q)) {  // 小写形式在词典中出现过
                ans.emplace_back(low[q]);  // 返回词典中对应的原始拼写
                continue;  // 继续下一个查询
            }  // 大小写匹配判断结束
            q = f(q);  // 第三优先级：把查询词的元音也模糊化
            if (pat.contains(q)) {  // 模糊模式在词典中出现过
                ans.emplace_back(pat[q]);  // 返回词典中对应的原始拼写
                continue;  // 继续下一个查询
            }  // 元音模糊匹配判断结束
            ans.emplace_back("");  // 三级都匹配不上，用空串表示无匹配
        }  // 查询遍历结束
        return ans;  // 返回全部查询的结果
    }  // 方法结束
};  // 题解类结束
