// 题目：2182. 构造限制重复的字符串（Construct String With Repeat Limit）
// 思路：统计每个字母出现次数，从大到小枚举字母；每轮尽量输出 repeatLimit 个当前最大字母，若还有剩余，就插入一个更小的字母隔开。
// 时间复杂度：O(n + 26 * n)，n 为字符串长度，每个字母最多被搬运 n 次；空间复杂度：O(26 + n)，计数数组与答案字符串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string repeatLimitedString(string s, int repeatLimit) {  // s：可用字符；repeatLimit：同一字母最多连续出现次数
        int cnt[26]{};  // 计数数组，cnt[x] 表示字母 'a'+x 的剩余个数，{} 全部初始化为 0
        for (char& c : s) {  // 遍历原字符串统计每种字母出现次数
            ++cnt[c - 'a'];  // 对应字母计数加一
        }
        string ans;  // 结果字符串，按字典序从大到小拼接
        for (int i = 25, j = 24; ~i; --i) {  // i 从最大字母 'z' 向下枚举；~i 表示 i >= 0（i 变成 -1 时 ~(-1) 为 0）
            j = min(j, i - 1);  // j 是比 i 小的备选「隔开字母」，不能与 i 相同且需随 i 缩小
            while (1) {  // 反复输出字母 i，直到把它用完或没有更小字母可隔开
                for (int k = min(cnt[i], repeatLimit); k; --k) {  // 一轮最多连续写 repeatLimit 个字母 i
                    ans += 'a' + i;  // 追加一个字母 i
                    --cnt[i];  // 剩余个数减一
                }
                if (cnt[i] == 0) {  // 字母 i 已经用完，不必再插入隔开字符
                    break;  // 跳出本轮
                }
                while (j >= 0 && cnt[j] == 0) {  // 从大到小找下一个还有剩余的更小字母
                    --j;  // 该字母用完，继续往下找
                }
                if (j < 0) {  // 没有更小字母可用来隔开
                    break;  // 剩下的字母 i 只能丢弃，结束
                }
                ans += 'a' + j;  // 插入一个更小字母，打断连续重复
                --cnt[j];  // 该隔开字母的剩余个数减一
            }
        }
        return ans;  // 返回构造出的长度最长的合法字符串
    }
};
