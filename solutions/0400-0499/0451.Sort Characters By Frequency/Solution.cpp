// 题目：451. 根据字符出现频率排序（Sort Characters By Frequency）
// 思路：先统计每个字符的出现次数，再把出现过的字符按次数从大到小排序，最后按各自次数重复拼接成结果串。
// 时间复杂度：O(n + k log k)，n 为串长、k 为不同字符数；空间复杂度：O(k)，哈希表与字符列表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string frequencySort(string s) {  // s：待排序的字符串；返回按出现频率降序重排后的新串
        unordered_map<char, int> cnt;  // 哈希表：字符 → 它出现的次数
        for (char& c : s) {  // 顺序扫一遍原串，统计每个字符的频次
            ++cnt[c];  // 字符 c 的计数加一（首次出现时自动从 0 开始）
        }  // 结束频次统计
        vector<char> cs;  // 收集所有出现过的不同字符，供随后排序
        for (auto& [c, _] : cnt) {  // 结构化绑定遍历哈希表，这里只需要键 c，值用占位名忽略
            cs.push_back(c);  // 把该字符放入待排序列表
        }  // 结束收集
        sort(cs.begin(), cs.end(), [&](char& a, char& b) {  // 按频次降序排序，比较器按引用捕获 cnt 以便查次数
            return cnt[a] > cnt[b];  // 次数多的字符排在前面
        });  // 结束 sort 调用
        string ans;  // 结果串，按排好的顺序逐字符拼接
        for (char& c : cs) {  // 依次取出排好序的字符
            ans += string(cnt[c], c);  // 该字符重复 cnt[c] 次，整段拼到结果末尾
        }  // 结束拼接
        return ans;  // 返回按频率降序排列的结果串
    }  // 结束 frequencySort
};  // 结束 Solution 类