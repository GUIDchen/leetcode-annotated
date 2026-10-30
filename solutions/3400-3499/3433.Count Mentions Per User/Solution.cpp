// 3433. Count Mentions Per User / 3433. 统计用户被提及情况
// 核心思路：按 (时间戳, 事件类型第三个字符) 排序后线性扫描，用 onlineT 记下线时间、lazy 延迟累计 @all。
// 复杂度：时间 O(n log n + m * n)，空间 O(n)。

class Solution {  // LeetCode 题解统一使用 Solution 类
public:  // 判题器调用的公有方法
    vector<int> countMentions(int numberOfUsers, vector<vector<string>>& events) {  // 返回每个用户被提及的次数
        ranges::sort(events, [](const vector<string>& a, const vector<string>& b) {  // 按时间升序排序，时间相同时把 OFFLINE 排在 MESSAGE 前面
            int x = stoi(a[1]);  // 事件 a 的时间戳
            int y = stoi(b[1]);  // 事件 b 的时间戳
            if (x == y) {  // 时间相同则比较事件类型第三个字符
                return a[0][2] < b[0][2];  // OFFLINE 的第三个字符 F 小于 MESSAGE 的 S，故下线事件先处理
            }  // 相同时刻的次序判断结束
            return x < y;  // 时间不同则按时间戳升序
        });  // 排序比较函数结束

        vector<int> ans(numberOfUsers, 0);  // 每个用户的提及计数
        vector<int> onlineT(numberOfUsers, 0);  // 每个用户的下线时刻，0 表示一开始就在线
        int lazy = 0;  // 延迟累计的 @all 提及次数

        for (const auto& e : events) {  // 按时间顺序处理每个事件
            string etype = e[0];  // 事件类型字符串
            int cur = stoi(e[1]);  // 当前事件时间戳
            string s = e[2];  // 事件附加信息：用户编号或提及内容

            if (etype[0] == 'O') {  // OFFLINE 事件：该用户下线，在线状态保持到 cur + 60
                onlineT[stoi(s)] = cur + 60;  // 记录用户 stoi(s) 的下线时刻
            } else if (s[0] == 'A') {  // MESSAGE 事件中提到所有人
                lazy++;  // 先累计到 lazy，最后统一结算给所有用户
            } else if (s[0] == 'H') {  // MESSAGE 事件中提到在线用户 HERE
                for (int i = 0; i < numberOfUsers; ++i) {  // 遍历所有用户，判断事发时是否在线
                    if (onlineT[i] <= cur) {  // 该用户事发时在线（下线时刻晚于当前时间）
                        ++ans[i];  // 该用户被提及，计数加一
                    }
                }
            } else {  // 其余 MESSAGE 事件：提及具体的用户编号列表
                stringstream ss(s);  // 用字符串流逐个解析提及项
                string token;  // 当前提及项，形如 id123
                while (ss >> token) {  // 逐个读取空白分隔的提及项
                    ans[stoi(token.substr(2))]++;  // 去掉 id 前缀，取用户编号并累加提及次数
                }
            }
        }

        if (lazy > 0) {  // 存在 @all 提及需要统一结算
            for (int i = 0; i < numberOfUsers; ++i) {  // 遍历所有用户
                ans[i] += lazy;  // 把 lazy 次 @all 提及补加给每个用户
            }
        }

        return ans;  // 返回每个用户的提及次数
    }  // 方法结束
};  // 类定义结束
