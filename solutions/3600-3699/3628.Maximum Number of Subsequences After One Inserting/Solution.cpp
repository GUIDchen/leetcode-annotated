// 3628. Maximum Number of Subsequences After One Inserting（3628. 插入一个字母的最大子序列数）
// 核心思路：先统计原有 "LCT" 子序列数，同时记录每个位置左右两侧的 L、T 数量以求出插入 C 带来的最大增益；再分别与插入 T 的增益（LC 数）、插入 L 的增益（CT 数）取最大，加到答案上。
// 复杂度：时间 O(n)（三次线性扫描），空间 O(1)。
class Solution {  // 定义题解类
public:  // 公有成员，供判题器调用
    long long numOfSubsequences(string s) {  // 求插入一个字母后 "LCT" 子序列的最大数量
        auto calc = [&](string t) {  // 统计 s 中等于模式串 t 的子序列个数
            long long cnt = 0, a = 0;  // cnt 为子序列个数，a 为已遇到的 t[0] 个数
            for (char c : s) {  // 顺序扫描字符串
                if (c == t[1]) {  // 遇到模式的第二个字符
                    cnt += a;  // 与前面每个 t[0] 配对形成子序列
                }
                a += (c == t[0]);  // 累计 t[0] 出现的次数
            }
            return cnt;  // 返回子序列个数
        };

        long long l = 0, r = count(s.begin(), s.end(), 'T');  // l 为左侧 L 的数量，r 为右侧 T 的数量
        long long ans = 0, mx = 0;  // ans 为原有 LCT 数量，mx 为插入一个字符的最大增益
        for (char c : s) {  // 枚举插入位置（以当前字符为界）
            r -= (c == 'T');  // 当前字符移入左侧，右侧 T 数量减一
            if (c == 'C') {  // 当前字符是 C，可与左侧 L、右侧 T 组成 LCT
                ans += l * r;  // 累加原有的 LCT 子序列数
            }
            l += (c == 'L');  // 把当前字符计入左侧 L 的数量
            mx = max(mx, l * r);  // 在此处插入 C 的增益为 l * r，取最大
        }
        mx = max(mx, calc("LC"));  // 插入 T 的增益等于原串中 LC 子序列的个数
        mx = max(mx, calc("CT"));  // 插入 L 的增益等于原串中 CT 子序列的个数
        ans += mx;  // 原有数量加上插入一个字符的最大增益
        return ans;  // 返回最终答案
    }
};
