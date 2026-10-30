// 题目：2655. 寻找最大长度的未覆盖区间（Find Maximal Uncovered Ranges）
// 核心思路：把被覆盖区间按左端点排序后从左到右扫描，维护已覆盖的最右位置 last，遇到空隙就输出 [last+1, l-1]，最后补上尾部空隙。
// 时间复杂度：O(k log k)，k 是区间个数，主要是排序；空间复杂度：O(1) 额外（不计排序与返回值）。
class Solution {  // 题解类
public:  // 方法对外可见
    vector<vector<int>> findMaximalUncoveredRanges(int n, vector<vector<int>>& ranges) {  // n：坐标范围为 [0, n-1]；ranges：被覆盖的闭区间列表；返回所有极大未覆盖区间
        sort(ranges.begin(), ranges.end(), [](const vector<int>& a, const vector<int>& b) {  // 按左端点升序排序，便于从左往右扫描合并
            return a[0] < b[0];  // 左端点小的排在前面，保证扫描顺序
        });  // 排序用的 lambda 结束
        int last = -1;  // last 是当前已被覆盖到的最右位置，-1 表示还没开始覆盖
        vector<vector<int>> ans;  // ans 收集所有极大未覆盖区间
        for (auto& range : ranges) {  // 依次扫描每个被覆盖区间
            int l = range[0], r = range[1];  // 取出当前区间的左右端点
            if (last + 1 < l) {  // last 与 l 之间有空隙，说明 [last+1, l-1] 未被覆盖
                ans.push_back({last + 1, l - 1});  // 记录这一段极大未覆盖区间
            }
            last = max(last, r);  // 更新已覆盖的最右端，取较大值防止被更短的区间「回退」
        }
        if (last + 1 < n) {  // 所有区间扫完后，末尾可能还有一段未覆盖
            ans.push_back({last + 1, n - 1});  // 记录末尾的极大未覆盖区间
        }
        return ans;  // 返回按左端点递增排列的未覆盖区间
    }
};  // class Solution 结束