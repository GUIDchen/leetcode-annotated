// 题目：1370. 上升下降字符串（Increasing Decreasing String）
// 思路：统计每个字母出现次数，反复做「a→z 取一个、z→a 取一个」的扫描，直到用完所有字符。
// 时间复杂度：O(n + 26·n)，每轮至少取一个字符；空间复杂度：O(26)，计数数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string sortString(string s) {  // s：待重排的字符串
        int cnt[26]{};  // cnt 统计每个字母出现次数，初始全 0
        for (char& c : s) {  // 遍历字符串中的每个字符（用引用避免拷贝）
            ++cnt[c - 'a'];  // 对应字母计数加一
        }  // 字母统计结束
        string ans;  // ans 保存重排结果
        while (ans.size() < s.size()) {  // 反复「上升 + 下降」直到用完所有字符
            for (int i = 0; i < 26; ++i) {  // 上升阶段：a 到 z
                if (cnt[i]) {  // 该字母还有剩余
                    ans += i + 'a';  // 追加到答案
                    --cnt[i];  // 用掉一个
                }  // if 结束
            }  // 上升循环结束
            for (int i = 25; i >= 0; --i) {  // 下降阶段：z 到 a
                if (cnt[i]) {  // 该字母还有剩余
                    ans += i + 'a';  // 追加到答案
                    --cnt[i];  // 用掉一个
                }  // if 结束
            }  // 下降循环结束
        }  // while 结束
        return ans;  // 返回重排结果
    }  // 方法结束
};  // 类定义结束