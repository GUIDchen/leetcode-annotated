// 4001. 聚合两个时间序列 / Aggregate Two Time Series（中等）
// 核心思路：两个序列的时间戳都严格递增，用双指针归并；某序列缺失的时间戳要取「下一个更晚时间戳」的值，恰好就是该指针当前指向的值（指针越界后视为 0），所以每个出现过的时刻把两个当前值相加即可。
// 复杂度：时间 O(m + n)，空间 O(m + n) 用于存放结果。
class Solution {  // 题解类
public:  // 公有接口
    vector<vector<int>> aggregateTimeSeries(vector<vector<int>>& series1, vector<vector<int>>& series2) {  // 返回按时间戳严格递增排列的聚合序列
        int m = series1.size(), n = series2.size();  // 两个序列的长度
        int i = 0, j = 0;  // 双指针分别指向两个序列的当前元素
        vector<vector<int>> ans;  // 聚合结果

        while (i < m && j < n) {  // 两个序列都还有元素时归并
            int t1 = series1[i][0], v1 = series1[i][1];  // 序列 1 当前时刻与值
            int t2 = series2[j][0], v2 = series2[j][1];  // 序列 2 当前时刻与值

            if (t1 == t2) {  // 两个序列都有该时刻
                ans.push_back({t1, v1 + v2});  // 该时刻的值等于两者相加
                i++;  // 序列 1 指针前进
                j++;  // 序列 2 指针前进
            } else if (t1 < t2) {  // 序列 1 的时刻更早
                ans.push_back({t1, v1 + v2});  // 序列 2 在该时刻缺失，取它下一个时间戳的值 v2
                i++;  // 序列 1 指针前进
            } else {  // 序列 2 的时刻更早
                ans.push_back({t2, v1 + v2});  // 序列 1 在该时刻缺失，取它下一个时间戳的值 v1
                j++;  // 序列 2 指针前进
            }  // if 结束
        }  // while 结束

        while (i < m) {  // 序列 2 已耗尽，它在这些时刻的值为 0
            ans.push_back(series1[i]);  // 序列 1 的剩余元素原样加入
            i++;  // 指针前进
        }  // while 结束

        while (j < n) {  // 序列 1 已耗尽，它在这些时刻的值为 0
            ans.push_back(series2[j]);  // 序列 2 的剩余元素原样加入
            j++;  // 指针前进
        }  // while 结束

        return ans;  // 返回聚合结果
    }  // 方法结束
};  // 类定义结束