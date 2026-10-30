// 题目：692. 前 K 个高频单词（Top K Frequent Words）
// 思路：哈希表统计词频，再把所有单词按下标排序（频次降序，频次相同则字典序升序），最后截取前 k 个。
// 时间复杂度：O(m log m)，m 为不同单词数（排序主导）；空间复杂度：O(m)，存词频表与结果。
class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {  // words 是单词列表，k 是要取出的个数，返回按出现频率降序排列的前 k 个单词
        unordered_map<string, int> cnt;  // 哈希表：键是单词，值是出现次数
        for (const auto& w : words) {  // 遍历单词列表逐个计数
            ++cnt[w];  // 对应单词的计数加一
        }
        vector<string> ans;  // 结果数组，先收集全部不同单词，排序后再截断
        for (const auto& [w, _] : cnt) {  // 用结构化绑定遍历词频表，w 是单词（第二个字段是次数，此处用不到）
            ans.push_back(w);  // 把单词放入待排序数组
        }
        ranges::sort(ans, [&](const string& a, const string& b) {  // C++20 ranges::sort 配合自定义比较器进行排序
            return cnt[a] > cnt[b] || (cnt[a] == cnt[b] && a < b);  // 比较规则：频次高的排前面；频次相同则字典序小的排前面
        });
        ans.resize(k);  // 只保留前 k 个高频单词
        return ans;  // 返回结果
    }
};
