// 题目：2217. 找到指定长度的回文数（Find Palindrome With Fixed Length）
// 思路：定长回文由前半段唯一决定。第 q 个回文的前半段是 start + q - 1，超过 end 就不存在；否则反转前半段拼接成回文。
// 时间复杂度：O(len(queries) * intLength)，每个查询做一次反转与拼接；空间复杂度：O(intLength)，存放单个回文字符串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<long long> kthPalindrome(vector<int>& queries, int intLength) {  // queries 是询问列表，intLength 是回文长度
        int l = (intLength + 1) >> 1;  // 回文前半段长度：向上取整，奇数长度时包含中间那位
        long long start = pow(10, l - 1), end = pow(10, l) - 1;  // 前半段取值范围 [start, end]，避免前导零
        vector<long long> ans;  // 按 queries 的顺序收集答案
        for (int& q : queries) {  // 依次处理每个询问
            long long v = start + q - 1;  // 第 q 小的回文对应的前半段数值
            if (v > end) {  // 超出合法前半段范围，说明该回文不存在
                ans.push_back(-1);  // 按题目要求填 -1
                continue;  // 直接处理下一个询问
            }
            string s = to_string(v);  // 前半段转成字符串
            string s1 = s;  // 复制一份，用来生成镜像部分
            reverse(s1.begin(), s1.end());  // 反转得到后半段的镜像
            s += s1.substr(intLength % 2);  // 偶数长度拼完整反转；奇数长度跳过中间那位
            ans.push_back(stoll(s));  // 拼接结果转回整数，加入答案
        }
        return ans;  // 返回所有查询的答案
    }
};