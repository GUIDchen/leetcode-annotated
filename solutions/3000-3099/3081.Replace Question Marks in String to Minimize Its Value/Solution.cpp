// 题目：3081. 替换字符串中的问号使分数最小（Replace Question Marks in String to Minimize Its Value）
// 思路：用小根堆每次取 (频次最小, 字母最小) 的字母分配给一个问号，收集 k 个字母后升序排列按序填回，即可得到字典序最小的结果。
// 时间复杂度：O(n + k log 26 + k log k)，每个问号一次堆操作；空间复杂度：O(n)，结果串与字母计数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string minimizeStringValue(string s) {  // s 中含有 '?'，用尽量小的字母替换使它分数最小，返回字典序最小的结果
        int cnt[26]{};  // cnt[i] 记录字母 i+'a' 在原串中出现的次数
        int k = 0;  // k 记录问号 '?' 的个数
        for (char& c : s) {  // 第一次遍历：统计各字母频次与问号数量
            if (c == '?') {  // 当前字符是待替换的问号
                ++k;  // 问号计数加一
            } else {  // 当前字符是普通小写字母
                ++cnt[c - 'a'];  // 累加该字母的出现次数
            }
        }
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;  // 小根堆，按 (频次, 字母编号) 排序；频次相同时字母更小的优先
        for (int i = 0; i < 26; ++i) {  // 把 26 个字母的 (当前频次, 编号) 全部入堆
            pq.push({cnt[i], i});  // 入堆后堆顶就是「当前最该被使用」的字母
        }
        vector<int> t(k);  // t 保存 k 个问号最终要填入的字母编号
        for (int i = 0; i < k; ++i) {  // 每次取出频次最小（字母也最小）的字母，分配给一个问号
            auto [v, c] = pq.top();  // v 是该字母当前频次，c 是字母编号
            pq.pop();  // 弹出堆顶
            t[i] = c;  // 记录这个问号使用的字母
            pq.push({v + 1, c});  // 频次加一后重新入堆，让各字母被使用的机会保持均衡
        }
        sort(t.begin(), t.end());  // 把选出的字母升序排列，再按顺序填入问号即得字典序最小的结果
        int j = 0;  // j 指向 t 中下一个待填入的字母
        for (char& c : s) {  // 第二次遍历：把问号按 t 的顺序替换掉
            if (c == '?') {  // 只处理问号位置
                c = t[j++] + 'a';  // 取出对应字母编号并转成字符，j 后移
            }
        }
        return s;  // 返回替换完成的字符串
    }
};