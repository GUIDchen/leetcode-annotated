// 题目：3169. 无需开会的工作日（Count Days Without Meetings）
// 思路：先把所有会议区间按开始日排序，用 last 记录已经被会议覆盖到的最晚日期；遇到区间开始日 st > last 时，中间空档 st-last-1 天都没有会，累计进答案；扫描完再把 last 之后到第 days 天的空档补上。
// 时间复杂度：O(n log n)，瓶颈是排序；空间复杂度：O(1)，只用了常数个额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countDays(int days, vector<vector<int>>& meetings) {  // days 是总天数 1..days；meetings 每个元素为 [开始日, 结束日]；返回无需开会的工作日数量
        sort(meetings.begin(), meetings.end());  // 按开始日升序排序，保证区间从左到右依次处理，空档判断才有意义
        int ans = 0, last = 0;  // ans 累计无会议天数；last 是已覆盖区间的最右端（0 表示一天都还没覆盖）
        for (auto& e : meetings) {  // 依次处理每一个会议区间
            int st = e[0], ed = e[1];  // 取出当前区间的左右端点，后面判断空档要用
            if (last < st) {  // 开始日晚于已覆盖范围，说明两者之间出现了没有会议的连续天数
                ans += st - last - 1;  // 空档长度 = st - last - 1（st 与 last 当天都在开会，所以两头不计）
            }
            last = max(last, ed);  // 合并区间：last 取右端点更大者，始终表示已被覆盖的最晚日期
        }
        ans += days - last;  // 收尾：last 之后一直到第 days 天同样没有会议
        return ans;  // 返回无需开会的工作日总数
    }
};