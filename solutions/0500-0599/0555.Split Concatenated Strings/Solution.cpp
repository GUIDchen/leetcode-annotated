// 题目：555. 分割连接字符串（Split Concatenated Strings）
// 核心思路：每个串先取「本身/反转」中较大的一个；再枚举切开位置，串内旋转后接上环形的其余串，取最大。
// 时间复杂度：O(L*sumLen)，L 为最长串长度；空间复杂度：O(sumLen)，用于构造候选答案。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string splitLoopedString(vector<string>& strs) {  // strs：字符串数组，把首尾相接成环后在某处切开，返回字典序最大的结果
        for (auto& s : strs) {  // 遍历每个串，决定它在最终答案里用正序还是逆序
            string t{s.rbegin(), s.rend()};  // 用反向迭代器构造 s 的逆序副本 t
            s = max(s, t);  // 正序与逆序取较大者，因为切开处可以让串整体反向出现
        }  // 预处理结束
        int n = strs.size();  // n 为串的个数，用于拼接环形剩余部分
        string ans = "";  // ans 记录目前得到的最大字符串，初始为空
        for (int i = 0; i < strs.size(); ++i) {  // 枚举从第 i 个串内部切开
            auto& s = strs[i];  // 引用当前被切开的串，避免拷贝
            string t;  // t 用于存放除第 i 个串之外的其余串按环形顺序拼成的部分
            for (int j = i + 1; j < n; ++j) {  // 先拼接第 i 个串之后的那些串
                t += strs[j];  // 依次追加
            }  // 后半段结束
            for (int j = 0; j < i; ++j) {  // 再拼接第 i 个串之前的那些串，保证环形顺序
                t += strs[j];  // 依次追加
            }  // 环形的其余部分拼接完成
            for (int j = 0; j < s.size(); ++j) {  // 枚举在第 i 个串内部的下标 j 处切开
                auto a = s.substr(j);  // a 是切口之后的后缀，将成为答案的开头
                auto b = s.substr(0, j);  // b 是切口之前的前缀，将成为答案的结尾
                auto cur = a + t + b;  // 正序情形：后缀 + 其余串 + 前缀
                if (ans < cur) {  // 若候选答案更大就更新
                    ans = cur;  // 记录新的最大答案
                }  // 判断结束
                reverse(a.begin(), a.end());  // 把后缀反转，用于尝试整体反向的情形
                reverse(b.begin(), b.end());  // 把前缀反转，用于尝试整体反向的情形
                cur = b + t + a;  // 反向情形：反转后的前缀 + 其余串 + 反转后的后缀
                if (ans < cur) {  // 若候选答案更大就更新
                    ans = cur;  // 记录新的最大答案
                }  // 判断结束
            }  // 当前切口位置枚举结束
        }  // 当前被切开的串枚举结束
        return ans;  // 返回字典序最大的结果
    }  // 方法结束
};  // 类定义结束