// 题目：358. K 距离间隔重排字符串（Rearrange String k Distance Apart）
// 思路：统计词频后用最大堆每次取剩余次数最多的字符，并用长度为 k 的队列做冷却，保证同字符间隔至少 k。
// 时间复杂度：O(n + 26 log 26)，每个字符入堆出堆一次；空间复杂度：O(n + 26)，答案与堆/队列开销。
class Solution {  // LeetCode 题解类
public:  // 对外暴露的解法入口
    string rearrangeString(string s, int k) {  // s 是原字符串，k 是相同字符之间至少间隔的距离
        vector<int> cnt(26, 0);  // 统计 26 个小写字母各自出现次数
        for (char c : s) {  // 遍历字符串中的每个字符
            ++cnt[c - 'a'];  // 字符减去 'a' 映射到 0~25 的下标并累加
        }  // 统计循环结束

        priority_queue<pair<int, int>> pq;  // 大根堆：pair 先比剩余次数，再比字符下标
        for (int i = 0; i < 26; ++i) {  // 枚举 26 个字母
            if (cnt[i] > 0) {  // 只把出现过的字母入堆
                pq.emplace(cnt[i], i);  // 入堆：(剩余次数, 字母下标)
            }  // 出现次数判断结束
        }  // 建堆结束

        queue<pair<int, int>> q;  // 冷却队列：存放刚用过、暂时不能再用的字母
        string ans;  // 结果字符串，按顺序拼接
        while (!pq.empty()) {  // 只要还有可用字母就继续取
            auto p = pq.top();  // 取出剩余次数最多的字母
            pq.pop();  // 该字母出堆，准备消耗一次
            p.first -= 1;  // 用掉一次，剩余次数减一
            ans.push_back('a' + p.second);  // 把字母下标还原成字符，追加到答案
            q.push(p);  // 进入冷却队列，等 k 步之后才能再用
            if (q.size() >= k) {  // 冷却队列已满 k 个，说明队首字母的间隔已够
                p = q.front();  // 取出冷却完成的字母
                q.pop();  // 从冷却队列中移除
                if (p.first > 0) {  // 还有剩余次数才放回堆
                    pq.push(p);  // 重新参与调度
                }  // 剩余次数判断结束
            }  // 冷却判断结束
        }  // 主循环结束

        return ans.size() < s.size() ? "" : ans;  // 长度不足说明无法满足间隔要求，返回空串
    }  // 解法方法结束
};  // 题解类结束
