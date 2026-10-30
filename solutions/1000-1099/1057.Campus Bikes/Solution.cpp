// 题目：1057. 校园自行车分配（Campus Bikes）
// 思路：枚举所有「工人-自行车」配对算出曼哈顿距离，按（距离, 工人下标, 自行车下标）升序排序，再贪心配对互不冲突的组合。
// 时间复杂度：O(n·m·log(n·m))，排序为主；空间复杂度：O(n·m)，保存全部候选配对。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {  // 返回每个工人被分配到的自行车下标
        int n = workers.size(), m = bikes.size();  // n 个工人，m 辆自行车
        vector<tuple<int, int, int>> arr(n * m);  // 存放所有「(距离, 工人下标, 自行车下标)」候选
        for (int i = 0, k = 0; i < n; ++i) {  // 枚举每个工人，k 是三元组的写入位置
            for (int j = 0; j < m; ++j) {  // 枚举每辆自行车
                int dist = abs(workers[i][0] - bikes[j][0]) + abs(workers[i][1] - bikes[j][1]);  // 曼哈顿距离：横向差绝对值 + 纵向差绝对值
                arr[k++] = {dist, i, j};  // 记录这条候选配对的优先级与端点
            }  // 自行车枚举结束
        }  // 所有工人-自行车配对都被记录下来
        sort(arr.begin(), arr.end());  // 按距离、工人下标、自行车下标依次升序，符合题目优先级
        vector<bool> vis1(n), vis2(m);  // vis1 标记工人是否已分配，vis2 标记自行车是否已被占用
        vector<int> ans(n);  // 答案数组：ans[i] 是工人 i 分到的自行车下标
        for (auto& [_, i, j] : arr) {  // 按优先级从优到劣遍历所有候选配对
            if (!vis1[i] && !vis2[j]) {  // 工人空闲且自行车空闲才能配对
                vis1[i] = true;  // 标记工人已分配
                vis2[j] = true;  // 标记自行车已占用
                ans[i] = j;  // 记录该工人的自行车
            }  // 配对分支结束
        }  // 遍历完所有候选，分配结束
        return ans;  // 返回每个工人对应的自行车下标
    }  // 方法结束
};  // 类定义结束