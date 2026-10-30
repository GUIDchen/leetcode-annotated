// 题目：1601. 最多可达成的换楼请求数目（Maximum Number of Achievable Transfer Requests）
// 思路：二进制枚举请求子集，用出入度计数判断该子集能否让每栋楼人数守恒，取最大的合法子集大小。
// 时间复杂度：O(2^m * m)，枚举子集并逐个校验；空间复杂度：O(n)，一个出入度计数数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumRequests(int n, vector<vector<int>>& requests) {  // n 为楼栋数，requests[i] = {from, to} 表示一次换楼请求
        int m = requests.size();  // 请求总数，用于枚举子集
        int ans = 0;  // 合法请求子集的最大大小
        auto check = [&](int mask) -> bool {  // lambda：判断 mask 选出的这批请求能否同时全部满足
            int cnt[n];  // 每栋楼的净人数变化（搬入为 +，搬出为 -）
            memset(cnt, 0, sizeof(cnt));  // 清零，保证每次校验都从初始状态开始
            for (int i = 0; i < m; ++i) {  // 遍历所有请求
                if (mask >> i & 1) {  // 第 i 位为 1 表示该请求被选中
                    int f = requests[i][0], t = requests[i][1];  // f 是搬出楼，t 是搬入楼
                    --cnt[f];  // 搬出，该楼人数减少
                    ++cnt[t];  // 搬入，该楼人数增加
                }  // 选中判断结束
            }  // 请求遍历结束
            for (int v : cnt) {  // 检查每栋楼的净变化
                if (v) {  // 只要有一栋楼的净变化不为 0
                    return false;  // 人数就无法守恒，该子集不可行
                }  // 非零判断结束
            }  // 校验结束
            return true;  // 所有楼净变化都是 0，该子集可行
        };  // check lambda 定义结束
        for (int mask = 0; mask < 1 << m; ++mask) {  // 枚举所有 2^m 种请求子集
            int cnt = __builtin_popcount(mask);  // 统计子集里选了多少个请求
            if (ans < cnt && check(mask)) {  // 只有子集更大且合法时才更新答案
                ans = cnt;  // 记录新的最优值
            }  // 更新判断结束
        }  // 子集枚举结束
        return ans;  // 返回最多可同时满足的请求数
    }  // 方法结束
};  // 类结束