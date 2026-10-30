class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string toHexspeak(string num) {  // num：十进制数字字符串
        stringstream ss;  // 用字符串流完成十进制到十六进制的转换
        ss << hex << stol(num);  // stol 按十进制解析，hex 让输出使用十六进制
        string t = ss.str();  // 取出转换后的十六进制字符串
        for (int i = 0; i < t.size(); ++i) {  // 逐位检查并替换成魔术数字字符
            if (t[i] >= '2' && t[i] <= '9') return "ERROR";  // 出现 2~9 的位无法映射成字母，直接判定为 ERROR
            if (t[i] == '0')  // 遇到数字 0
                t[i] = 'O';  // 0 换成字母 O
            else if (t[i] == '1')  // 遇到数字 1
                t[i] = 'I';  // 1 换成字母 I
            else  // 其余是 a~f 的小写字母
                t[i] = t[i] - 32;  // 小写字母减 32 变成大写
        }  // 结束 for 循环
        return t;  // 返回转换并大写后的魔术数字
    }  // toHexspeak 方法结束
};  // Solution 类定义结束