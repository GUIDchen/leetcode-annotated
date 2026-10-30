// 题目：2933. 高访问员工（High-Access Employees）
// 思路：把每个员工的时间换算成分钟数后按员工分组，组内排序，再用长度为 3 的滑动窗口判断是否 1 小时内访问了 3 次。
// 时间复杂度：O(n log n)，主要开销是分组内排序；空间复杂度：O(n)，哈希表存下全部访问时间。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> findHighAccessEmployees(vector<vector<string>>& access_times) {  // access_times：每项形如 [姓名, "HHMM"] 的访问记录
        unordered_map<string, vector<int>> d;  // 哈希表：姓名 -> 该员工所有访问时间（统一换成分钟数）
        for (auto& e : access_times) {  // 遍历每条访问记录
            auto name = e[0];  // 记录中的员工姓名
            auto s = e[1];  // 形如 "HHMM" 的四位时间字符串
            int t = stoi(s.substr(0, 2)) * 60 + stoi(s.substr(2, 2));  // 前两位是小时、后两位是分钟，统一换算成分钟数便于做差比较
            d[name].emplace_back(t);  // 把换算后的时间追加到该员工的时间列表里
        }
        vector<string> ans;  // 结果：所有高访问员工姓名
        for (auto& [name, ts] : d) {  // 逐个员工独立判断
            sort(ts.begin(), ts.end());  // 时间升序排序，方便用间隔为 2 的窗口判断是否落在 1 小时内
            for (int i = 2; i < ts.size(); ++i) {  // 窗口右端从第 3 个元素开始（下标 2）
                if (ts[i] - ts[i - 2] < 60) {  // 相隔两次的访问跨度小于 60 分钟，说明这三次访问都在 1 小时内
                    ans.emplace_back(name);  // 该员工属于高访问员工，记入答案
                    break;  // 每个员工最多加入一次，找到就跳出内层循环
                }
            }
        }
        return ans;  // 返回所有高访问员工的姓名
    }
};  // 类定义结束