// 题目：1405. 最长快乐字符串（Longest Happy String）
// 思路：大顶堆按剩余次数排序，每次取最多的字母拼接；若末尾已有两个相同字母，则退而取第二多的字母插一个再放回，循环至堆空。
// 时间复杂度：O((a+b+c) log 3)，每步一次堆操作；空间复杂度：O(1)，堆中至多 3 个元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string longestDiverseString(int a, int b, int c) {  // a、b、c 分别是 'a'、'b'、'c' 的可用次数
        using pci = pair<char, int>;  // 类型别名：二元组为「字母, 剩余次数」
        auto cmp = [](pci x, pci y) { return x.second < y.second; };  // 比较器：次数大的优先级高，构成大顶堆
        priority_queue<pci, vector<pci>, decltype(cmp)> pq(cmp);  // 用 lambda 类型做比较器的优先队列

        if (a > 0) pq.push({'a', a});  // 只把还有剩余的字母入堆
        if (b > 0) pq.push({'b', b});  // 同上处理 'b'
        if (c > 0) pq.push({'c', c});  // 同上处理 'c'

        string ans;  // 逐字符构造答案
        while (!pq.empty()) {  // 堆非空说明还有字母可用
            pci cur = pq.top();  // 取出当前剩余次数最多的字母
            pq.pop();  // 先出堆，稍后按需放回
            int n = ans.size();  // 已拼好的长度，用于检查末尾
            if (n >= 2 && ans[n - 1] == cur.first && ans[n - 2] == cur.first) {  // 末尾已连续出现两个相同字母，不能继续拼接它
                if (pq.empty()) break;  // 没有其他字母可换，答案已达最长
                pci nxt = pq.top();  // 取出第二多的字母来打断连击
                pq.pop();  // 先出堆以便修改次数
                ans.push_back(nxt.first);  // 拼接这个替代字母
                if (--nxt.second > 0) {  // 先自减使用次数，仍有剩余才放回堆
                    pq.push(nxt);  // 放回替代字母
                }  // 放回判断结束
                pq.push(cur);  // 原字母没用掉，原样放回堆中
            } else {  // 末尾不构成 AAA，可以安全拼接当前字母
                ans.push_back(cur.first);  // 拼上当前字母
                if (--cur.second > 0) {  // 消耗一次，仍有余量才放回
                    pq.push(cur);  // 放回继续参与后续选择
                }  // 放回判断结束
            }  // 分支结束
        }  // 主循环结束

        return ans;  // 返回构造出的最长快乐字符串
    }  // longestDiverseString 方法结束
};  // Solution 类结束