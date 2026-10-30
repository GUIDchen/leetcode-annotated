// 题目：1847. 最近的房间（Closest Room）
// 思路：把房间按面积升序、查询按 minSize 升序后离线处理，用 multiset 维护"面积足够大"的房间编号；随着 minSize 增大不断删掉小房间，
//       再在有序集合里二分出 prefer 的左右邻居，取编号差更小的那个。
// 时间复杂度：O((n+k) log n)，排序与每次二分/删除都是对数级；空间复杂度：O(n + k)，multiset 与答案数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> closestRoom(vector<vector<int>>& rooms, vector<vector<int>>& queries) {  // rooms：{编号, 面积}；queries：{偏好编号, 最小面积}
        int n = rooms.size();  // 房间数量
        int k = queries.size();  // 查询数量
        sort(rooms.begin(), rooms.end(), [](const vector<int>& a, const vector<int>& b) {  // 按面积升序排列房间
            return a[1] < b[1];  // 面积小的排在前面，便于后续按阈值递增地剔除
        });
        vector<int> idx(k);  // 存放查询下标的数组
        iota(idx.begin(), idx.end(), 0);  // 填入 0,1,...,k-1，即查询的原始下标
        sort(idx.begin(), idx.end(), [&](int i, int j) {  // 按查询的 minSize 升序排列这些下标（离线处理）
            return queries[i][1] < queries[j][1];  // 面积门槛低的查询先处理，这样只需单向删除房间
        });
        vector<int> ans(k, -1);  // 答案数组，默认 -1 表示无满足面积的房间
        int i = 0;  // 指向 rooms 中第一个"面积仍可能达标"的房间
        multiset<int> s;  // 有序集合：保存当前面积达标的房间编号，支持二分查找
        for (auto& room : rooms) {  // 初始把所有房间编号都放进去
            s.insert(room[0]);  // multiset 自动保持升序
        }
        for (int j : idx) {  // 按规定顺序逐个处理查询
            int prefer = queries[j][0], minSize = queries[j][1];  // 偏好编号与面积下限
            while (i < n && rooms[i][1] < minSize) {  // 面积不达标的房间要移出候选集合
                s.erase(s.find(rooms[i][0]));  // find 定位单个元素，避免 erase 把同编号全部删掉
                ++i;  // 门槛单调不减，指针只需单向前进
            }
            if (i == n) {  // 所有房间面积都太小，之后的查询同样无解
                break;  // 剩余答案保持 -1
            }
            auto it = s.lower_bound(prefer);  // 找出编号 >= prefer 的最小房间
            if (it != s.end()) {  // 存在右侧邻居
                ans[j] = *it;  // 暂时以右侧邻居作为答案
            }
            if (it != s.begin()) {  // 存在左侧邻居
                --it;  // 退到左边那个编号更小的房间
                if (ans[j] == -1 || abs(*it - prefer) <= abs(ans[j] - prefer)) {  // 左侧距离不大于右侧时优先选编号更小的
                    ans[j] = *it;  // 用左侧邻居更新答案
                }
            }
        }
        return ans;  // 返回每个查询对应的房间编号
    }
};