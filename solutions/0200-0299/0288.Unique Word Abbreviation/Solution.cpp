// 题目：288. 单词的唯一缩写（Unique Word Abbreviation）—— 判断某个单词的缩写是否唯一，即该缩写没有对应词典中其它单词。
// 核心思路：构造时按缩写把词典里的单词分组（缩写 -> 单词集合）；查询时看该缩写下是否只存在目标单词自己。
// 时间复杂度：构造 O(总字符数)，单次查询 O(1) 期望；空间复杂度：O(总字符数)，哈希表存下全部单词。
class ValidWordAbbr {  // 设计类：构造阶段建索引，查询阶段只查表
public:  // 对外接口
    ValidWordAbbr(vector<string>& dictionary) {  // dictionary：初始化词典（引用传参，避免拷贝整个列表）
        for (auto& s : dictionary) {  // 遍历词典里的每个单词
            d[abbr(s)].insert(s);  // 用缩写做键，把单词放进对应集合；set 顺带做了去重
        }
    }  // 构造结束，索引已建好

    bool isUnique(string word) {  // 判断 word 的缩写是否唯一
        string s = abbr(word);  // 先算出待查询单词的缩写
        return !d.count(s) || (d[s].size() == 1 && d[s].count(word));  // 缩写不存在 → 唯一；或该缩写下只有 word 自己（size==1 且就是 word）→ 也算唯一
    }

private:  // 以下是内部实现，不对外暴露
    unordered_map<string, unordered_set<string>> d;  // 哈希表：缩写 -> 该缩写对应的所有单词

    string abbr(string& s) {  // 计算缩写：长度 < 3 的单词原样返回
        int n = s.size();  // 单词长度
        return n < 3 ? s : s.substr(0, 1) + to_string(n - 2) + s.substr(n - 1, 1);  // 首字母 + 中间字符个数 + 末字母；短词（长度 < 3）没有中间部分，直接返回原串
    }
};

// 下面是 LeetCode 生成的调用代码说明，保留原样，仅作提示
/**
 * Your ValidWordAbbr object will be instantiated and called as such:
 * ValidWordAbbr* obj = new ValidWordAbbr(dictionary);
 * bool param_1 = obj->isUnique(word);
 */