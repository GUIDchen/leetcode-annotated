// 题目：1694. 重新格式化电话号码（Reformat Phone Number）
// 思路：先删掉空格和短横线得到纯数字串；再按每 3 位分组，末尾余 1 位时把最后一组拆成 2+2，余 2 位时单独加一组 2 位。
// 时间复杂度：O(n)，只做常数次线性扫描与拼接；空间复杂度：O(n)，需要存放纯数字串与分组结果。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string reformatNumber(string number) {  // number：可能含空格与 '-' 的原始号码
        string s;  // 用来累积只含数字的号码
        for (char c : number) {  // 逐个字符检查原始号码
            if (c != ' ' && c != '-') {  // 空格和短横线是分隔符，需要丢弃
                s.push_back(c);  // 数字字符原样保留
            }
        }
        int n = s.size();  // 纯数字的位数，决定后面如何分组
        vector<string> res;  // 保存最后输出的各个数字块
        for (int i = 0; i < n / 3; ++i) {  // 先按每块 3 位切分，共 n/3 块
            res.push_back(s.substr(i * 3, 3));  // 取出第 i 块连续的 3 位数字
        }
        if (n % 3 == 1) {  // 末尾还剩 1 位：不能出现长度为 1 的块，需要拆成 2+2
            res.back() = res.back().substr(0, 2);  // 把最后一块 3 位砍成 2 位
            res.push_back(s.substr(n - 2));  // 再补上最后剩下的 2 位
        } else if (n % 3 == 2) {  // 末尾还剩 2 位：正好可以自成一块
            res.push_back(s.substr(n - 2));  // 直接追加这 2 位数字
        }
        string ans;  // 用短横线把各块连起来的最终结果
        for (auto& v : res) {  // 顺序拼接每一块
            ans += v;  // 先接上这一块数字
            ans += "-";  // 再接一个分隔符，最后会多出一个待删除
        }
        ans.pop_back();  // 去掉末尾多余的那个短横线
        return ans;  // 返回格式化后的号码
    }
};