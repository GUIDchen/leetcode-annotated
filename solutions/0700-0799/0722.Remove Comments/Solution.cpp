// 题目：722. 删除注释（Remove Comments）
// 思路：按行内字符逐位扫描，维护「是否处于块注释」状态；块注释可能跨行，因此用缓冲 t 把被切开的多行重新拼成一行。
// 时间复杂度：O(N)，N 为源码总字符数；空间复杂度：O(N)，输出占用的空间。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> removeComments(vector<string>& source) {  // source：按行给出的源码
        vector<string> ans;  // 保存删除注释后的各行
        string t;  // 当前正在拼接的行（跨行块注释会把多行合并成一行）
        bool blockComment = false;  // 是否处于 /* */ 块注释内部
        for (auto& s : source) {  // 逐行扫描源码
            int m = s.size();  // 当前行的长度
            for (int i = 0; i < m; ++i) {  // 逐字符扫描当前行
                if (blockComment) {  // 处于块注释中，只需寻找结束标记
                    if (i + 1 < m && s[i] == '*' && s[i + 1] == '/') {  // 找到块注释结束标记
                        blockComment = false;  // 退出块注释状态
                        ++i;  // 跳过 '/'，避免它再被当成普通字符
                    }  // 内层 if 结束
                } else {  // 不在块注释中，需要识别注释开头与普通字符
                    if (i + 1 < m && s[i] == '/' && s[i + 1] == '*') {  // 遇到 /* ，块注释开始
                        blockComment = true;  // 进入块注释状态
                        ++i;  // 跳过 '*'
                    } else if (i + 1 < m && s[i] == '/' && s[i + 1] == '/') {  // 遇到 // ，行注释开始
                        break;  // 本行剩余内容全部丢弃
                    } else {  // 既不是注释开头也不是块注释内部
                        t.push_back(s[i]);  // 普通字符，追加到当前行缓冲
                    }  // if 结束
                }  // 块注释状态分支结束
            }  // 本行扫描结束
            if (!blockComment && !t.empty()) {  // 不在块注释中且缓冲非空，说明一行输出已完成
                ans.emplace_back(t);  // 收集这一行
                t.clear();  // 清空缓冲，准备下一行
            }  // if 结束
        }  // for 循环结束
        return ans;  // 返回删除注释后的源码行
    }  // 方法结束
};  // 类定义结束