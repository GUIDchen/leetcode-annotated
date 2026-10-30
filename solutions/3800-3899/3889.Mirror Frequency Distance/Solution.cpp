// 题目：3889. 镜像频次距离（Mirror Frequency Distance）
// 思路：先统计每个字符的出现次数，再对每个字符算出它的镜像字符，用哈希集合保证每一对镜像字符只统计一次，累加 |freq(c) - freq(m)|。
// 时间复杂度：O(n + |Σ|)，n 为字符串长度、|Σ| 为字符集大小；空间复杂度：O(|Σ|)，存放频次表与去重集合。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int mirrorFrequency(string s) {  // s：只由小写字母和数字组成的字符串
        unordered_map<char, int> freq;  // 字符 → 出现次数的哈希表
        for (char c : s) {  // 遍历字符串中的每个字符
            freq[c]++;  // 该字符频次加 1
        }  // 结束遍历

        int ans = 0;  // 答案：所有镜像字符对的频次绝对差之和
        unordered_set<char> vis;  // 去重集合：记录已经统计过的字符

        for (auto& [c, v] : freq) {  // 遍历每个出现的字符及其频次
            char m;  // 用于存放镜像字符
            if (isalpha(c)) {  // 字母的镜像按字母表逆序计算
                m = 'a' + 25 - (c - 'a');  // a↔z、b↔y：用 25 减去到 'a' 的距离
            } else {  // 否则是数字
                m = '0' + (9 - (c - '0'));  // 0↔9、1↔8：用 9 减去到 '0' 的距离
            }

            if (vis.count(m)) {  // 镜像字符已经处理过，说明这一对已统计
                continue;  // 直接跳过，避免重复计数
            }
            vis.insert(c);  // 标记当前字符已处理

            int mv = freq.count(m) ? freq[m] : 0;  // 取镜像字符的频次，不存在则为 0
            ans += abs(v - mv);  // 累加两者的频次绝对差
        }  // 结束遍历

        return ans;  // 返回镜像频次距离
    }  // 结束方法
};  // 结束类
