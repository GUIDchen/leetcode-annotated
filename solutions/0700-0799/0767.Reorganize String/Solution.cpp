// 题目：767. 重构字符串（Reorganize String）
// 思路：先判可行（某字母出现次数不超过 (n+1)/2），再按频次降序把字母依次填到下标 0,2,4,... 然后回到 1,3,5,...，保证相邻不同。
// 时间复杂度：O(n + 26 log 26)，统计与填表为线性；空间复杂度：O(n)，答案串与频次数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string reorganizeString(string s) {  // s：待重构的字符串
        vector<int> cnt(26);  // 统计 26 个小写字母各自出现的次数
        for (char& c : s) ++cnt[c - 'a'];  // 遍历字符串累加频次
        int mx = *max_element(cnt.begin(), cnt.end());  // 找到出现次数最多的字母的频次
        int n = s.size();  // 字符串长度
        if (mx > (n + 1) / 2) return "";  // 超过向上取整的一半就无法隔开，返回空串
        vector<vector<int>> m;  // 保存 {频次, 字母下标}，便于排序
        for (int i = 0; i < 26; ++i) {  // 遍历所有字母
            if (cnt[i]) m.push_back({cnt[i], i});  // 只保留出现过的字母
        }
        sort(m.begin(), m.end());  // 先按频次升序排序
        reverse(m.begin(), m.end());  // 反转为降序，让高频字母优先占位
        string ans = s;  // 借用原串长度构造答案容器
        int k = 0;  // 当前写入位置，步长为 2
        for (auto& e : m) {  // 按频次从高到低依次填字母
            int v = e[0], i = e[1];  // v 是该字母剩余个数，i 是它在 0..25 中的下标
            while (v--) {  // 把该字母逐个写进答案
                ans[k] = 'a' + i;  // 还原成字符写入
                k += 2;  // 隔一个位置写下一个，保证不相邻
                if (k >= n) k = 1;  // 越过末尾就回到下标 1，切换到另一组奇偶位置
            }
        }
        return ans;  // 返回重构后的字符串
    }
};  // 类定义结束（源文件末尾无换行）