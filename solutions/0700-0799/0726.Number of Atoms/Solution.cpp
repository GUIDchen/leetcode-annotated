// 题目：726. 原子的数量（Number of Atoms）
// 思路：从右往左扫描化学式，先读到数字再读到元素名（反向正好符合「元素名后跟个数」的写法）；遇到 ')' 把当前乘数压栈并乘以括号后的数字，遇到 '(' 出栈恢复外层乘数。
// 时间复杂度：O(n + E log E)，n 为化学式长度，E 为元素种数；空间复杂度：O(E)，哈希表与栈的开销。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string countOfAtoms(string formula) {  // formula：化学式字符串
        unordered_map<string, int> cnt;  // 记录每个元素的原子总数
        vector<int> stk;  // 栈：保存每一层括号外的乘数
        int multiplier = 1, freq = 0;  // multiplier 为当前所在层的乘数；freq 为刚读到的数字（0 表示没写数字）
        for (int i = formula.size() - 1; i >= 0; --i) {  // 从右往左扫描，这样先读到个数再读到元素名，处理最自然
            if (formula[i] >= 'a' && formula[i] <= 'z') {  // 小写字母：属于前面元素名的一部分
                int end = i--;  // end 记录元素名右端，i 左移去找首字母
                while (i >= 0 && formula[i] >= 'a' && formula[i] <= 'z') {  // 继续吞掉前面的小写字母
                    --i;  // 指针左移
                }  // while 循环结束
                cnt[formula.substr(i, end - i + 1)] += max(freq, 1) * multiplier;  // 元素名 = 首字母 + 后续小写字母；没写数字时个数按 1 计，再乘以当前层乘数
                freq = 0;  // 数字已消费，清零
            } else if (formula[i] >= 'A' && formula[i] <= 'Z') {  // 大写字母：单字母元素名
                cnt[string(1, formula[i])] += max(freq, 1) * multiplier;  // 累加个数（缺省为 1），再乘当前层乘数
                freq = 0;  // 数字已消费，清零
            } else if (formula[i] >= '0' && formula[i] <= '9') {  // 数字：反向解析出完整数值
                freq = formula[i] - '0';  // 先取个位
                int p = 10;  // 下一位的权重
                while (i - 1 >= 0 && formula[i - 1] >= '0' && formula[i - 1] <= '9') {  // 前面还是数字，继续拼高位
                    freq += p * (formula[--i] - '0');  // 指针先左移，再按权重累加
                    p *= 10;  // 权重乘以 10
                }  // while 循环结束
            } else if (formula[i] == ')') {  // 右括号：进入新的一层
                stk.push_back(multiplier);  // 先把外层乘数压栈
                multiplier *= max(freq, 1);  // 内层乘数 = 外层乘数 * 括号后的数字（缺省为 1）
                freq = 0;  // 数字已消费，清零
            } else {  // 剩下只可能是左括号，表示这一层结束
                multiplier = stk.back();  // 恢复外层乘数
                stk.pop_back();  // 弹出栈顶
            }  // if 结束
        }  // for 循环结束
        vector<string> keys;  // 收集所有元素名，之后排序输出
        for (auto& [k, _] : cnt) {  // 遍历哈希表，取出键
            keys.push_back(k);  // 保存键名
        }  // for 循环结束
        sort(keys.begin(), keys.end());  // 按元素名字典序排序
        string ans;  // 结果字符串
        for (auto& key : keys) {  // 依次拼接每个元素
            ans += key;  // 先追加元素名
            if (cnt[key] > 1) {  // 个数为 1 时按题意省略数字
                ans += to_string(cnt[key]);  // 追加个数
            }  // if 结束
        }  // for 循环结束
        return ans;  // 返回格式化后的结果
    }  // 方法结束
};  // 类定义结束
