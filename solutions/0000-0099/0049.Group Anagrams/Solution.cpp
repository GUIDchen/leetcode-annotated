// 题目：49. 字母异位词分组（Group Anagrams）
// 核心思路：把每个字符串按字符排序，互为异位词的串排序后会完全相同，用它当哈希表的键就能自然分组。
// 时间复杂度：O(n·k log k)，k 为串长，主要开销是排序；空间复杂度：O(n·k)，存放所有字符串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<string>> groupAnagrams(vector<string>& strs) {  // strs 是字符串数组，把互为字母异位词的串分到同一组
        unordered_map<string, vector<string>> d;  // 哈希表：键是排序后的字符串（异位词共用的签名），值是同组的原串列表
        for (auto& s : strs) {  // 逐个处理输入字符串
            string k = s;  // 复制一份用于排序，避免破坏原串
            sort(k.begin(), k.end());  // 排序后异位词得到同一串代码，正好当作分组键
            d[k].emplace_back(s);  // 用这个键把原串追加到对应分组里，键不存在会自动创建空列表
        }
        vector<vector<string>> ans;  // 收集所有分组，按哈希表遍历顺序输出，顺序不影响判题
        for (auto& [_, v] : d) ans.emplace_back(v);  // 结构化绑定同时取出键和值，未使用的键用 _ 占位
        return ans;  // 返回分组结果
    }
};
