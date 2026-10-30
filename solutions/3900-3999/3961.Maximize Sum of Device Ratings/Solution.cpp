// 3961. 设备评分的最大和 / Maximize Sum of Device Ratings
// 核心思路：设备评分为其所有单元容量的最小值。把每台设备的最小单元移走后，其评分升为次小值 x[1]，
//          共 m-1 台设备如此操作后剩一台设备作为接收方不损失，其评分降为全局最小值，因此答案为 sum(x[1]) - (mn2 - mn)。
// 复杂度：时间 O(m * n log n)（m 台设备、每台 n 个单元，逐行排序），空间 O(1)（除排序外原地处理）。

class Solution {
public:
    long long maxRatings(vector<vector<int>>& units) {  // 返回所有设备评分之和的最大值
        int n = units[0].size();  // 每台设备的单元数量
        if (n == 1) {  // 每台设备只有一个单元：移走会让该设备清空、评分变 0，不操作最优
            long long ans = 0;  // 累加所有设备的唯一评分
            for (auto& x : units) {  // 遍历每台设备
                ans += x[0];  // 直接累加该设备的唯一单元容量
            }
            return ans;  // 返回所有设备原本的评分之和
        }

        long long ans = 0;  // 累加每台设备贡献的次小值 x[1]
        int mn = INT_MAX;  // 记录所有设备单元容量中的全局最小值
        int mn2 = INT_MAX;  // 记录所有设备次小值 x[1] 中的最小值

        for (auto& x : units) {  // 逐台设备处理
            sort(x.begin(), x.end());  // 将该设备的单元容量升序排序
            ans += x[1];  // 移走最小单元后该设备评分变为次小值，累加进总和
            mn2 = min(mn2, x[1]);  // 更新最小的次小值（即损失最小的接收方）
            mn = min(mn, x[0]);  // 更新全局最小容量（会被送入接收方）
        }

        return ans - (mn2 - mn);  // 扣除一台设备评分由次小值降到全局最小值的损失
    }
};