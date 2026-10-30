// 题目：2288. 价格减免（Apply Discount to Prices）
// 核心思路：用字符串流按空格切词，逐词判断是否为「$ + 纯数字」的合法价格；是则换成整数后乘 (100 - discount)，再按分（0.01 元）格式化回两位小数，非价格单词原样拼回。
// 时间复杂度：O(L)，L 为句子长度，每个字符只被扫描常数次；空间复杂度：O(L)，存放结果字符串与切分出的单词。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string discountPrices(string sentence, int discount) {  // sentence：原句；discount：折扣百分比；返回替换价格后的句子
        istringstream is(sentence);  // 用字符串流把句子按空格切分成一个个单词
        string w;  // 接收当前读到的单词
        string ans;  // 存放最终结果
        auto check = [](string s) {  // 辅助 lambda：判断一个单词是否为合法价格（$ 后全是数字）
            if (s[0] != '$' || s.size() == 1) {  // 不以 $ 开头，或者只有 $ 没有数字
                return false;  // 判定为非价格
            }  // 判断结束
            for (int i = 1; i < s.size(); ++i) {  // 逐个检查 $ 后面的字符
                if (!isdigit(s[i])) {  // 出现非数字字符（小数点、字母等）
                    return false;  // 判定为非价格
                }  // 判断结束
            }  // 循环结束
            return true;  // $ 后全是数字，是合法价格
        };  // lambda 定义结束
        while (is >> w) {  // 逐个读出单词，流读不出时结束
            if (check(w)) {  // 当前单词是价格，需要打折
                long long v = stoll(w.substr(1)) * (100 - discount);  // 去掉 $ 转成整数再乘 (100-discount)，此时单位是 0.01 元
                char t[20];  // 存放格式化后的价格文本
                sprintf(t, "$%lld.%02lld", v / 100, v % 100);  // 按「整数部分.两位小数」格式化：v/100 是元，v%100 是分
                ans += t;  // 把打折后的价格拼进结果
            } else {  // 当前单词不是价格，原样保留
                ans += w;  // 直接拼接原单词
            }  // 分支结束
            ans += ' ';  // 每个单词后补一个空格作为分隔符
        }  // 单词读完，循环结束
        ans.pop_back();  // 去掉末尾多加的那个空格
        return ans;  // 返回处理后的句子
    }  // 方法结束
};  // 类定义结束