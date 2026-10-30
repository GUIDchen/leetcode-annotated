// 题目：320. 列举单词的全部缩写（Generalized Abbreviation）
// 思路：对后缀做递归枚举，dfs(i) 只需考虑「保留 word[i]」或「把 word[i..j-1] 缩写成数字 j-i」两种分支。
// 时间复杂度：O(2^n * n)，答案规模为 2^(n-1) 量级且每个答案要 O(n) 拼接；空间复杂度：O(2^n * n)，递归保存全部中间结果。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> generateAbbreviations(string word) {  // word：原单词；返回它的全部缩写形式
        int n = word.size();  // 单词长度，作为递归的终止边界
        function<vector<string>(int)> dfs = [&](int i) -> vector<string> {  // dfs(i) 返回后缀 word[i..] 的所有缩写，用 function 保存以便递归调用自身
            if (i >= n) {  // 下标已越过末尾，后缀为空
                return {""};  // 空后缀只有一种缩写：空串
            }  // 基线情形结束
            vector<string> ans;  // 收集当前后缀的全部缩写
            for (auto& s : dfs(i + 1)) {  // 情形一：保留 word[i] 本身，接着拼后缀的缩写
                string p(1, word[i]);  // 由 1 个字符 word[i] 构造单字符字符串
                ans.emplace_back(p + s);  // 把「字母 + 后缀缩写」放进答案
            }  // 情形一结束
            for (int j = i + 1; j <= n; ++j) {  // 情形二：把 word[i..j-1] 缩写成数字 j-i
                for (auto& s : dfs(j + 1)) {  // 枚举剩余后缀 word[j+1..] 的缩写
                    string p = j < n ? string(1, word[j]) : "";  // 数字后紧跟的字母；j 已越界时留空
                    ans.emplace_back(to_string(j - i) + p + s);  // 拼出「数字 + 字母 + 剩余缩写」
                }  // 内层后缀枚举结束
            }  // 缩写长度枚举结束
            return ans;  // 返回当前后缀的全部缩写
        };  // lambda 定义结束
        return dfs(0);  // 从整个单词的起点开始求全部缩写
    }  // 方法结束
};  // 类定义结束