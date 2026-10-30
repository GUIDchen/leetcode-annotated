// 题目：1424. 对角线遍历 II（Diagonal Traverse II）
// 核心思路：同一条对角线上的元素满足行号加列号相等，把 (i+j, j, 值) 全部排序后按序取值即为答案。
// 时间复杂度：O(N log N)，N 为元素总数，排序主导；空间复杂度：O(N)，需要额外保存排序数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> findDiagonalOrder(vector<vector<int>>& nums) {  // nums：各行长度可以不同的二维数组
        vector<tuple<int, int, int>> arr;  // 存放 (对角线编号 i+j, 列号 j, 元素值)，便于统一排序
        for (int i = 0; i < nums.size(); ++i) {  // 枚举行号 i
            for (int j = 0; j < nums[i].size(); ++j) {  // 枚举该行现有的列（各行长度不等）
                arr.push_back({i + j, j, nums[i][j]});  // 同一对角线 i+j 相同，再用列号 j 决定对角线内的先后
            }  // 该行列枚举结束
        }  // 所有行枚举结束
        sort(arr.begin(), arr.end());  // 按 (i+j, j) 升序：先排对角线，再在对角线内从下往上
        vector<int> ans;  // 收集遍历结果
        for (auto& e : arr) {  // 按排好的顺序依次取出元素
            ans.push_back(get<2>(e));  // 只取元组中的元素值，忽略排序用的两个坐标
        }  // 排序数组遍历结束
        return ans;  // 返回沿对角线遍历得到的序列
    }  // 方法结束
};  // 题解类定义结束