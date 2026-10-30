// 3481. 应用替换 🔒（Apply Substitutions）
// 核心思路：把替换关系存成哈希表，用递归扫描字符串中成对的 %...% 占位符，先递归展开占位符对应的替换串，再拼接前缀与递归展开的后缀，从而支持多层嵌套。
// 复杂度：时间 O(L × 嵌套层数)，空间 O(L)（L 为展开后的字符串长度）
class Solution {  // 解题类
public:  // 公有成员
    string applySubstitutions(vector<vector<string>>& replacements, string text) {  // 返回把 text 中所有 %key% 占位符替换后的结果
        unordered_map<string, string> d;  // 从占位符名到替换字符串的映射
        for (const auto& e : replacements) {  // 依次读入每条替换规则
            d[e[0]] = e[1];  // 记录 key -> 替换内容
        }  // 结束读入替换规则
        auto dfs = [&](this auto&& dfs, const string& s) -> string {  // 递归函数：把 s 中的占位符全部展开（C++23 显式对象参数写法便于自递归）
            size_t i = s.find('%');  // 找到第一个 %
            if (i == string::npos) {  // 没有占位符起始符
                return s;  // 原样返回
            }  // 结束判断
            size_t j = s.find('%', i + 1);  // 找到与之配对的第二个 %
            if (j == string::npos) {  // 没有配对的结束符
                return s;  // 原样返回
            }  // 结束判断
            string key = s.substr(i + 1, j - i - 1);  // 截取两个 % 之间的占位符名
            string replacement = dfs(d[key]);  // 先递归展开该占位符对应的替换串，避免遗留嵌套占位符
            return s.substr(0, i) + replacement + dfs(s.substr(j + 1));  // 拼接：前缀 + 展开后的替换内容 + 递归展开的后缀
        };  // 结束递归函数
        return dfs(text);  // 从整串 text 开始递归展开
    }  // 结束方法
};  // 结束类定义
