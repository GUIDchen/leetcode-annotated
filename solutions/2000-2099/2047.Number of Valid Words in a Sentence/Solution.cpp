// 题目：2047. 句子中的有效单词数（Number of Valid Words in a Sentence）
// 思路：按空白切出每个 token，逐个字符校验：不能有数字，标点只能出现在末尾，连字符最多一个且两边必须是字母；合法就计数。
// 时间复杂度：O(L)，L 为句子总长度；空间复杂度：O(L)，stringstream 复制了一份句子。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countValidWords(string sentence) {  // sentence：输入句子；返回其中有效单词的个数
        auto check = [](const string& s) -> int {  // 内部 lambda：判断一个 token 是否有效，返回 1/0 便于直接累加
            bool st = false;  // st 记录本单词里是否已经用过一个连字符（最多允许一个）
            for (int i = 0; i < s.length(); ++i) {  // 逐字符检查这个 token
                if (isdigit(s[i])) {  // 出现数字，这个单词一定无效
                    return 0;  // 直接判为无效
                }  // 结束数字判断
                if ((s[i] == '!' || s[i] == '.' || s[i] == ',') && i < s.length() - 1) {  // 标点只允许出现在单词末尾，出现在中间就无效
                    return 0;  // 判为无效
                }  // 结束标点判断
                if (s[i] == '-') {  // 遇到连字符，开始合法性检查
                    if (st || i == 0 || i == s.length() - 1) {  // 连字符不能出现两次，也不能在单词首或尾
                        return 0;  // 判为无效
                    }  // 结束位置检查
                    if (!isalpha(s[i - 1]) || !isalpha(s[i + 1])) {  // 连字符左右两边必须都是字母
                        return 0;  // 判为无效
                    }  // 结束两侧字符检查
                    st = true;  // 标记本单词的连字符已经用过
                }  // 结束连字符分支
            }  // 结束逐字符循环
            return 1;  // 全部检查通过，这个 token 是有效单词
        };  // lambda 定义结束

        int ans = 0;  // ans：有效单词计数器
        stringstream ss(sentence);  // 用 stringstream 按空白把句子切成一个个 token
        string s;  // s 用来接住每次切出来的 token
        while (ss >> s) {  // 不断取出下一个 token
            ans += check(s);  // 有效单词就让计数加一
        }  // 结束取词循环
        return ans;  // 返回有效单词总数
    }  // 方法结束
};  // 题解类结束
