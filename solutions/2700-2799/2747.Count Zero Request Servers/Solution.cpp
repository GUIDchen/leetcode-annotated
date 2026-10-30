// 题目：2747. 统计没有收到请求的服务器数目（Count Zero Request Servers）
// 思路：日志按时间排序，询问按时间排序后用双指针维护滑动窗口 [r-x, r]，哈希表统计窗口内出现过的服务器数，n 减去它即答案。
// 时间复杂度：O((m + q) log(m + q))，排序主导；空间复杂度：O(n + q)，哈希表与结果数组。
class Solution {  // LeetCode 约定的题解类
public:  // 公有成员：判题器直接调用下面的方法
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {  // n：服务器总数；logs：[服务器编号, 时间]；x：时间窗口长度；queries：询问的时间点
        sort(logs.begin(), logs.end(), [](const auto& a, const auto& b) {  // 日志按时间（下标 1）升序排序，为后面的双指针滑动窗口做准备
            return a[1] < b[1];  // 比较函数：时间早的日志排在前面
        });  // 结束 sort 调用
        int m = queries.size();  // 询问的个数
        vector<pair<int, int>> qs(m);  // 把询问时间和它的原始下标绑定，排序后还能写回正确位置
        for (int i = 0; i < m; ++i) {  // 逐条构造 (询问时间, 询问下标) 对
            qs[i] = {queries[i], i};  // 记录时间与下标
        }  // 结束构造循环
        sort(qs.begin(), qs.end());  // 询问按时间升序排序，保证窗口左右指针只向前移动
        unordered_map<int, int> cnt;  // 哈希表：统计窗口内每个服务器的日志条数（条数为 0 时删除键）
        vector<int> ans(m);  // 结果数组，下标与原始询问一一对应
        int j = 0, k = 0;  // j：窗口左端指针（日志下标）；k：窗口右端指针
        for (auto& [r, i] : qs) {  // 按时间从小到大依次处理每个询问
            int l = r - x;  // 窗口左边界：只统计时间在 [r-x, r] 内的日志
            while (k < logs.size() && logs[k][1] <= r) {  // 右端扩张：把时间 ≤ r 的日志全部加入窗口
                ++cnt[logs[k++][0]];  // 该服务器日志条数加一，右指针后移
            }  // 结束右端扩张循环
            while (j < logs.size() && logs[j][1] < l) {  // 左端收缩：把时间 < r-x 的日志移出窗口
                if (--cnt[logs[j][0]] == 0) {  // 该服务器日志条数减一
                    cnt.erase(logs[j][0]);  // 条数降为 0 时删除键，这样 cnt.size() 就是窗口内出现过的服务器数
                }  // 结束“删除键”分支
                ++j;  // 左指针后移，继续检查下一条过期日志
            }  // 结束左端收缩循环
            ans[i] = n - cnt.size();  // 总服务器数减去窗口内出现过的服务器数，即没收到请求的服务器数
        }  // 结束询问循环
        return ans;  // 按原始询问顺序返回答案
    }  // 结束题解方法
// 结束题解类
};