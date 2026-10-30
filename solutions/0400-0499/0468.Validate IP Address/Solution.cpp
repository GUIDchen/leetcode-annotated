// 题目：468. 验证 IP 地址（Validate IP Address）
// 思路：先按点切分尝试 IPv4（四段、无前导零、0..255），再按冒号切分尝试 IPv6（八段、每段 1..4 位十六进制），都不满足则返回 Neither。
// 时间复杂度：O(L)，L 为地址串长度；空间复杂度：O(L)，存放切分出的各段字符串。
class Solution {  // LeetCode 约定的题解类
public:  // 对外接口
    string validIPAddress(string queryIP) {  // queryIP：待校验的地址串
        if (isIPv4(queryIP)) {  // 先按 IPv4 规则校验
            return "IPv4";  // 合法则返回 IPv4
        }  // 结束 IPv4 分支
        if (isIPv6(queryIP)) {  // 再按 IPv6 规则校验
            return "IPv6";  // 合法则返回 IPv6
        }  // 结束 IPv6 分支
        return "Neither";  // 两种都不是
    }  // 结束 validIPAddress

private:  // 以下为内部辅助函数
    bool isIPv4(const string& s) {  // 判断是否为合法 IPv4
        if (s.empty() || s.back() == '.') {  // 空串或以点结尾都不合法
            return false;  // 直接判负
        }  // 结束判空
        vector<string> ss = split(s, '.');  // 按点切分
        if (ss.size() != 4) {  // IPv4 必须恰好四段
            return false;  // 段数不对直接判负
        }  // 结束段数判断
        for (const string& t : ss) {  // 逐段校验
            if (t.empty() || (t.size() > 1 && t[0] == '0')) {  // 空段或多位前导零都不合法
                return false;  // 直接判负
            }  // 结束本段格式判断
            int x = convert(t);  // 转成整数并顺便校验字符
            if (x < 0 || x > 255) {  // 超出 0..255（含 -1）不合法
                return false;  // 直接判负
            }  // 结束范围判断
        }  // 结束逐段校验
        return true;  // 四段均合法
    }  // 结束 isIPv4

    bool isIPv6(const string& s) {  // 判断是否为合法 IPv6
        if (s.empty() || s.back() == ':') {  // 空串或以冒号结尾不合法
            return false;  // 直接判负
        }  // 结束判空
        vector<string> ss = split(s, ':');  // 按冒号切分
        if (ss.size() != 8) {  // IPv6 必须恰好八段
            return false;  // 段数不对直接判负
        }  // 结束段数判断
        for (const string& t : ss) {  // 逐段校验
            if (t.size() < 1 || t.size() > 4) {  // 每段长度必须是 1..4
                return false;  // 直接判负
            }  // 结束长度判断
            for (char c : t) {  // 逐字符校验
                if (!isxdigit(c)) {  // 只允许十六进制字符
                    return false;  // 直接判负
                }  // 结束字符判断
            }  // 结束本段字符遍历
        }  // 结束逐段校验
        return true;  // 八段均合法
    }  // 结束 isIPv6

    int convert(const string& s) {  // 把一段转成整数，出现非法字符时返回 -1
        int x = 0;  // 累积结果
        for (char c : s) {  // 逐字符累加
            if (!isdigit(c)) {  // 出现非数字字符
                return -1;  // 返回 -1 表示非法
            }  // 结束字符判断
            x = x * 10 + (c - '0');  // 累积十进制值
            if (x > 255) {  // 超过上限可提前返回
                return x;  // 返回超限值，调用方按 >255 判负
            }  // 结束超限判断
        }  // 结束字符遍历
        return x;  // 返回转换结果
    }  // 结束 convert

    vector<string> split(const string& s, char delimiter) {  // 按分隔符切分字符串
        vector<string> tokens;  // 存放切分出的各段
        string token;  // 当前正在读取的一段
        istringstream iss(s);  // 用字符串流逐段读取
        while (getline(iss, token, delimiter)) {  // 读到分隔符即得到一段
            tokens.push_back(token);  // 收进结果
        }  // 结束读取循环
        return tokens;  // 返回切分结果
    }  // 结束 split
};  // 结束 Solution 类