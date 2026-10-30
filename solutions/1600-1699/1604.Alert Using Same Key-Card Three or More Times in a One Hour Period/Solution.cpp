// 题目：1604. 警告一小时内使用相同员工卡大于等于三次的人（Alert Using Same Key-Card Three or More Times in a One Hour Period）
// 思路：先把每人的刷卡时间转成分钟并按人名分组，再对每人排序，检查任意连续三次的时间跨度是否 ≤ 60。
// 时间复杂度：O(n log n)，主要是排序；空间复杂度：O(n)，需要按人保存全部时间。
class Solution {  // 题解类
public:  // 对外接口
    vector<string> alertNames(vector<string>& keyName, vector<string>& keyTime) {  // keyName[i] 是刷卡人，keyTime[i] 是其刷卡时间（"HH:MM"）
        unordered_map<string, vector<int>> d;  // 哈希表：员工名 → 他的全部刷卡时间（统一换算成分钟数）
        for (int i = 0; i < keyName.size(); ++i) {  // 逐个处理每一条刷卡记录
            auto name = keyName[i];  // 本次刷卡的人
            auto time = keyTime[i];  // 本次刷卡的时间字符串
            int a, b;  // 接收解析出的小时与分钟
            sscanf(time.c_str(), "%d:%d", &a, &b);  // 用 sscanf 按 "HH:MM" 格式解析时间
            int t = a * 60 + b;  // 换算成「从 0 点开始的分钟数」，便于做时间差比较
            d[name].emplace_back(t);  // 把该时间追加到这位员工的时间列表末尾
        }  // 本层循环结束
        vector<string> ans;  // 保存答案：一小时内刷满 3 次的员工
        for (auto& [name, ts] : d) {  // 结构化绑定遍历哈希表：name 是人名，ts 是他的时间列表
            int n = ts.size();  // 这位员工的刷卡次数
            if (n > 2) {  // 少于 3 次不可能触发警告，直接跳过
                sort(ts.begin(), ts.end());  // 先按时间升序排序，之后才能用相邻三次判断时间跨度
                for (int i = 0; i < n - 2; ++i) {  // i 为连续三次中的第一次，最多枚举到 n-3
                    if (ts[i + 2] - ts[i] <= 60) {  // 第 1 次与第 3 次间隔不超过 60 分钟，说明一小时内刷了三次
                        ans.emplace_back(name);  // 记录该员工
                        break;  // 同一位员工只需记录一次，跳出内层循环
                    }  // if 结束
                }  // 内层循环结束
            }  // if 结束
        }  // 遍历哈希表结束
        sort(ans.begin(), ans.end());  // 结果按字典序排序，题目要求有序输出
        return ans;  // 返回所有需要警告的员工
    }
};