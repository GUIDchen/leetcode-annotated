// 3612. Process String with Special Operations I / 用特殊操作处理字符串 I
// 核心思路：按顺序模拟四种操作——小写字母追加、星号删除末尾、井号复制整串、百分号反转整串。
// 复杂度：时间复杂度 O(n^2)（井号复制使串长翻倍），空间复杂度 O(n)，n 为操作串长度。
class Solution {  // 定义题解类
public:  // 公有成员：对外提供 processStr
    string processStr(string s) {  // 按操作序列模拟构造最终字符串
        string result;  // 用空串暂存当前结果
        for (char c : s) {  // 顺序扫描每个操作字符
            if (isalpha(c)) {  // 情况一：当前字符是英文字母
                result += c;  // 直接把字母追加到末尾
            } else if (c == '*') {  // 情况二：星号表示删除末尾字符
                if (!result.empty()) {  // 只有结果非空时才允许删除
                    result.pop_back();  // 弹出最后一个字符
                }  // 结束非空判断
            } else if (c == '#') {  // 情况三：井号表示复制当前整串
                result += result;  // 追加自身使长度翻倍
            } else if (c == '%') {  // 情况四：百分号表示反转整串
                ranges::reverse(result);  // 原地反转当前结果
            }  // 结束四种操作的分支判断
        }  // 结束遍历
        return result;  // 返回构造完成的字符串
    }  // 方法结束
};  // 类定义结束