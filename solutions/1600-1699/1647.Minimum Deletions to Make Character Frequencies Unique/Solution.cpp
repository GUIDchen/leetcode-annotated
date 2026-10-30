// 题目：1647. 字符频次唯一的最小删除次数（Minimum Deletions to Make Character Frequencies Unique）
// 思路：统计频次并降序排序，贪心地让每个频次严格小于前一个；冲突就削到 pre-1，pre 降到 0 后剩余频次全部删空。
// 时间复杂度：O(n + 26 log 26)，统计 O(n) 加排序常数级；空间复杂度：O(1)，只有 26 个字母的计数数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外开放
    int minDeletions(string s) {  // s：输入字符串，返回让所有字符频次互不相同所需的最小删除次数
        vector<int> cnt(26);  // cnt[ch - 'a'] 统计每个小写字母出现的次数
        for (char& c : s) ++cnt[c - 'a'];  // 遍历字符串，累加各字符的频次
        sort(cnt.rbegin(), cnt.rend());  // 频次降序排序，从最大的频次开始贪心分配
        int ans = 0, pre = 1 << 30;  // ans 记录删除次数；pre 记录上一个保留的频次，初值取很大以保证第一个频次原样保留
        for (int& v : cnt) {  // 按频次从大到小逐个处理
            if (pre == 0) {  // pre 已经降到 0，说明后面再小的频次也无处可放
                ans += v;  // 当前频次只能全部删掉
            } else if (v >= pre) {  // 当前频次与上一个冲突（或不小于它），必须削到 pre - 1
                ans += v - pre + 1;  // 削到 pre - 1 需要删除 v - (pre - 1) 个字符
                --pre;  // 可用的最大频次跟着递减
            } else {  // 当前频次比 pre 小，可以原样保留
                pre = v;  // 更新上一个保留下来的频次
            }  // 分支处理结束
        }  // 频次遍历结束
        return ans;  // 返回最小删除次数
    }  // 方法结束
};  // 类定义结束